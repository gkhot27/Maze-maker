#ifndef JGRAPH_UTIL_H
#define JGRAPH_UTIL_H

#include <iostream>

/* Convert RGB 0-255 to float 0-1 for jgraph fill. */
void rgb255_to_float(int r, int g, int b, float& out_r, float& out_g, float& out_b);

/* Emit jgraph filled box: pts x0 y0 x1 y0 x1 y1 x0 y1 x0 y0 marktype none fill r g b */
void emit_box(std::ostream& out, double x0, double y0, double x1, double y1,
              float r, float g, float b);

/* Emit jgraph line from (x0,y0) to (x1,y1). */
void emit_line(std::ostream& out, double x0, double y0, double x1, double y1);

/* Emit jgraph text label at (x, y). */
void emit_text(std::ostream& out, double x, double y, const std::string& label);

#endif /* JGRAPH_UTIL_H */
