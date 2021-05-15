CXX = pgc++
SOURCE = main.cpp
OBJ = main.o
EXISTED=$(wildcard $(SOURCE))
ifeq($(EXISTED),)
SOURCE := test.cpp
OBJ := test.o
endif

execute: $(OBJ)
	$(CXX) -o execute $(OBJ) -Minfo
$(OBJ): $(SOURCE)
	$(CXX) -c -acc -Minfo -std=c++11 $(SOURCE)

clean:
	rm -rf *.o execute 

