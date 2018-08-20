
import itertools
import rangetools

class DataGenConfig(object) :

    def __init__(self) :
        """Set up defaults"""

        self.vars = {}

        self.allvars = []

        self.type_map = {}
        self.models   = []

        self.range_names = []
        self.range_vals  = []
        
        self.io = {}

        self.generated_values = []

    def add_vars(self, category, values) :
        if category in self.vars.keys() :
            self.vars[category].extend(values)
        else :
            self.vars[category] = values[:]

        self.allvars.extend(values)

    def get_vars(self, category=None) :
        if category :
            return self.vars.get(category, [])
        else :
            return self.allvars

    def set_type_info(self, var_name, var_type, var_fmt) :
        self.type_map[var_name] = (var_type, var_fmt)

    def get_types(self) :
        return self.type_map

    def add_model(self, mod_name, model) :
        self.models.append((mod_name, model))

    def get_models(self) :
        return self.models

    def add_range(self, var_name, var_type, var_fmt, var_range) :
        self.range_names.append(var_name)
        self.range_vals.append(self.make_range(var_type, var_fmt, var_range))

    ####################################################################
    #
    def make_range(self, var_type, var_fmt, var_range) :
        args_in = [x[1] for x in var_range[2:5]]

        if var_type == 'date' :
            cls = rangetools.DateRange
        elif var_type == 'integer' :
            cls = rangetools.IntRange
        elif var_type in ['double', 'float'] :
            cls = rangetools.FloatRange
        else :
            raise Exception('make_range: unknown type %s' % var_type)

        rv = list(cls(*args_in, fmt=var_fmt).values())
        return rv

    def realize_ranges(self) :
        names = self.range_names
        tmp   = itertools.product(*self.range_vals)
        self.generated_values = [dict(zip(names, x)) for x in tmp]

    def get_gen_values(self) :
        return self.generated_values

    def add_io(self, category, value) :
        self.io[category] = value

    def get_io(self, category) :
        return self.io.get(category, None)
