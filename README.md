# Maze-Maker

Given an ASCII maze file (and optional game inputs), the purpose of this project is to **visualize the maze** as a JGraph drawing. You can either use a pre-made maze file or **generate a random maze** with the included generator, then render it to a PDF or image. The program outputs JGraph (`.jgr`) that can be converted to PostScript, PDF, or PNG/JPG.

## Example Input (Maze File)

The maze is a text file: one character per cell. All lines must have the same length (rectangular grid).

- `#` = wall  
- `.` = open path  
- `S` = start  
- `E` = exit  
- `*` = solution path (optional)

Example (`examples/maze1.txt`):

```
#########################################
#S..#...#.........#.......#.....#.......#
###.###.#.#.#####.###.###.#.###.#.#####.#
...
#.................#...#.#...#...#...#..E#
#########################################
```

## Command-Line Inputs

### 1. mazechart (render maze → JGraph)

**Usage:**

```text
./mazechart <maze.txt> [options]
```

- **maze.txt** — Input maze file (required). Must be rectangular; characters `# . S E *` (others treated as open with a warning).
- **options** (optional; last occurrence wins):
  - `cell_size X` — Size of each cell (default: 0.20). Larger = bigger cells in the graph.
  - `no_gridlines` — Turn off grid lines between cells.
  - `grid_spacing X` — Label row/column indices every X cells (default: 10).
  - `no_numbering` — Do not draw row/column labels.
  - `all_numbers` — Label every row and column.

Output is printed to **stdout** (JGraph format). Redirect to a file and then run `jgraph` to get PostScript, then PDF or an image.

### 2. maze_gen (generate a random maze)

**Usage:**

```text
./maze_gen <width> <height> [output.txt]
```

- **width**, **height** — Maze size in *cells* (e.g. 15 20). Must be between 2 and 200.
- **output.txt** — Optional. If omitted, the maze is printed to stdout.

The generator builds a perfect maze (one path between any two cells) and places `S` at the top-left and `E` at the bottom-right.

## Full Example

**Build:**

```bash
# Build mazechart (C++)
make

# Build maze generator (C)
gcc -o maze_gen maze_gen.c
```

**Render an existing maze to PDF:**

```bash
./mazechart examples/maze1.txt cell_size 0.25 > out.jgr
jgraph -P out.jgr > out.ps
ps2pdf out.ps out.pdf
open out.pdf
```

Or use the convert script (maze → JGraph → PostScript → PDF/PNG/JPG):

```bash
./scripts/convert.sh examples/maze1.txt cell_size 0.35 output.pdf
open output.pdf
```

**Generate a new maze and render it:**

```bash
./scripts/make_maze.sh 15 20
# Creates maze_15x20.txt and maze_15x20.pdf
open maze_15x20.pdf
```

One-liner (generate maze, render to JGraph, then to PDF and JPEG):

```bash
./maze_gen 10 10 maze10.txt && ./mazechart maze10.txt cell_size 0.3 > maze10.jgr && jgraph -P maze10.jgr | ps2pdf - maze10.pdf && convert -density 300 maze10.pdf -quality 100 maze10.jpg
```

## Creating the Board (JGraph)

- **Dimensions** — Taken from the maze: height = number of rows, width = number of columns. The graph's coordinate system is set with `xaxis` and `yaxis` (min/max, size, nodraw).
- **Cells** — Each maze character is one cell. A cell is drawn as a **filled polygon**: `newcurve poly pcfill r g b pts x0 y0 x1 y0 x1 y1 x0 y1 x0 y0`. RGB values are in 0–1 (converted from 0–255).
- **Coordinates** — Row 0 is the top of the maze, column 0 is the left. In the graph:
  - `x0 = c * cell_size`, `x1 = (c+1) * cell_size`
  - `y0 = (H - r - 1) * cell_size`, `y1 = (H - r) * cell_size`
  So the maze's top row has the largest y in the graph.
- **Colors (defaults, RGB 0–255):**
  - Wall `#`: 0 0 0 (black)  
  - Open `.`: 255 255 255 (white)  
  - Start `S`: 0 200 0 (green)  
  - End `E`: 200 0 0 (red)  
  - Path `*`: 0 90 255 (blue)
- **Grid lines** — If gridlines are enabled, each cell boundary is drawn with `newline color 0.6 0.6 0.6 pts ...`.
- **Labels** — Row/column indices (when numbering is on) are drawn with `newstring` at computed positions; step is controlled by `grid_spacing` or `all_numbers`.

## Project Layout

- **mazechart** — C++ program that reads a maze file and prints JGraph to stdout. Implemented in `src/` and `include/` (one source file per symbol: wall, open, start, end, path).
- **maze_gen** — C program that generates a random ASCII maze; source: `maze_gen.c`.
- **scripts/convert.sh** — Runs `mazechart` on a maze file, pipes to `jgraph -P`, then converts PostScript to `.ps`, `.pdf`, or `.png`/`.jpg` (needs `ps2pdf` or ImageMagick for PDF/PNG/JPG).
- **scripts/make_maze.sh** — Runs `maze_gen` with given width/height, then `convert.sh` to produce a maze file and a PDF.

## Requirements

- **jgraph** — Required to turn `.jgr` into PostScript. Not in Homebrew on macOS; see **JGRAPH.md** for building from source and installing. Linux: `sudo apt-get install jgraph`.
- **Ghostscript** — For PDF output (`ps2pdf`). Install with `brew install ghostscript` (macOS) or `apt-get install ghostscript` (Linux).
- **ImageMagick** — Optional; for PNG/JPG output (`convert`). Install with `brew install imagemagick` or `apt-get install imagemagick`.

## How to Run (Summary)

| Goal | Command |
|------|--------|
| Render maze → PDF | `./scripts/convert.sh <maze.txt> cell_size 0.25 output.pdf` |
| Render maze → .jgr only | `./mazechart <maze.txt> [options] > out.jgr` |
| .jgr → PDF | `jgraph -P out.jgr > out.ps && ps2pdf out.ps out.pdf` |
| Generate random maze + PDF | `./scripts/make_maze.sh <width> <height> [output.pdf]` |
| Generate maze to file | `./maze_gen <width> <height> output.txt` |

All commands above are run from the project root (where `mazechart`, `maze_gen`, and `scripts/` live).
