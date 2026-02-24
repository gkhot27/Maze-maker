/*
 * Handles only the 'E' (exit/end) character.
 * Color: 200 0 0 (red).
 */
#include "symbol_end.h"
#include "jgraph_util.h"

void render_end(std::ostream& out, double x0, double y0, double x1, double y1) {
    float r, g, b;
    rgb255_to_float(200, 0, 0, r, g, b);
    emit_box(out, x0, y0, x1, y1, r, g, b);
}
