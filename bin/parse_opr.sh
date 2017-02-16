#!/bin/bash

if [ ! -d data]
then
  mkdir data
fi

rm -f data/openbareruimte.csv

./bin/parse_opr --header > data/openbareruimte.csv

for file in inspire/opr/*.xml
do
  echo "Processing $file"
  cat $file | ./bin/parse_opr >> data/openbareruimte.csv
done

