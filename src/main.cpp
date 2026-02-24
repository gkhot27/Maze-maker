#include "args.h"
#include "maze_io.h"
#include "renderer.h"
#include <iostream>
#include <cstdio>

int main(int argc, char* argv[]) {
    Options opts;
    std::vector<std::string> positional;
    parse_args(argc, argv, opts, positional);

    if (positional.empty()) {
        fprintf(stderr, "usage: mazechart <maze.txt> [options]\n");
        fprintf(stderr, "  options: cell_size X, no_gridlines, grid_spacing X, no_numbering, all_numbers\n");
        return 1;
    }

    std::string path = positional[0];
    std::vector<std::string> grid = read_maze(path);
    if (grid.empty()) {
        fprintf(stderr, "mazechart: could not read maze file or file empty: %s\n", path.c_str());
        return 1;
    }
    if (!validate_rectangle(grid)) {
        fprintf(stderr, "mazechart: maze is not rectangular: %s\n", path.c_str());
        return 1;
    }

    render_maze(std::cout, grid, opts);
    return 0;
}
