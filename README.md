# Download BAG #

Code for downloading the Dutch Buildings Register (*Basisadministratie Gebouwen*/BAG) and converting it to CSV format. 




## Building code ##

The programmes to convert the XML-files from the BAG to CSV-format are written
in C++ and need to be compiled. In order to compile the programmes libxml2 and
libgdal need to be installed. Under Ubuntie this can be done using:

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

Should download the BAG and

```
make csv 
```

should convert the XML-files to CSV-format.



