CXX		 = g++
CXXFLAGS = -Wall -std=c++17
TARGET	 = main
SRC		 = main.cpp
LDLIBS   = -lboost_thread -lboost_system

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDLIBS) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)
