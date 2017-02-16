#!/bin/bash

if [ ! -d data ]
then
  mkdir data
fi

rm -f data/woonplaatsen.csv

./bin/parse_wpl --header > data/woonplaatsen.csv

for file in inspire/wpl/*.xml
do
  echo "Processing $file"
  cat $file | ./bin/parse_wpl >> data/woonplaatsen.csv
done

