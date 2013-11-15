#!/usr/bin/bash

#
# names of CSV files read from the command line.
#
# names converted to output files according to scheme
#
# input/directory/path/base.csv -> columns.input.directory.path.base.txt 
#
function report_columns () {
    input_file=${1}
    base_file_name=`basename ${input_file} .csv`
    directory=`dirname ${input_file}`
    output_infix=`echo ${directory} | tr / .`
    output_file=columns${output_infix}.${base_file_name}.txt

    head -1 ${input_file} | tr ',' '\012' | nl -ba > ${output_file}

}

while [ $# -gt 0 ]; do
    report_columns ${1}
    shift
done

exit 0

for x in `ls *.csv`; do
    base=`basename $x .csv`
    text=${base}.txt
done

