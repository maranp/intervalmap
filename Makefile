CXXINCFLAGS := -std=c++11 -I /home/maran/eclipse/boost_1_62_0 -Werror=narrowing #-O3
CXXFLAGS := -Wall -g $(CXXINCFLAGS)
LDFLAGS := -lpthread
SRC := $(wildcard *.cpp)
TARGET := $(SRC:%.cpp=bin/%)

all: | bin $(TARGET)

bin/% : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

bin:
	mkdir bin

clean:
	rm -fr bin/
