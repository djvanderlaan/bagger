#!/bin/bash

if [ ! -d data]
then
  mkdir data
fi

rm -f data/panden.csv

./bin/parse_pnd --header > data/panden.csv

for file in inspire/pnd/*.xml
do
  echo "Processing $file"
  cat $file | ./bin/parse_pnd >> data/panden.csv
done

