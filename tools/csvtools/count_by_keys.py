#!/usr/bin/env python3

"""
Analyze input columns and report results
"""

import argparse
import itertools
import math
import sys

import keycounter
        
################################################################
#
class Analyzer(keycounter.KeyCounter) :
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
