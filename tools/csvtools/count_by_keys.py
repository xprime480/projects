#!/usr/bin/env python3

"""
Analyze input columns and report results
"""

import argparse
import itertools
import math
import sys

import csvprocessor


################################################################
#
class KeyCounter(csvprocessor.CsvProcessor) :

    ################################################################
    #
    def __init__(self, categories, extra_columns = ['Count']) :
        super().__init__()

        self.categories = categories

        self.category_values = {}
        for cat in self.categories :
            self.category_values[cat] = {}

        self.category_count = len(self.categories)

        self.headers = self.categories[:]
        self.headers.extend(extra_columns)

        # input data
        #
        self.all_rows = []


    ################################################################
    #
    def process_row(self, row) :
        self.all_rows.append(row)

        for cat in self.categories :
            value = row[cat]
            self.category_values[cat][value] = 1

    ################################################################
    #
    def start_write(self) :
        return self.headers[:]

    ################################################################
    #
    def get_next_output_row(self) :
        for row in self._generate_rows(self.all_rows, {}, 0) :
            yield row

    ################################################################
    #
    def _generate_rows(self, candidates, output, index) :
        if index < self.category_count :
            for row in self._loop_on_index(candidates, output, index) :
                yield row
        else :
            for row in self.generate_one(candidates, output) :
                yield row

    ################################################################
    #
    def _loop_on_index(self, candidates, output, index) :
        key  = self.categories[index]
        vals = self.category_values[key]
        for val in vals.keys() :
            new_output = {}
            new_output.update(output)
            new_output[key] = val

            new_candidates = [x for x in candidates if x[key] == val]

            for row in self._generate_rows(new_candidates, new_output, index+1) :
                yield row

        new_output = {}
        new_output.update(output)
        new_output[key] = '***All***'
        for row in self._generate_rows(candidates, new_output, index+1) :
            yield row

    ################################################################
    #
    def generate_one(self, candidates, output) :
        output['Count'] = len(candidates)
        yield output
        
################################################################
#
class Analyzer(KeyCounter) :
    __categories = [
        'Business_Status',
        'Facility_Risk_Rating',
        'Loan_Type',
        'Balance_Tier',
        'Term_Type',
        'Collateral_Group',
        'Period'
    ]

    __extra = [
        'Count',
        'Total_Balance',
        'Effective_Rate'
    ]

    def __init__(self) :
        super().__init__(Analyzer.__categories, Analyzer.__extra)

    def generate_one(self, candidates, output) :

        if output['Collateral_Group'].startswith('Fin') :
            return

        lt = output['Loan_Type']
        tt = output['Term_Type']
        bt = output['Balance_Tier']
        nn = 'None'
        if lt == 'TERM' :
            if tt == nn :
                return
            if bt != nn :
                return
        elif lt == 'REVOLVER' :
            if tt != nn :
                return
            if bt == nn :
                return
        elif lt == '***All***' :
            if tt == bt == nn :
                return

        bal = sum([
            int(x['TotalFacilityCommitmentBalance'])
            for x in candidates
        ])
        try :
            rate = sum([
                float(x['Effective_Rate'])
                for x in candidates
            ])
        except KeyError as e :
            print (e)
            print (list(candidates[0].keys()))
            sys.exit(2)
        
        count = len(candidates)
        if count :
            rate /= count

        output['Count']          = count
        output['Total_Balance']  = bal
        output['Effective_Rate'] = rate

        yield output

################################################################
#
def main() :
    """Read inputs and analyze columns."""

    parser = argparse.ArgumentParser()
    parser.add_argument("infile",
                        help="CSV input file",
                        nargs=1)
    parser.add_argument("outfile",
                        help="CSV output file",
                        nargs=1)

    try :
        args = parser.parse_args()
    except IOError as e :
        print (e)
        sys.exit(1)
    
    analyzer = Analyzer()
    analyzer.read(*args.infile)
    analyzer.write(*args.outfile)

################################################################
#
if __name__ == '__main__' :
    main()
