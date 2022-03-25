TC_FOLDER = tests
EXT_IN = in
EXT_OUT = out
EXT_ANS = ans
EXECUTABLE_FILENAME = main
SRC_FOLDER = src
ALL_SRCS := $(wildcard *.cpp)
SRCS     := $(filter-out check.cpp, $(SRC_FOLDER)/$(ALL_SRCS))

all: compile test check

MainKrap: manual run

manual: 
	g++ -std=c++17 src/main.cpp src/MainKrap.cpp src/Item/Item.cpp src/Exception/Exception.cpp src/Boxes/Boxes.cpp src/Boxes/Inventory.cpp src/Boxes/Recipe.cpp src/Boxes/Crafting.cpp -o src/main.exe  -lstdc++fs

# Compile all cpp files except check.cpp
compile:
	g++ -std=c++17 -o $(EXECUTABLE_FILENAME) $(SRCS) -lstdc++fs 

# Test
test: $(TC_FOLDER)/*.$(EXT_IN) $(EXECUTABLE_FILENAME)
	for inputfile in $(TC_FOLDER)/*.$(EXT_IN); do \
		./$(EXECUTABLE_FILENAME) < $$inputfile; \
	done;

# Check
check: FORCE check.cpp
	g++ -std=c++17 -o check check.cpp
	./check

FORCE: ;