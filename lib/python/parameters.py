#!/usr/bin/env python3

"""Generic parameter file reader."""

# name of the file to look for if not specified.
#
_master_file = 'mst_parms.dat'

################################################################
#
class Parms(object) :
    """Interface to a parameters file.

    Lines in the input file have the form:
    
    parm_name [context] : value
    
    'context' looks like '[' key = value [, key = value ]* ']'.

    When present, the context overrides the parm_name for those key/value
    combinations.  Blank lines are allowed, and lines starting with '#' 
    are ignored.
    """

    ################################################################
    #
    def __init__(self, f = _master_file) :
        """Read data file and initialize parameters."""

        self.set_defaults()

        with open(f) as dat :
            for line in dat :
                (name, context, value) = self.parse_line(line)
                if name != None :
                    self.put(name, context, value)

        c = [k for k in self.params.keys()]
        c.sort(key = lambda x : (- len(x), x))
        self.contexts = c

    ################################################################
    #
    def set_defaults(self) :
        """Set up default values.

        Derived classes should call this version before doing anything.
        
        """

        self.params = {}
        self.params[()] = {}
        self.params[()][()] = {}

    ################################################################
    #
    def parse_line(self, line) :
        """Convert one line into parameter format."""

        line = line[:-1]
                
        if len(line) == 0 :
            return None,None,None
        if line[0] == '#' :
            return None,None,None

        context = {}
        (name, rest) = line.split(' ', 1)
        if rest[0] == '[' :
            (kvlist,pvalue) = rest[1:].split(']')
            kvpairs = kvlist.split(',')
            for kvp in kvpairs :
                (k,v) = kvp.split('=')
                context[k.strip()] = v.strip()
        else :
            pvalue = rest

        pvalue = pvalue.strip()
        try :
            x = float(pvalue)
            pvalue = x
        except ValueError :
            pass

        return (name, context, pvalue)

    ################################################################
    #
    def put(self, name, context, value) :
        """Process one parameter entry.

        NAME    is the name by which the parameter will be fetched.
        CONTEXT is a dictionary for the domain to which name applies.
        VALUE   is the value of the parameter.
        """

        if context :
            ks = [k for k in context.keys()]
            ks.sort()
            vs = [context[k] for k in ks]
            ks = tuple(ks)
            vs = tuple(vs)
            if not ks in self.params.keys() :
                self.params[ks] = {}
            if not vs in self.params[ks].keys() :
                self.params[ks][vs] = {}
            self.params[ks][vs][name] = value
        else :
            self.params[()][()][name] = value

    ################################################################
    #
    def get(self, name, context={}) :
        """Get a parameter from the best matching context.

        NAME    is the parameter to look up.
        CONTEXT is a dictionary to match in the contexts.
        """

        lck = context.keys()
        candidate_contexts = []
        for c in self.contexts :
            if all(k in lck for k in c) :
                candidate_contexts.append(c)

        for c in candidate_contexts :
            context_values = tuple(context[k] for k in c)
            try : 
                t = self.params[c][context_values][name]
                return t
            except KeyError :
                pass

        return None

################################################################
#
def main() :
    p = Parms()
    print (dir(p))
    print (p.params)

################################################################
#
if __name__ == '__main__' :
    main()
