/*
 * Handles only the '.' (open path) character.
 * Color: 255 255 255 (white).
 */
#include "symbol_open.h"
#include "jgraph_util.h"

void render_open(std::ostream& out, double x0, double y0, double x1, double y1) {
    float r, g, b;
    rgb255_to_float(255, 255, 255, r, g, b);
    emit_box(out, x0, y0, x1, y1, r, g, b);
}
