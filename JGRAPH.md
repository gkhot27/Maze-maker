# Jgraph

Maze-Maker outputs `.jgr` (JGraph) format. To get PDF or images you need [Jgraph](https://web.eecs.utk.edu/~jplank/plank/jgraph/jgraph.html).

## Install

**macOS:** Not in Homebrew. Build from source:

```bash
curl -LO http://web.eecs.utk.edu/~jplank/plank/jgraph/2024-02-15-Jgraph.tar
tar xf 2024-02-15-Jgraph.tar
cd jgraph/jgraph
make
sudo cp jgraph /usr/local/bin/
```

Use the **inner** `jgraph/jgraph/` directory (the executable is the file `./jgraph` there). Do not run `make` in the top-level `jgraph/` folder. If the compiler complains: `make CC="gcc -ansi -pedantic -Wno-implicit-int"`.

**Linux:** `sudo apt-get install jgraph`

## Test

```bash
./mazechart examples/maze1.txt cell_size 0.25 > out.jgr
jgraph -P out.jgr > out.ps
ps2pdf out.ps out.pdf
```

Or: `./scripts/convert.sh examples/maze1.txt cell_size 0.35 output.pdf` (needs jgraph and ghostscript or ImageMagick for PNG/JPG).

## Syntax used

- Filled cells: `newcurve poly pcfill r g b pts x0 y0 x1 y0 x1 y1 x0 y1 x0 y0`
- Grid lines: `newline color 0.6 0.6 0.6 pts x0 y0 x1 y1`
- Coordinates: `xaxis` / `yaxis` min/max with `nodraw`
