#!/usr/bin/env python3

import sys
import traceback
import datagenparser
import argparse
from parsertools import Success
import datagenlexer
import simplebuffer
import datagentoken
import random
import datetime
import datagenconfig
import rangetools
import itertools
import datagenfile

####################################################################
#
class DataGen(object) :
    """Spec based data generator"""

    ####################################################################
    #
    def __init__(self, spec, log) :
        """Set up defaults"""

        self.spec = spec
        self.log  = log
        self.good = True
        self.config = datagenconfig.DataGenConfig()

        self.valid_categories = datagentoken.get_valid_categories()
        self.valid_io         = datagentoken.get_valid_io()
        self.genvars = []

        self.config_handlers = {
            'EOF'      : self.end_of_config,
            'CATEGORY' : self.category_config,
            'LOOP'     : self.loop_config,
            'DECL'     : self.decl_config,
            'IO'       : self.io_config
        }

    ####################################################################
    #
    def parse_spec(self, trace=False) :
        """Parse specification"""

        try :
            lexer  = datagenlexer.DatagenLexer()
            buffr  = simplebuffer.SimpleBuffer(lambda : lexer.get_token())
            parser = datagenparser.DatagenConfigParser(buffr)

            datagentoken.add_tokens(lexer)

            for line in self.spec.readlines() :
                lexer.add_text(line)

            while self.good :
                result = parser.parse_toplevel()
                
                if not isinstance(result, Success) :
                    self.log.write('*** ERROR ***\n')
                    self.log.write('\n')
                    self.log.write(str(result))
                    self.log.write('\n')
                    self.good = False
                    raise Exception('Parse error %s' % str(result))

                ast = result.ast
                if not ast or len(ast) < 1 :
                    self.log.write('Unexpected command received: %s\n' % ast)
                    self.good = False
                    return

                cmd = ast[0]
                handler = self.config_handlers.get(cmd, self.unknown_config)
                (ok, done) = handler(ast, result.text, parser)
                if done :
                    if not ok :
                        self.good = False
                    break

        except IOError as e :
            self.good = False
            self.log.write('I/O Error: %s\n' % str(e)) 
        #except datagenparser.ParseError as p :
        #    print p
        #    print traceback.format_exc()
        
        if trace :
            self.log.write('[Config]\n')
            self.log.write('\n')
            self.log.write(str(self.config))
            self.log.write('\n')

        self.config.realize_ranges()

    ####################################################################
    #
    def update_config(self, text, ast, parser=None) :
        """Execute one order from the configuration file."""

    ####################################################################
    #
    def end_of_config(self, *args) :
        """End of command stream"""

        return (True, True)

    ####################################################################
    #
    def category_config(self, ast, *args) :
        """Configure a category"""
        
        cat = ast[1]
        if cat not in self.valid_categories :
            self.log.write('Unexpected category: %s\n' % cat)
            return (False, True)
            
        values = ast[2]
        self.config.add_vars(cat, values)

        if cat in [datagentoken.genkw, datagentoken.tmpkw] :
            self.genvars.extend(values)

        return (True, False)

    ####################################################################
    #
    def loop_config(self, ast, text, parser) :
        if len(ast) < 4 : 
            self.log.write('Bad Loop Configuration: %s' % str(ast))
            return (False, True)

        if parser :
            args = [parser.deparse_infix(x) for x in ast[1:4]]
        else :
            self.log.write('No parser to convert loop arguments\n')
            return (False, True)

        varname = '$loop'
        self.config.add_vars(datagentoken.tmpkw, [varname])
        self.config.add_model(varname, args)

        return (True, False)

    ####################################################################
    #
    def decl_config(self, ast, text, parser) :
        var_name = ast[1]
        if var_name not in self.config.get_vars() :
            msg = 'Undeclared variable: %s\n' % var_name
            raise Exception('Datagen error: %s' % msg)

        var_type   = ast[2]
        var_fmt    = ast[3]
        var_mod    = ast[4]
        var_range  = ast[5]

        if var_mod and var_range :
            self.log.write(
                'Cannot have both AS and RANGE clause for %s\n' % var_name
            )
            return (False, True)

        self.config.set_type_info(var_name, var_type, var_fmt)

        if var_name in self.genvars and var_mod:
            if parser :
                var_mod = parser.deparse_infix(var_mod)

            if var_type == 'integer' :
                var_mod = 'to_int(%s)' % var_mod
            elif var_type in ['double', 'float'] :
                var_mod = 'to_float(%s)' % var_mod

            self.config.add_model(var_name, var_mod)

        elif var_name in self.genvars and var_range :
            self.config.add_range(var_name, var_type, var_fmt, var_range)

        elif var_mod :
            self.log.write('Ignoring model for variable: %s\n' % var_name)

        return (True, False)

    ####################################################################
    #
    def io_config(self, ast, *args) :
        io_cat  = ast[1]
        if io_cat not in self.valid_io :
            self.log.write('Unknown I/O category: %s\n' % io_cat)
            return (False, True)

        io_file = ast[2] 
        self.config.add_io(io_cat, io_file)

        return (True, False)

    ####################################################################
    #
    def unknown_config(self, ast) :
        self.log.write('Unknown configuration command: %s\n' % ast[0])
        return (False, True)

    ####################################################################
    #
    def generate_data(self) :
        """Read a template and generate data"""

        if not self.good :
            self.log.write('Cannot generate data due to earlier errors.\n')
            return

        self.env = self.make_environment()

        try :
            with self.make_data_input() as self.src :
                self.verify_input_headers()
                with self.make_data_output() as self.dst :
                    self.dst.writeheader()
                    self.generate_lines()
        except IOError as e :
            self.log.write('Error generating data:\n')
            self.log.write(str(e))
            self.log.write('\n')
        finally :
            self.src = self.dst = None

    ####################################################################
    #
    def make_environment(self) :
        """Create global environment for future expression evaluation"""
        
        env = {}
        env['__builtins__'] = {} # globals()['__builtins__']

        def to_int(v) :
            return int(v)
        env['to_int'] = to_int

        def to_float(v) :
            return float(v)
        env['to_float'] = to_float

        def gauss(mu=0, sigma=1) :
            return random.gauss(mu, sigma)
        env['gauss'] = gauss

        def uniform(lo, hi) :
            if type(lo) == type(hi) == type(0) :
                return random.randint(lo, hi)
            return random.uniform(lo, hi)
        env['uniform'] = uniform

        def new_id(prefix) :
            return '%s%08d' % (prefix, random.uniform(1, 1e8-1))
        env['new_id'] = new_id

        return env

    ####################################################################
    #
    def make_data_input(self) :
        fn = self.config.get_io(datagentoken.inpkw)
        rv = datagenfile.DataGenFile(fn, False) 
        return rv

    ####################################################################
    #
    def verify_input_headers(self) :

        required = self.get_vars_by_category(
            datagentoken.rokw, 
            datagentoken.rwkw
        )
        fieldnames = self.src.fieldnames
        for key in required :
            if key not in self.genvars :
                if key not in fieldnames :
                    raise Exception('Input is missing a column: %s' % key)

    ####################################################################
    #
    def make_data_output(self) :
        fs = self.config.get_io(datagentoken.outkw)
        ov = self.get_vars_by_category(
            datagentoken.rwkw,
            datagentoken.genkw
        )
        rv = datagenfile.DataGenFile(fs, True, ov)
        return rv
        
    ####################################################################
    #
    def get_vars_by_category(self, *kws) :
        rv = []
        for kw in kws :
            rv.extend(self.config.get_vars(kw))
        return rv

    ####################################################################
    #
    def generate_lines(self) :
        """Transform input lines into output lines"""

        types = self.config.get_types()
        count = 0

        for row in self.src :
            local_dict = self.make_local_dict(row)
            if not local_dict :
                break
            count += 1

            output_rows = self.make_output(local_dict)
            if not output_rows :
                return
            if not self.write_output(output_rows, types) :
                return

        if count == 0 :
            if self.config.get_gen_values() :
                output_rows = self.make_output({})
                if not output_rows :
                    return
                if not self.write_output(output_rows, types) :
                    return

    ####################################################################
    #
    def make_local_dict(self, row) :
        """Convert data values by the key's local type."""
        
        types = self.config.get_types()
        data = {}

        for (k,v) in row.items() :
            t = types[k][0]
            if t == 'integer' :
                data[k] = int(v)
            elif t in ['double', 'float'] :
                data[k] = float(v)
            elif t == 'date' :
                fmt = types[k][1]
                vx = v.strip()
                if fmt :
                    vx = datetime.datetime.strptime(vx, fmt)
                data[k] = vx
            else :
                data[k] = v.strip()

        return data

    ####################################################################
    #
    def make_output(self, local_dict) :
        genvals = self.config.get_gen_values()
        models  = self.config.get_models()

        output_rows = self.expand_output_rows(local_dict, genvals)
        return self.produce_output(output_rows, models)

    ####################################################################
    #
    def expand_output_rows(self, start, rest) :
        rows = []
        if rest :
            for item in rest :
                d = {}
                d.update(start)
                d.update(item)
                rows.append(d)
        else :
            rows.append(local_dict)

        return rows

    ####################################################################
    #
    def produce_output(self, rows, models) :
        for row in rows :
            if not self.process_models(row, models) :
                return []

        return rows

    ####################################################################
    #
    def process_models(self, row, models) :
        for index in range(len(models)) :
            (key, fn) = models[index]
            env = {}
            env.update(row)
            env.update(self.env)

            try :
                if key == '$loop' :
                    return self.process_loop(fn, models[index+1:], row)

                #self.log.write(
                #    'Evaluating formula %s for %s\n' % (str(fn), str(key))
                #)

                result = eval(fn, env, None)
                #self.log.write('Result is %s\n' % str(result))
                row[key] = eval(fn, env, None)

            except Exception as e :
                msg = 'Unable to evaluate \'%s\',\n' % str(fn)
                self.log.write(msg)
                self.log.write('\t%s\n' % str(e))
                self.log.write('\tenv = %s\n' % str(env))
                return []

        return [row]

    ####################################################################
    #
    def process_loop(self, bounds, rest, context) :
        env = {}
        env.update(context)
        env.update(self.env)

        try :
            (start, stop, step) = [eval(f, env, None) for f in bounds]

        except Exception as e :
            msg = 'Unable to evaluate loop bounds \'%s\',\n' % str(bounds)
            self.log.write(msg)
            self.log.write('\t%s\n' % str(e))
            self.log.write('\tenv = %s\n' % str(env))
            return False
            
        vals  = list(rangetools.IntRange(start, stop, step).values())
        xvals = [dict([x]) for x in zip(itertools.cycle(['loop_index']), vals)]
        expanded = self.expand_output_rows(context, xvals)

        return self.produce_output(expanded, rest)

    ####################################################################
    #
    def write_output(self, rows, types) :
        for row in rows :
            if not self.convert_types(row, types) :
                return False
            self.dst.writerow(row)

        return True

    ####################################################################
    #
    def convert_types(self, row, types) :
        for key in types.keys() :
            (typ,fmt) = types[key]
            if fmt :
                value = row[key]
                try : 
                    if typ == 'date' :
                        row[key] = value.strftime(fmt)
                    else :
                        row[key] = fmt % value
                except ValueError as e :
                    vv = (str(value), key, str(fmt))
                    self.log.write(
                        'Cannot format value %s (%s) with format %s\n' % vv
                    )
                    self.log.write('\t%s\n' % str(e))
                    return False

        return True


####################################################################
###
###
###
if __name__ == '__main__' :

    parser = argparse.ArgumentParser()
    parser.add_argument("spec",
                        help="file with datagen spec", 
                        default=sys.stdin,
                        nargs='?',
                        type=argparse.FileType('r') )
    parser.add_argument("log",
                        help="file to which to write log messages", 
                        default=sys.stdout,
                        nargs='?',
                        type=argparse.FileType('w') )
    parser.add_argument("--trace",
                        help="turn on trace", 
                        action='store_true')

    try :
        args = parser.parse_args()
    except IOError as e :
        print (e)
        sys.exit(1)

    try :
        g = DataGen(spec=args.spec, log=args.log)
        g.parse_spec(trace=args.trace)
        g.generate_data()
    except Exception as e :
        traceback.print_exc()
        #print (e)
        sys.exit(1)
