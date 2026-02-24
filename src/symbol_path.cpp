/*
 * Handles only the '*' (solution path) character.
 * Color: 0 90 255 (blue).
 */
#include "symbol_path.h"
#include "jgraph_util.h"

void render_path(std::ostream& out, double x0, double y0, double x1, double y1) {
    float r, g, b;
    rgb255_to_float(0, 90, 255, r, g, b);
    emit_box(out, x0, y0, x1, y1, r, g, b);
}
