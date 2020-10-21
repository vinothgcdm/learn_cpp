CXX		 = g++
CXXFLAGS = -Wall -std=c++17
TARGET	 = main
SRC		 = main.cpp
LDLIBS   = -lboost_thread -lboot_system
INCLUDE  = C:/Program\ Files/Boost/include/boost-1_73/

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDLIBS) -I$(INCLUDE) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)
