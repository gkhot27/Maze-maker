#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <string>
#include <vector>
#include "args.h"

/* Output jgraph header (newgraph, bounds, etc.) and then render grid using opts.
   Grid: H rows, each row W chars. Dispatches to symbol renderers per char.
   Unknown chars rendered as open and trigger a one-time warning. */
void render_maze(std::ostream& out, const std::vector<std::string>& grid, const Options& opts);

#endif /* RENDERER_H */
