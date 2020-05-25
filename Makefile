.SUFFIXES: .c .cc .h

SOURCES = gml_scanner.c gml_parser.c gml_demo.c
OBJECTS = $(SOURCES:.c=.o)
CC = gcc
CFLAGS = -g

# where LEDA is installed

# LEDADIR = /usr/local/lib/LEDA-3.4.1
LEDADIR = $(LEDAGCCBASE)

CXXSOURCES = gml_to_graph.cc gml_to_graph_demo.cc
CXXOBJECTS = $(CXXSOURCES:.cc=.o)
CXXFLAGS = -g -I$(LEDADIR)/include -I.
CXX = g++

all : gml gml_to_graph

gml: $(OBJECTS)
	$(CC) -o gml_demo $(OBJECTS)

gml_to_graph : $(CXXOBJECTS) gml_scanner.o gml_parser.o
	$(CXX) -o gml_to_graph_demo $(CXXOBJECTS) gml_parser.o gml_scanner.o -L$(LEDADIR)/lib -lG -lL -lm


archive : $(SOURCES) $(CXXSOURCES) Makefile 
	zip gml_tools $(SOURCES) $(CXXSOURCES) Makefile *.h 

.PHONY: clean

clean: 
	-rm -f $(OBJECTS) $(CXXOBJECTS) gml_demo gml_to_graph_demo



