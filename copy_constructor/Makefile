app: main.o point.o
	@echo "Building..."
	@g++ main.o point.o -o app -std=c++0x

main.o: main.cpp point.h
	@echo "Compile main.cpp..."
	@g++ -c main.cpp -std=c++0x

point.o: point.cpp point.h
	@echo "Compile point.cpp..."
	@g++ -c point.cpp -std=c++0x

.PHONY: clean
clean:
	@echo "Clean repo..."
	@rm -fr app *.o
