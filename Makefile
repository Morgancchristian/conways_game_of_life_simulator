CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -Wfatal-errors -std=c++20 -Iinclude

SRC = src/Main.cpp src/GameOfLife.cpp src/GOLparser.cpp src/ArgParser.cpp
OBJ = src/Main.o src/GameOfLife.o src/GOLparser.o src/ArgParser.o

GOLApp: $(OBJ)
	$(CXX) $(CXXFLAGS) -o GOLApp $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o GOLApp *.o
	@echo "Removed all object files and executable."

.PHONY: clean
