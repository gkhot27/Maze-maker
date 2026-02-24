#ifndef ARGS_H
#define ARGS_H

#include <string>
#include <vector>

struct Options {
    double cell_size;      /* default 0.20 */
    bool gridlines;        /* default true */
    int grid_spacing;      /* default 10, labels every N */
    bool numbering;       /* default true */
    bool all_numbers;     /* default false; if true, label every cell */
};

/* Parse argv; last occurrence of each option wins. Returns options and non-option args (e.g. maze file). */
void parse_args(int argc, char* argv[], Options& opts, std::vector<std::string>& positional);

#endif /* ARGS_H */
