#!/bin/bash

if [ -z "$BAGGER_OUTPUTDIR" ]
then
  export BAGGER_OUTPUTDIR="data"
fi

echo "Exporting CSV to $BAGGER_OUTPUTDIR"

if [ ! -d "$BAGGER_OUTPUTDIR" ]
then
  mkdir --parents "$BAGGER_OUTPUTDIR"
  echo "Creating $BAGGER_OUTPUTDIR"
fi

rm -f "$BAGGER_OUTPUTDIR/nummeraanduidingen.csv"

./bin/parse_num --header > "$BAGGER_OUTPUTDIR/nummeraanduidingen.csv"

for file in inspire/num/*.xml
do
  echo "Processing $file"
  cat $file | ./bin/parse_num >> "$BAGGER_OUTPUTDIR/nummeraanduidingen.csv"
done

