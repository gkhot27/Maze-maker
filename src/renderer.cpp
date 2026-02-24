#include "renderer.h"
#include "args.h"
#include "jgraph_util.h"
#include "symbol_wall.h"
#include "symbol_open.h"
#include "symbol_start.h"
#include "symbol_end.h"
#include "symbol_path.h"
#include <iomanip>
#include <sstream>
#include <cstdio>

static bool warned_unknown = false;

static void warn_unknown_once(char ch) {
    if (!warned_unknown) {
        fprintf(stderr, "mazechart: unknown character '%c' (0x%02x), treating as open\n", ch, (unsigned char)ch);
        warned_unknown = true;
    }
}

static void emit_jgraph_header(std::ostream& out, int H, int W, double cell_size) {
    double width = W * cell_size;
    double height = H * cell_size;
    double margin = cell_size; /* room for axis labels */
    /* jgraph uses xaxis/yaxis min/max to define coordinate system; nodraw hides axes */
    out << "newgraph\n";
    out << "xaxis min " << std::fixed << -margin << " max " << width + margin << " size 5 nodraw\n";
    out << "yaxis min " << -margin << " max " << height + margin << " size 5 nodraw\n";
}

void render_maze(std::ostream& out, const std::vector<std::string>& grid, const Options& opts) {
    int H = static_cast<int>(grid.size());
    if (H == 0) return;
    int W = static_cast<int>(grid[0].size());
    double cs = opts.cell_size;

    emit_jgraph_header(out, H, W, cs);

    /* Draw each cell: row r (0 at top), col c (0 at left)
       x0 = c * cell_size, x1 = (c+1) * cell_size
       y1 = (H - r) * cell_size, y0 = (H - r - 1) * cell_size
    */
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < W; c++) {
            double x0 = c * cs;
            double x1 = (c + 1) * cs;
            double y1 = (H - r) * cs;
            double y0 = (H - r - 1) * cs;
            char ch = (c < static_cast<int>(grid[r].size())) ? grid[r][c] : '.';
            switch (ch) {
                case '#': render_wall(out, x0, y0, x1, y1); break;
                case '.': render_open(out, x0, y0, x1, y1); break;
                case 'S': render_start(out, x0, y0, x1, y1); break;
                case 'E': render_end(out, x0, y0, x1, y1); break;
                case '*': render_path(out, x0, y0, x1, y1); break;
                default:
                    warn_unknown_once(ch);
                    render_open(out, x0, y0, x1, y1);
                    break;
            }
        }
    }

    /* Gridlines: vertical and horizontal at cell boundaries (y: 0 = bottom, H*cs = top) */
    if (opts.gridlines) {
        for (int c = 0; c <= W; c++) {
            double x = c * cs;
            emit_line(out, x, 0, x, H * cs);
        }
        for (int r = 0; r <= H; r++) {
            double y = r * cs;
            emit_line(out, 0, y, W * cs, y);
        }
    }

    /* Numbering: labels every grid_spacing (or every 1 if all_numbers) */
    if (opts.numbering) {
        int step = opts.all_numbers ? 1 : opts.grid_spacing;
        if (step < 1) step = 1;
        for (int c = 0; c < W; c += step) {
            double x = (c + 0.5) * cs;
            std::ostringstream oss;
            oss << c;
            emit_text(out, x, -0.5 * cs, oss.str());
        }
        for (int r = 0; r < H; r += step) {
            double y = (H - r - 0.5) * cs;
            std::ostringstream oss;
            oss << r;
            emit_text(out, -0.5 * cs, y, oss.str());
        }
    }
}
