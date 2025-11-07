# Conway's Game of Life Simulator

A C++ implementation of Conway's Game of Life. This version has options to run a few different game variations.

## Features

- **Classic Game of Life**: Standard rules with birth and death pattern.
- **3-State Mode** (`-s`): Variant with "dying" state for cells.
- **Wraparound Mode** (`-w`): Grid where edges wrap around to all sides.
- **Customizable Simulation**: Control the number of generations and print intervals.
- **File-based Input**: Load initial cell configurations from text files.
- **Optional Output Files**: Save simulation results to files for GIF generation

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
- `-o <output_file>`: Write simulation output to a file (optional)
- `-s`: Enable 3-state mode (mutually exclusive with `-w`)
- `-w`: Enable wraparound (mutually exclusive with `-s`)

### Examples

```sh
# Simulate a glider with wraparound for 20 generations, printing every 4th
./GOLApp -f tests/glider -w -g 20 -p 4

# Simulate a glider with wraparound for 20 generations, printing every 4th, and write the results to an output file
./GOLApp -f tests/glider -w -g 100 -p 2 -o glider_output.txt

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

**Important:** The header format is `<height> <width>`, not `<width> <height>`. The height must match the number of rows that follow. For example:

```
18 11
```

means 18 rows with 11 columns each. If the dimensions don't match the actual grid, you'll get an error.

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
- The grid wraps around at edges
- Cells at the edges have neighbors from the opposite side

## GIF Generation

To visualize simulations as animated GIFs, use the included `make_gif.sh` script:

```sh
./GOLApp -f tests/glider -w -g 100 -p 2 -o glider_output.txt
./make_gif.sh glider_output.txt glider
```

The script will create `output/gifs/glider.gif`.

## Visualizations

**Classic Mode - Glider:**
```sh
./GOLApp -f tests/glider -g 15 -p 1 -o output_glider_classic_15gen.txt
./make_gif.sh output_glider_classic_15gen.txt glider_classic_15gen
```
![Classic Glider](output/gifs/glider_classic_15gen.gif)

**3-State Mode - Beacon:**
```sh
./GOLApp -f tests/beacon -s -g 20 -p 1 -o output_beacon_3state_20gen.txt
./make_gif.sh output_beacon_3state_20gen.txt beacon_3state_20gen
```
![3-State Beacon](output/gifs/beacon_3state_20gen.gif)

**Wraparound Mode - Glider:**
```sh
./GOLApp -f tests/glider -w -g 50 -p 1 -o output_glider_wraparound_50gen.txt
./make_gif.sh output_glider_wraparound_50gen.txt glider_wraparound_50gen
```
![Wraparound Glider](output/gifs/glider_wraparound_50gen.gif)

**Wraparound Mode - Pulsar:**
```sh
./GOLApp -f tests/pulsar -w -g 60 -p 1 -o output_pulsar_wraparound_60gen.txt
./make_gif.sh output_pulsar_wraparound_60gen.txt pulsar_wraparound_60gen
```
![Wraparound Pulsar](output/gifs/pulsar_wraparound_60gen.gif)

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
├── output/           # Generated output files and GIFs
├── make_gif.sh       # GIF generation script
├── Makefile
└── README.md
```

## Author

Caleb Christian

## License

MIT License
