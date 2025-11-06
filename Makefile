CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -Wfatal-errors -std=c++20 -Iinclude

SRC = src/Main.cpp src/GameOfLife.cpp src/GOLparser.cpp src/ArgParser.cpp
OBJ = $(SRC:.cpp=.o)

GOLApp: $(OBJ)
	$(CXX) $(CXXFLAGS) -o GOLApp $^

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f src/*.o GOLApp
	@echo "Removed all object files and executable."

.PHONY: clean
