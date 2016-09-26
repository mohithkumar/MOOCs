CXX = g++ --std=c++11
INCLUDES= -I. -I/usr/include/
LIBS = -L/usr/lib/ -lboost_system -lboost_program_options
CXXFLAGS = -g -Wall $(INCLUDES) # -DFILE_BASED
SRCM = Graph.cpp
OBJM = $(SRCM:.cpp=.o)
TARGET = MinCut

all: $(TARGET)

$(TARGET): main.cpp $(OBJM)
	$(CXX) $(CXXFLAGS) -o $@ main.cpp $(LIBS) $(OBJM)

# Default compile
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJM) $(TARGET)

