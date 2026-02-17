#include <stdlib.h>

#define MAX_POINTS 1024

// points buffer format: [x0, y0, x1, y1, x2, y2, ...]
int make_path(
    int x1, int y1,
    int x2, int y2,
    int *out_points
) {
    int count = 0;

    int x = x1;
    int y = y1;

    // horizontal first
    while (x != x2 && count < MAX_POINTS) {
        out_points[count * 2]     = x;
        out_points[count * 2 + 1] = y;
        count++;

        if (x < x2) x++;
        else x--;
    }

    // then vertical
    while (y != y2 && count < MAX_POINTS) {
        out_points[count * 2]     = x;
        out_points[count * 2 + 1] = y;
        count++;

        if (y < y2) y++;
        else y--;
    }

    // final point
    out_points[count * 2]     = x2;
    out_points[count * 2 + 1] = y2;
    count++;

    return count;
}
//Hectra-32