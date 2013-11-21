#!/usr/bin/env python3

"""
Analyze input columns and report results
"""

import argparse
import itertools
import math
import sys

import csvfileio


################################################################
#
class Analyzer(object) :
    ################################################################
    #
    def __init__(self) :

        self.categories = [
            'Business_Status',
            'Facility_Risk_Rating',
            'Loan_Type',
            'Balance_Tier',
            'Term_Type',
            'Collateral_Group',
            'Period'
        ]

        self.category_values = {}
        for cat in self.categories :
            self.category_values[cat] = {}

        self.category_count = len(self.categories)

        self.headers = self.categories[:]
        self.headers.extend([
            'Count',
            'Total_Balance',
            'Effective_Rate'
        ])

        # input data
        #
        self.all_rows = []

    ################################################################
    #
    def read(self, infile) :
        with csvfileio.CsvFileIo(infile, False) as rdr :
            self._process(rdr)

    ################################################################
    #
    def write(self, outfile) :
        with csvfileio.CsvFileIo(outfile, True, self.headers) as rtr :
            rtr.writeheader()
            self._write_rows(rtr, self.all_rows, {}, 0)
        
    ################################################################
    #
    def _process(self, rdr) :
        for row in rdr :
            self.all_rows.append(row)

            for cat in self.categories :
                value = row[cat]
                self.category_values[cat][value] = 1

    ################################################################
    #
    def _write_rows(self, rtr, candidates, output, index) :
        if index < self.category_count :
            self._loop_on_index(rtr, candidates, output, index)
        else :
            self._write_one(rtr, candidates, output)

    ################################################################
    #
    def _loop_on_index(self, rtr, candidates, output, index) :
        key  = self.categories[index]
        vals = self.category_values[key]
        for val in vals.keys() :
            new_output = {}
            new_output.update(output)
            new_output[key] = val

            new_candidates = [x for x in candidates if x[key] == val]

            self._write_rows(rtr, new_candidates, new_output, index+1)

        new_output = {}
        new_output.update(output)
        new_output[key] = '***All***'
        self._write_rows(rtr, candidates, new_output, index+1)

    ################################################################
    #
    def _write_one(self, rtr, candidates, output) :

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

        rtr.writerow(output)
        
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
    analyzer.read(args.infile[0])
    analyzer.write(args.outfile[0])

################################################################
#
if __name__ == '__main__' :
    main()
