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

rm -f "$BAGGER_OUTPUTDIR/panden.csv"

./bin/parse_pnd --header > "$BAGGER_OUTPUTDIR/panden.csv"

for file in inspire/pnd/*.xml
do
  echo "Processing $file"
  cat $file | ./bin/parse_pnd >> "$BAGGER_OUTPUTDIR/panden.csv"
done

