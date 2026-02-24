#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct {
    int r, c;
} Cell;

static int is_int_string(const char *s) {
    if (s == NULL || *s == '\0') return 0;
    // allow leading +/-
    if (*s == '+' || *s == '-') s++;
    if (*s == '\0') return 0;
    while (*s) {
        if (!isdigit((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}

static int read_int_prompt(const char *prompt, int *out) {
    char buf[256];
    printf("%s", prompt);
    fflush(stdout);
    if (!fgets(buf, sizeof(buf), stdin)) return 0;

    // strip newline
    buf[strcspn(buf, "\r\n")] = '\0';

    if (!is_int_string(buf)) return 0;
    *out = atoi(buf);
    return 1;
}

static void shuffle4(int a[4]) {
    // Fisher-Yates shuffle
    for (int i = 3; i > 0; --i) {
        int j = rand() % (i + 1);
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
}

// Maze is carved on a grid of "cells" (w x h).
// ASCII output grid has dimensions: (2*h + 1) rows, (2*w + 1) cols
// Start is at cell (0,0) -> ASCII (1,1)
// End   is at cell (h-1,w-1) -> ASCII (2*h-1, 2*w-1)

int main(int argc, char **argv) {
    int w = 0, h = 0;
    const int MIN_SIZE = 2;
    const int MAX_SIZE = 200; // keep memory/runtime reasonable

    // Parse from args if possible
    int ok_args = 0;
    if (argc >= 3 && is_int_string(argv[1]) && is_int_string(argv[2])) {
        w = atoi(argv[1]);
        h = atoi(argv[2]);
        ok_args = 1;
    }

    // If args missing/invalid or out of bounds, ask repeatedly
    while (!ok_args || w < MIN_SIZE || h < MIN_SIZE || w > MAX_SIZE || h > MAX_SIZE) {
        if (!ok_args) {
            printf("Usage: %s <width> <height> [outputfile]\n", argv[0]);
            printf("Width/height must be integers.\n");
        } else {
            printf("Invalid size. Width/height must be between %d and %d (cells).\n", MIN_SIZE, MAX_SIZE);
        }

        if (!read_int_prompt("Enter maze width (cells): ", &w)) {
            printf("Not a valid integer. Try again.\n\n");
            ok_args = 0;
            continue;
        }
        if (!read_int_prompt("Enter maze height (cells): ", &h)) {
            printf("Not a valid integer. Try again.\n\n");
            ok_args = 0;
            continue;
        }
        ok_args = 1;
    }

    // Output file if provided
    FILE *out = stdout;
    if (argc >= 4) {
        out = fopen(argv[3], "w");
        if (!out) {
            perror("Could not open output file; writing to stdout instead");
            out = stdout;
        }
    }

    srand((unsigned int)time(NULL));

    // visited array for DFS
    unsigned char *visited = (unsigned char *)calloc((size_t)w * (size_t)h, 1);
    if (!visited) {
        fprintf(stderr, "Memory allocation failed (visited).\n");
        if (out != stdout) fclose(out);
        return 1;
    }

    // ASCII grid
    int rows = 2 * h + 1;
    int cols = 2 * w + 1;
    char *grid = (char *)malloc((size_t)rows * (size_t)cols);
    if (!grid) {
        fprintf(stderr, "Memory allocation failed (grid).\n");
        free(visited);
        if (out != stdout) fclose(out);
        return 1;
    }

    // Fill with walls
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            grid[r * cols + c] = '#';
        }
    }

    // Carve out cell centers as open initially (.)
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            int ar = 2 * r + 1;
            int ac = 2 * c + 1;
            grid[ar * cols + ac] = '.';
        }
    }

    // Iterative DFS stack (perfect maze => always solvable)
    Cell *stack = (Cell *)malloc((size_t)w * (size_t)h * sizeof(Cell));
    if (!stack) {
        fprintf(stderr, "Memory allocation failed (stack).\n");
        free(grid);
        free(visited);
        if (out != stdout) fclose(out);
        return 1;
    }

    int top = 0;
    stack[top++] = (Cell){0, 0};
    visited[0] = 1;

    // Direction arrays: 0=up,1=right,2=down,3=left
    const int dr[4] = {-1, 0, 1, 0};
    const int dc[4] = {0, 1, 0, -1};

    while (top > 0) {
        Cell cur = stack[top - 1];

        int dirs[4] = {0, 1, 2, 3};
        shuffle4(dirs);

        int moved = 0;
        for (int i = 0; i < 4; i++) {
            int d = dirs[i];
            int nr = cur.r + dr[d];
            int nc = cur.c + dc[d];

            if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;

            int idx = nr * w + nc;
            if (visited[idx]) continue;

            // carve wall between cur and neighbor in ASCII grid
            int cur_ar = 2 * cur.r + 1;
            int cur_ac = 2 * cur.c + 1;
            int nbr_ar = 2 * nr + 1;
            int nbr_ac = 2 * nc + 1;

            int wall_r = (cur_ar + nbr_ar) / 2;
            int wall_c = (cur_ac + nbr_ac) / 2;
            grid[wall_r * cols + wall_c] = '.'; // open passage

            visited[idx] = 1;
            stack[top++] = (Cell){nr, nc};
            moved = 1;
            break;
        }

        if (!moved) {
            top--; // backtrack
        }
    }

    // Place S and E (guaranteed connected in a perfect maze)
    grid[1 * cols + 1] = 'S';
    grid[(rows - 2) * cols + (cols - 2)] = 'E';

    // Print the maze
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            fputc(grid[r * cols + c], out);
        }
        fputc('\n', out);
    }

    if (out != stdout) fclose(out);
    free(stack);
    free(grid);
    free(visited);
    return 0;
}