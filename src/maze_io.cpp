#include "maze_io.h"
#include <fstream>
#include <iostream>

std::vector<std::string> read_maze(const std::string& path) {
    std::vector<std::string> grid;
    std::ifstream f(path.c_str());
    if (!f) {
        return grid;
    }
    std::string line;
    while (std::getline(f, line)) {
        /* strip trailing \r if present */
        if (!line.empty() && line[line.size() - 1] == '\r') {
            line.resize(line.size() - 1);
        }
        grid.push_back(line);
    }
    return grid;
}

bool validate_rectangle(const std::vector<std::string>& grid) {
    if (grid.empty()) return false;
    size_t w = grid[0].size();
    for (size_t i = 1; i < grid.size(); i++) {
        if (grid[i].size() != w) return false;
    }
    return true;
}
