#!/bin/bash

O=$1
if [ -z "$1" ]; then
    exit 1
fi
M=$(echo $1 | sed -e 's/^main_//' | sed -e 's/\.cpp$//')

echo ""                                 > $O
echo "extern void $M(int, char**);"    >> $O
echo ""                                >> $O
echo "int main(int argc, char** argv)" >> $O
echo "{"                               >> $O
echo "    $M(argc, argv);"             >> $O
echo "    return 0;"                   >> $O
echo "}"                               >> $O

exit 0