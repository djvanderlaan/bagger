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

rm -f "$BAGGER_OUTPUTDIR/openbareruimte.csv"

./bin/parse_opr --header > "$BAGGER_OUTPUTDIR/openbareruimte.csv"

for file in inspire/opr/*.xml
do
  echo "Processing $file"
  cat $file | ./bin/parse_opr >> "$BAGGER_OUTPUTDIR/openbareruimte.csv"
done

