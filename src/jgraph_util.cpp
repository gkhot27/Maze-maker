#include "jgraph_util.h"
#include <iomanip>

void rgb255_to_float(int r, int g, int b, float& out_r, float& out_g, float& out_b) {
    out_r = r / 255.0f;
    out_g = g / 255.0f;
    out_b = b / 255.0f;
}

void emit_box(std::ostream& out, double x0, double y0, double x1, double y1,
              float r, float g, float b) {
    /* jgraph: poly = closed polygon, pcfill = RGB fill (0-1) */
    out << "newcurve poly pcfill " << r << " " << g << " " << b << " pts " << std::fixed
        << x0 << " " << y0 << " "
        << x1 << " " << y0 << " "
        << x1 << " " << y1 << " "
        << x0 << " " << y1 << " "
        << x0 << " " << y0 << "\n";
}

void emit_line(std::ostream& out, double x0, double y0, double x1, double y1) {
    /* newline = newcurve marktype none linetype solid; gray grid lines */
    out << "newline color 0.6 0.6 0.6 pts " << std::fixed << x0 << " " << y0 << " " << x1 << " " << y1 << "\n";
}

void emit_text(std::ostream& out, double x, double y, const std::string& label) {
    out << "newstring hjc vjc x " << std::fixed << x << " y " << y << " fontsize 8 : " << label << "\n";
}
