#!/usr/bin/python3

#
# Provide the interface for a formatter object

################################################################
#
class ColumnFormatter(object) :

    ################################################################
    #
    def write_unknown(self) :
        pass

    ################################################################
    #
    def write_string(self, name, data) :
        """
        Write information about string data to stdout.
        
        NAME is the name of the data set.
        DATA is a dictionary of values.

        In the data, the following keys are required to be 
        present:  'distinct_count', 'null_count', both integers;
        'display_values', a list of pairs of the form 
        (str, int).
        """

        pass

    ################################################################
    #
    def write_flag(self, name, data) :
        """
        Write information about string data to stdout.
        
        NAME is the name of the data set.
        DATA is a dictionary of values.

        In the data, the following keys are required to be 
        present:  'true_count', 'false_count', and 'null_count', 
        all of which are integers.
        """

        pass

    ################################################################
    #
    def write_date(self, name, data) :
        """
        Write information about string data to stdout.
        
        NAME is the name of the data set.
        DATA is a dictionary of values.

        In the data, the following keys are required to be 
        present:  'valid_count' and 'null_count', both integers;
        'earliest' and 'latest' both strings that look like
        dates.
        """

        pass

    ################################################################
    #
    def write_float(self, name, data) :
        """
        Write information about string data to stdout.
        
        NAME is the name of the data set.
        DATA is a dictionary of values.

        In the data, the following keys are required to be 
        present:  'value_count' and 'null_count', both integers;
        'quartiles', an array of at least five numeric values;
        and 'avg' and 'sd' both numeric.
        dates.
        """

        pass

    ################################################################
    #
    def write_error(self, name) :
        print ('Error in field', name)

