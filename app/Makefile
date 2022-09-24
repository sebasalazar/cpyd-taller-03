CXX = g++
CXXFLAGS = -g3 -Wall -std=c++14
MKDIR = mkdir -p

LIBS = -lm -lpqxx -lpq

directorios:
	$(MKDIR) build dist

DBService.o: directorios DBService.cpp
	$(CXX) $(CXXFLAGS) -c DBService.cpp -o build/DBService.o

Utem.o: directorios Utem.cpp
	$(CXX) $(CXXFLAGS) -c Utem.cpp -o build/Utem.o

Trx.o: directorios Trx.cpp
	$(CXX) $(CXXFLAGS) -c Trx.cpp -o build/Trx.o

main.o: directorios main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o build/main.o

all: clean main.o Trx.o Utem.o DBService.o
	$(CXX) $(CXXFLAGS) -o dist/programa \
	build/main.o build/Trx.o build/Utem.o build/DBService.o \
	$(LIBS)
	rm -fr build

clean:
	rm -fr *.o a.out core programa dist build

.DEFAULT_GOAL := all
