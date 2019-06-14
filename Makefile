
EXE_DIR=../bin/
BUILD_DIR=../bin/build/

# Object Files
SOURCE_FILES= \
	./src/Table.hpp \
	./src/Utils.hpp \
	./src/Utils.cpp \
	./src/Table.cpp

build:
	mkdir -p $(BUILD_DIR)
	g++ -std=c++11 ./tests/test1.cpp $(SOURCE_FILES) -o ./bin/test1
	
run:
	./bin/test1
	
run-win:
	./bin/test1.exe

clean:
	rm *.gch
	rm ./src/*.gch
	
	