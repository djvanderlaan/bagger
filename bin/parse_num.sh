#!/bin/bash

if [ ! -d data ]
then
  mkdir data
fi

rm -f data/nummeraanduidingen.csv

./bin/parse_num --header > data/nummeraanduidingen.csv

for file in inspire/num/*.xml
do
  echo "Processing $file"
  cat $file | ./bin/parse_num >> data/nummeraanduidingen.csv
done

