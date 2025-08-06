CPPFLAGS=-I/usr/include/libxml2
LDLIBS=-lxml2 -lgdal

.PHONY: build clean download nummeraanduiding openbareruimte panden \
  verblijfsobjecten woonplaatsen gemeentes csv


build: bin/parse_vbo bin/parse_opr bin/parse_num bin/parse_pnd bin/parse_wpl bin/parse_gem

bin/parse_vbo: src/parse_vbo.cpp src/parse.h
	g++ -o bin/parse_vbo $(CPPFLAGS) src/parse_vbo.cpp $(LDLIBS)

bin/parse_opr: src/parse_opr.cpp src/parse.h
	g++ -o bin/parse_opr $(CPPFLAGS) src/parse_opr.cpp $(LDLIBS)

bin/parse_num: src/parse_num.cpp src/parse.h
	g++ -o bin/parse_num $(CPPFLAGS) src/parse_num.cpp $(LDLIBS)

bin/parse_pnd: src/parse_pnd.cpp src/parse.h
	g++ -o bin/parse_pnd $(CPPFLAGS) src/parse_pnd.cpp $(LDLIBS)

bin/parse_wpl: src/parse_wpl.cpp src/parse.h
	g++ -o bin/parse_wpl $(CPPFLAGS) src/parse_wpl.cpp $(LDLIBS)

bin/parse_gem: src/parse_gem.cpp src/parse.h
	g++ -o bin/parse_gem $(CPPFLAGS) src/parse_gem.cpp $(LDLIBS)

clean:
	rm bin/parse_vbo bin/parse_opr bin/parse_num bin/parse_pnd


#INSPIRE_URL=http://geodata.nationaalgeoregister.nl/inspireadressen/extract/inspireadressen.zip
INSPIRE_URL=https://service.pdok.nl/lv/bag/atom/downloads/lvbag-extract-nl.zip
      
      

download:
	if [ ! -d inspire ]; \
	then \
	  mkdir inspire; \
	fi
	if [ ! -f inspire/inspireadressen.zip ]; \
	then \
	  wget -O inspire/inspireadressen.zip $(INSPIRE_URL); \
	else \
	  echo "File is already downloaded"; \
	fi
	rm -f inspire/*.xml
	unzip inspire/inspireadressen.zip -d inspire

csv: nummeraanduiding openbareruimte panden verblijfsobjecten woonplaatsen gemeentes

nummeraanduiding:
	if [ ! -d inspire/num ]; \
	then \
	  mkdir inspire/num; \
	fi
	rm -f inspire/num/*.xml
	unzip inspire/9999NUM*.zip -d inspire/num
	./bin/parse_num.sh

openbareruimte:
	if [ ! -d inspire/opr ]; \
	then \
	  mkdir inspire/opr; \
	fi
	rm -f inspire/opr/*.xml
	unzip inspire/9999OPR*.zip -d inspire/opr
	./bin/parse_opr.sh

panden:
	if [ ! -d inspire/pnd ]; \
	then \
	  mkdir inspire/pnd; \
	fi
	rm -f inspire/pnd/*.xml
	unzip inspire/9999PND*.zip -d inspire/pnd
	./bin/parse_pnd.sh

verblijfsobjecten:
	if [ ! -d inspire/vbo ]; \
	then \
	  mkdir inspire/vbo; \
	fi
	rm -f inspire/vbo/*.xml
	unzip inspire/9999VBO*.zip -d inspire/vbo
	./bin/parse_vbo.sh

woonplaatsen:
	if [ ! -d inspire/wpl ]; \
	then \
	  mkdir inspire/wpl; \
	fi
	rm -f inspire/wpl/*.xml
	unzip inspire/9999WPL*.zip -d inspire/wpl
	./bin/parse_wpl.sh

gemeentes:
	if [ ! -d inspire/gem ]; \
	then \
	  mkdir inspire/gem; \
	fi
	rm -f inspire/gem/*.xml
	unzip inspire/GEM-WPL*.zip -d inspire/gem
	./bin/parse_gem.sh

