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

rm -f "$BAGGER_OUTPUTDIR/gemeente_woonplaats.csv"

./bin/parse_gem --header > "$BAGGER_OUTPUTDIR/gemeente_woonplaats.csv"

for file in inspire/gem/*.xml
do
  echo "Processing $file"
  cat $file | ./bin/parse_gem >> "$BAGGER_OUTPUTDIR/gemeente_woonplaats.csv"
done

