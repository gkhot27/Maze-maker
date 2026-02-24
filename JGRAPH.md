# Using MazeChart with Jgraph

MazeChart outputs **jgraph** (`.jgr`) format. To view the maze as PDF or an image you need [Jgraph](https://web.eecs.utk.edu/~jplank/plank/jgraph/jgraph.html) (by James S. Plank).

## Install Jgraph

**macOS:** Jgraph is **not** in Homebrew (only `igraph` and `jgrasp` are). Build from source:

```bash
curl -LO http://web.eecs.utk.edu/~jplank/plank/jgraph/2024-02-15-Jgraph.tar
tar xf 2024-02-15-Jgraph.tar
cd jgraph/jgraph    # build is in the inner jgraph directory, not the top level
make
# Put the binary on your PATH (the executable is ./jgraph in this directory)
sudo make install
# or:  sudo cp jgraph /usr/local/bin/
```

**Important:** Run `make` and `sudo make install` from **inside** `jgraph/jgraph/`. If you run `cp jgraph /usr/local/bin/` from the parent `jgraph/` folder, `jgraph` is the **directory**, so you get "jgraph is a directory (not copied)". The executable is the **file** `./jgraph` in `jgraph/jgraph/`.

Do **not** run `make` in the top-level `jgraph/` folder—that Makefile only copies example files from the author’s server and will fail. Use `jgraph/jgraph/` and copy the **file** `jgraph` from there.

If your C compiler complains, try: `make CC="gcc -ansi -pedantic -Wno-implicit-int"`

**Linux (Debian/Ubuntu):**
```bash
sudo apt-get install jgraph
```

**From source (any OS):** [Download the tar](http://web.eecs.utk.edu/~jplank/plank/jgraph/2024-02-15-Jgraph.tar), then `tar xf ...`, `cd jgraph`, `make`.

## Quick test

```bash
make
./mazechart examples/maze1.txt cell_size 0.25 > out.jgr
jgraph -P out.jgr > out.ps
ps2pdf out.ps out.pdf
open out.pdf    # macOS
```

## Using the convert script

From the project root:

```bash
./scripts/convert.sh examples/maze1.txt cell_size 0.35 output.pdf
```

This runs `mazechart` → `jgraph -P` → `ps2pdf` (or `convert` for PNG/JPG). You need **jgraph** and either **ghostscript** (for PDF) or **ImageMagick** (for PNG/JPG).

## Jgraph syntax used

- **Filled cells:** `newcurve poly pcfill r g b pts x0 y0 x1 y0 x1 y1 x0 y1 x0 y0` (closed polygon fill, RGB 0–1).
- **Grid lines:** `newline color 0.6 0.6 0.6 pts x0 y0 x1 y1`.
- **Coordinates:** Set by `xaxis min/max` and `yaxis min/max` with `nodraw` so only the maze is drawn.
