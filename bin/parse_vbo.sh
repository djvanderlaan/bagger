#!/bin/bash

if [ ! -d data]
then
  mkdir data
fi

rm -f data/verblijfsobjecten.csv

./bin/parse_vbo --header > data/verblijfsobjecten.csv

for file in inspire/vbo/*.xml
do
  echo "Processing $file"
  cat $file | ./bin/parse_vbo >> data/verblijfsobjecten.csv
done


