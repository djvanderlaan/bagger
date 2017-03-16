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

rm -f "$BAGGER_OUTPUTDIR/verblijfsobjecten.csv"

./bin/parse_vbo --header > "$BAGGER_OUTPUTDIR/verblijfsobjecten.csv"

for file in inspire/vbo/*.xml
do
  echo "Processing $file"
  cat $file | ./bin/parse_vbo >> "$BAGGER_OUTPUTDIR/verblijfsobjecten.csv"
done

