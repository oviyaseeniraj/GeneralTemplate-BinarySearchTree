#MAKEFILE

CXXFLAGS: -std=c++11 -g -Wall -Wno -uninitialized

all: tests
	./tests

tests: genbst.cpp testbst.cpp
	g++ $(CXXFLAGS) genbst.cpp testbst.cpp -o tests

clean:
	rm tests