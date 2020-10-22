CXX		 = g++
CXXFLAGS = -Wall
TARGET	 = main
SRC		 = main.cpp
LDLIBS   =

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDLIBS) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)
