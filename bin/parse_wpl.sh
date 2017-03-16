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

rm -f "$BAGGER_OUTPUTDIR/woonplaatsen.csv"

./bin/parse_wpl --header > "$BAGGER_OUTPUTDIR/woonplaatsen.csv"

for file in inspire/wpl/*.xml
do
  echo "Processing $file"
  cat $file | ./bin/parse_wpl >> "$BAGGER_OUTPUTDIR/woonplaatsen.csv"
done

