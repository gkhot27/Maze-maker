/*
 * Handles only the '#' (wall) character.
 * Color: 0 0 0 (black).
 */
#include "symbol_wall.h"
#include "jgraph_util.h"

void render_wall(std::ostream& out, double x0, double y0, double x1, double y1) {
    float r, g, b;
    rgb255_to_float(0, 0, 0, r, g, b);
    emit_box(out, x0, y0, x1, y1, r, g, b);
}
