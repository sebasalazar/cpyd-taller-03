CXX = g++
CXXFLAGS = -g3 -Wall -std=c++14
MKDIR = mkdir -p

LIBS = -lm

directorios:
	$(MKDIR) build dist

Utem.o: directorios Utem.cpp
	$(CXX) $(CXXFLAGS) -c Utem.cpp -o build/Utem.o

Trx.o: directorios Trx.cpp
	$(CXX) $(CXXFLAGS) -c Trx.cpp -o build/Trx.o

main.o: directorios main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o build/main.o

all: clean main.o Trx.o Utem.o
	$(CXX) $(CXXFLAGS) -o dist/programa \
	build/main.o build/Trx.o build/Utem.o \
	$(LIBS)
	rm -fr build

clean:
	rm -fr *.o a.out core programa dist build

.DEFAULT_GOAL := all
