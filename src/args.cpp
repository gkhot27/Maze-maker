#include "args.h"
#include <cstdlib>
#include <cstring>

static void set_defaults(Options& opts) {
    opts.cell_size = 0.20;
    opts.gridlines = true;
    opts.grid_spacing = 10;
    opts.numbering = true;
    opts.all_numbers = false;
}

void parse_args(int argc, char* argv[], Options& opts, std::vector<std::string>& positional) {
    set_defaults(opts);
    positional.clear();

    for (int i = 1; i < argc; i++) {
        std::string arg(argv[i]);
        if (arg == "cell_size" && i + 1 < argc) {
            opts.cell_size = atof(argv[++i]);
        } else if (arg == "no_gridlines") {
            opts.gridlines = false;
        } else if (arg == "grid_spacing" && i + 1 < argc) {
            opts.grid_spacing = atoi(argv[++i]);
        } else if (arg == "no_numbering") {
            opts.numbering = false;
        } else if (arg == "all_numbers") {
            opts.all_numbers = true;
        } else {
            positional.push_back(arg);
        }
    }
}
