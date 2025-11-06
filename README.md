# Conway's Game of Life Simulator

A C++ implementation of Conway's Game of Life. This version has options to run a few different game variations.

## Features

- **Classic Game of Life**: Standard rules with birth and death pattern.
- **3-State Mode** (`-s`): Variant with "dying" state for cells.
- **Wraparound Mode** (`-w`): Grid where edges wrap around to all sides.
- **Customizable Simulation**: Control the number of generations and print intervals.
- **File-based Input**: Load initial cell configurations from text files.

## Building

```sh
make
```

Compilation flags: `-Wall -Wextra -Werror -Wfatal-errors -std=c++20`

To clean build artifacts:

```sh
make clean
```

## Usage

```sh
./GOLApp -f <filename> [options]
```

### Required Arguments

- `-f <filename>`: Path to the initial configuration file (e.g., `tests/glider.txt`)

### Optional Arguments

- `-g <generations>`: Number of generations to simulate (default: 10)
- `-p <interval>`: Print every nth generation (default: 1)
- `-s`: Enable 3-state mode (mutually exclusive with `-w`)
- `-w`: Enable wraparound/toroidal mode (mutually exclusive with `-s`)

### Examples

```sh
# Simulate a glider with wraparound for 20 generations, printing every 4th
./GOLApp -f tests/glider -w -g 20 -p 4

# Run a toad oscillator with default settings
./GOLApp -f tests/toad

# Simulate with 3-state mode for 30 generations
./GOLApp -f tests/beacon -s -g 30
```

## Input File Format

Configuration files use a simple text format:

```
<height> <width>
O X X O X
X X X X X
X O O O X
X X X X X
X X X X X
```

- First line: two space-separated integers representing height and width
- Remaining lines: grid state where `O` represents a live cell and `X` represents a dead cell
- Whitespace between characters is ignored

## Game Rules

### Standard Mode
- A live cell with 2-3 neighbors survives
- A dead cell with exactly 3 neighbors becomes alive
- All other cells die or stay dead

### 3-State Mode (`-s`)
- Live cells with 2-3 neighbors stay alive; otherwise enter "dying" state (D)
- Dying cells become dead in the next generation
- Dead cells with exactly 3 neighbors enter the dying state

### Wraparound Mode (`-w`)
- The grid wraps around at edges, creating a toroidal topology
- Cells at the edges have neighbors from the opposite side

## Project Structure

```
.
├── include/          # Header files
│   ├── ArgParser.h
│   ├── GameOfLife.h
│   └── GOLparser.h
├── src/              # Implementation files
│   ├── Main.cpp
│   ├── ArgParser.cpp
│   ├── GameOfLife.cpp
│   └── GOLparser.cpp
├── tests/            # Sample configuration files
│   ├── glider.txt
│   ├── blinker.txt
│   └── ...
├── Makefile
└── README.md
```

## Author

Caleb Christian

## License

MIT License
