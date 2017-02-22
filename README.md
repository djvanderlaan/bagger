# Download BAG #

Code for downloading the Dutch Buildings Register (*Basisadministratie Gebouwen*/BAG) and converting it to CSV format. 




## Building code ##

The programmes to convert the XML-files from the BAG to CSV-format are written
in C++ and need to be compiled. In order to compile the programmes libxml2 and
libgdal need to be installed. Under Ubuntu this can be done using:

```
sudo apt install libxml2-dev libgdal-dev
```

The binaries can then be built using

```
make build
```

## Downloading the BAG and converting it to CSV ##

```
make download
```

should download the BAG and

```
make csv 
```

should convert the XML-files to CSV-format. This generates a number of CSV-files. 


### data/panden.csv ###

Variable           | Type     | Description
-------------------|----------|--------------------------------------------------------------
id                 | string   | id of building
bouwjaar           | integer  | year built
pandstatus         | string   | status of building
begin\_geldigheid  | date     | start date of validity record (format: `2016123100000000000`)
eind\_geldigheid   | date     | end date of validity; often empty
geometrie\_wkt     | string   | polygon of building in WKT format (rijksdriehoek coordinates)
x                  | double   | x coordinate of centroid of building (rijksdriehoek)
y                  | double   | y coordinate

