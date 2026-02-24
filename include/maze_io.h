#ifndef MAZE_IO_H
#define MAZE_IO_H

#include <string>
#include <vector>

/* Read maze from file. Each line becomes a row; chars allowed: # . S E * and unknown (warned).
   Returns grid of rows (each row is a string). Empty file or invalid rectangle => empty grid. */
std::vector<std::string> read_maze(const std::string& path);

/* Validate that grid is rectangular (all rows same length). Return true if valid. */
bool validate_rectangle(const std::vector<std::string>& grid);

#endif /* MAZE_IO_H */
