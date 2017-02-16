#!/bin/bash

if [ ! -d data ]
then
  mkdir data
fi

rm -f data/gemeente_woonplaats.csv

./bin/parse_gem --header > data/gemeente_woonplaats.csv

for file in inspire/gem/*.xml
do
  echo "Processing $file"
  cat $file | ./bin/parse_gem >> data/gemeente_woonplaats.csv
done

