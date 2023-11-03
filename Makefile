
TARGET = crow_demo
# C++ Source Code Files
CXXFILES = main.cc
# C++ Headers Files
HEADERS = 

CXX = clang++
CXXFLAGS += -g -O3 -Wall -pedantic -pipe -std=c++17
LDFLAGS += -g -O3 -Wall -pedantic -pipe -std=c++17

OBJECTS = $(CXXFILES:.cc=.o)

DEP = $(CXXFILES:.cc=.d)

default all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJECTS) $(LLDLIBS)

-include $(DEP)

%.d: %.cc
	set -e; $(CXX) -MM $(CXXFLAGS) $< 	| sed 's/\($*\)\.o[ :]*/.o $@ : /g' > $@; 	[ -s $@ ] || rm -f $@

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $<

clean:
	-rm -f $(OBJECTS) core $(TARGET).core

spotless: clean
	-rm -f $(TARGET) $(DEP) a.out
	-rm -rf $(DOCDIR)
	-rm -rf $(TARGET).dSYM
	-rm -f compile_commands.json
