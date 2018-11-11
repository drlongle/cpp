
CXX	:= g++
CXXFLAGS := -Wall -Wno-unused-parameter -std=c++17 -g
GTEST	:=/home/long/src/googletest/googletest
GMOCK	:=/home/long/src/googletest/googlemock

all: solution

solution: solution.o
	$(CXX) -o $@ solution.o $(GTEST)/make/gtest_main.a -lpthread

.cpp.o:
	$(CXX) -c $(CXXFLAGS) -I$(GTEST)/include -I$(GMOCK)/include $<

clean:
	rm -f *.o solution *~


