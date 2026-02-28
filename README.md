# Maze-Maker

Visualizes ASCII mazes as JGraph drawings and renders them to PDF or images. Use a pre-made maze file or generate a random maze with the included generator. There are premade pdfs if you want to run without compiling

**Repository contents:** Source code only — no precompiled binaries. Build `mazechart` and `maze_gen` with `make`; install jgraph from source per [JGRAPH.md](JGRAPH.md).

## Compilation

**Requirements:** `g++`, `gcc`, `jgraph` (in PATH), Ghostscript (`ps2pdf`). Optional: ImageMagick (`convert`) for JPG. See [JGRAPH.md](JGRAPH.md) for jgraph.

```bash
make
```

Builds **mazechart** (C++) and **maze_gen** (C), then creates five sample PDFs in `output/`.

- Build only: `make mazechart maze_gen`
- Regenerate outputs: `make outputs`
- Clean: `make clean`

## Program Description

**mazechart** — Reads a maze file and prints JGraph to stdout. Pipe to `jgraph` and `ps2pdf` to get PDF.

```text
./mazechart <maze.txt> [options]
```

Options: `cell_size X`, `no_gridlines`, `grid_spacing X`, `no_numbering`, `all_numbers`.

**maze_gen** — Generates a random perfect maze (S at top-left, E at bottom-right).

```text
./maze_gen <width> <height> [output.txt]
```

**Maze characters:** `#` wall, `.` open, `S` start, `E` exit, `*` solution path.

## Examples

**Render maze to PDF (script):**
```bash
./scripts/convert.sh examples/maze1.txt cell_size 0.25 out.pdf
```

**Manual pipeline:**
```bash
./mazechart examples/maze1.txt cell_size 0.25 > out.jgr
jgraph -P out.jgr > out.ps
ps2pdf out.ps out.pdf
```

**Generate and render:**
```bash
./maze_gen 15 20 my_maze.txt
./scripts/convert.sh my_maze.txt cell_size 0.25 my_maze.pdf
```
Or: `./scripts/make_maze.sh 15 20` → creates `maze_15x20.txt` and `maze_15x20.pdf`.

**Sample outputs from `make`:** `output/example1.pdf`, `output/example2.pdf`, `output/small.pdf`, `output/medium.pdf`, `output/large.pdf`.

**Individual peices of jgraphs have there seperate folders (all walls follow same process):**
-black_wall
-white_wall
-green-wall


**Example outputs (links open in repo) (Once you clone the repo, delete the output directory and run make, output folder will automatically created and open pdfs.):**

- **Example 1** [output/example1.pdf](output/example1.pdf)
  
  ./mazechart examples/maze1.txt cell_size 0.25 > output/example1.jgr
  jgraph -P output/example1.jgr > output/example1.ps
  ps2pdf output/example1.ps output/example1.pdf

  https://github.com/gkhot27/Maze-Maker/blob/main/output/example1.pdf

- **Example 2** [output/example2.pdf](output/example2.pdf)
 
  ./mazechart examples/maze1.txt cell_size 0.28 no_gridlines > output/example2.jgr
  jgraph -P output/example2.jgr > output/example2.ps
  ps2pdf output/example2.ps output/example2.pdf

  https://github.com/gkhot27/Maze-Maker/blob/main/output/example2.pdf

**Example 3** [output/small.pdf](output/small.pdf)

  ./maze_gen 5 5 output/small_maze.txt
  ./mazechart output/small_maze.txt cell_size 0.4 > output/small.jgr
  jgraph -P output/small.jgr > output/small.ps
  ps2pdf output/small.ps output/small.pdf

https://github.com/gkhot27/Maze-Maker/blob/main/output/small.pdf

**Example 4** [output/medium.pdf](output/medium.pdf)

  ./maze_gen 10 10 output/medium_maze.txt
  ./mazechart output/medium_maze.txt cell_size 0.3 > output/medium.jgr
  jgraph -P output/medium.jgr > output/medium.ps
  ps2pdf output/medium.ps output/medium.pdf

https://github.com/gkhot27/Maze-Maker/blob/main/output/medium.pdf

**Example 5** [output/large.pdf](output/large.pdf)

  ./maze_gen 15 20 output/large_maze.txt
  ./mazechart output/large_maze.txt cell_size 0.22 > output/large.jgr
  jgraph -P output/large.jgr > output/large.ps
  ps2pdf output/large.ps output/large.pdf

https://github.com/gkhot27/Maze-Maker/blob/main/output/large.pdf



