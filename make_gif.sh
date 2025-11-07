#!/bin/bash

# Conway's Game of Life GIF Generator
# Usage: ./make_gif.sh <output_file> <gif_name>
# Example: ./make_gif.sh glider_output.txt glider

if [ $# -ne 2 ]; then
    echo "Usage: ./make_gif.sh <output_file> <gif_name>"
    echo "Example: ./make_gif.sh glider_output.txt glider"
    exit 1
fi

OUTPUT_FILE="output/$1"
GIF_NAME="output/gifs/$2.gif"
FRAMES_DIR=$(mktemp -d)

# Catppuccin Macchiato colors
CELL_SIZE=60
DEAD_COLOR="#24273a"      # Dark purplish-blue
ALIVE_COLOR="#a6e3a1"     # Green
DYING_COLOR="#89b4fa"     # Blue

python3 << EOF
from PIL import Image, ImageDraw
import sys

CELL_SIZE = $CELL_SIZE
DEAD_COLOR = "$DEAD_COLOR"
ALIVE_COLOR = "$ALIVE_COLOR"
DYING_COLOR = "$DYING_COLOR"

output_file = "$OUTPUT_FILE"
frames_dir = "$FRAMES_DIR"

try:
    with open(output_file, 'r') as f:
        lines = f.readlines()
except FileNotFoundError:
    print(f"Error: Could not read {output_file}")
    sys.exit(1)

# Count total generations first
total_gens = sum(1 for line in lines if line.strip().startswith("Generation:"))

current_gen = []
image_count = 0

for line in lines:
    line = line.strip()
    if line.startswith("Generation:"):
        if current_gen:
            height = len(current_gen)
            width = len(current_gen[0]) if current_gen else 0

            img = Image.new('RGB', (width * CELL_SIZE, height * CELL_SIZE), color=DEAD_COLOR)
            draw = ImageDraw.Draw(img)

            for y, row in enumerate(current_gen):
                for x, cell in enumerate(row):
                    x1 = x * CELL_SIZE
                    y1 = y * CELL_SIZE
                    x2 = (x + 1) * CELL_SIZE
                    y2 = (y + 1) * CELL_SIZE

                    if cell == '1':
                        draw.rectangle([x1, y1, x2, y2], fill=ALIVE_COLOR)
                    elif cell == 'D':
                        draw.rectangle([x1, y1, x2, y2], fill=DYING_COLOR)

            img.save(f'{frames_dir}/frame_{image_count:04d}.png')
            image_count += 1

            # Progress bar
            progress = image_count / total_gens
            bar_length = 40
            filled = int(bar_length * progress)
            bar = '█' * filled + '░' * (bar_length - filled)
            print(f'Generating frames: |{bar}| {image_count}/{total_gens}', end='\r', flush=True)

            current_gen = []
    else:
        current_gen.append(line)

# Last generation
if current_gen:
    height = len(current_gen)
    width = len(current_gen[0]) if current_gen else 0

    img = Image.new('RGB', (width * CELL_SIZE, height * CELL_SIZE), color=DEAD_COLOR)
    draw = ImageDraw.Draw(img)

    for y, row in enumerate(current_gen):
        for x, cell in enumerate(row):
            x1 = x * CELL_SIZE
            y1 = y * CELL_SIZE
            x2 = (x + 1) * CELL_SIZE
            y2 = (y + 1) * CELL_SIZE

            if cell == '1':
                draw.rectangle([x1, y1, x2, y2], fill=ALIVE_COLOR)
            elif cell == 'D':
                draw.rectangle([x1, y1, x2, y2], fill=DYING_COLOR)

    img.save(f'{frames_dir}/frame_{image_count:04d}.png')
    image_count += 1
    progress = 1.0
    bar = '█' * 40
    print(f'Generating frames: |{bar}| {image_count}/{total_gens}', flush=True)

EOF

echo ""
echo "Creating GIF..."

# Convert to GIF with proper codec
ffmpeg -y -framerate 2 -i "$FRAMES_DIR/frame_%04d.png" -loop 0 "$GIF_NAME" 2>&1 | grep -v "^frame=" &
FFMPEG_PID=$!

# Spinner while ffmpeg works
spinner=( '⠋' '⠙' '⠹' '⠸' '⠼' '⠴' '⠦' '⠧' '⠇' '⠏' )
while kill -0 $FFMPEG_PID 2>/dev/null; do
    for s in "${spinner[@]}"; do
        echo -ne "\rEncoding: $s"
        sleep 0.1
    done
done

wait $FFMPEG_PID

# Cleanup
rm -rf "$FRAMES_DIR"

echo ""
echo "✓ GIF created: $GIF_NAME"
