# Maze-Maker: build mazechart (C++) and maze_gen (C), then create sample outputs
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++98 -I include
TARGET = mazechart

SRCS = src/main.cpp src/args.cpp src/maze_io.cpp src/renderer.cpp \
       src/jgraph_util.cpp \
       src/symbol_wall.cpp src/symbol_open.cpp src/symbol_start.cpp \
       src/symbol_end.cpp src/symbol_path.cpp

OBJS = $(SRCS:.cpp=.o)

# Default: build both programs and create five sample outputs (PDF/JPG)
.PHONY: all clean outputs

all: $(TARGET) maze_gen outputs

# --- C++ maze renderer (reads maze file, prints JGraph to stdout)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)
	chmod +x $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# --- C maze generator
maze_gen: maze_gen.c
	gcc -Wall -Wextra -o maze_gen maze_gen.c
	chmod +x maze_gen

# --- Create at least five interesting JGraph outputs (PDF or JPG)
# Requires: jgraph in PATH, ps2pdf (Ghostscript), convert (ImageMagick)
outputs: $(TARGET) maze_gen
	@mkdir -p output
	@echo "Creating output/example1.pdf (example maze, default options)..."
	./scripts/convert.sh examples/maze1.txt cell_size 0.25 output/example1.pdf
	@echo "Creating output/example2.pdf (example maze, no gridlines)..."
	./scripts/convert.sh examples/maze1.txt cell_size 0.28 no_gridlines output/example2.pdf
	@echo "Creating output/small.pdf (5x5 generated maze)..."
	./maze_gen 5 5 output/small_maze.txt && ./scripts/convert.sh output/small_maze.txt cell_size 0.4 output/small.pdf
	@echo "Creating output/medium.pdf (10x10 generated maze)..."
	./maze_gen 10 10 output/medium_maze.txt && ./scripts/convert.sh output/medium_maze.txt cell_size 0.3 output/medium.pdf
	@echo "Creating output/large.pdf (15x20 generated maze)..."
	./maze_gen 15 20 output/large_maze.txt && ./scripts/convert.sh output/large_maze.txt cell_size 0.22 output/large.pdf
	@echo "Creating output/example1.jpg (example maze as JPG; requires ImageMagick)..."
	@if command -v convert >/dev/null 2>&1; then \
		./scripts/convert.sh examples/maze1.txt cell_size 0.25 output/example1.jpg; \
	else \
		echo "Skipping example1.jpg (convert not found); you have 5 PDFs in output/"; \
	fi
	@echo "Done. Outputs in output/: example1.pdf, example2.pdf, small.pdf, medium.pdf, large.pdf (and example1.jpg if convert installed)"

clean:
	rm -f $(OBJS) $(TARGET) maze_gen
	rm -rf output
