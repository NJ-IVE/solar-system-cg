#include "shapes.h"

// Horizontal line from x0 to x1 — used to fill shapes row by row.
static void hspan(Canvas& cv, int x0, int x1, int y, Color c) {
    for (int x = x0; x <= x1; x++) cv.setPixel(x, y, c);
}

void circleMidpoint(Canvas& cv, Point c, int r, Color col, bool filled) {
    int x = 0, y = r;
    int p = 1 - r;                                  // decision parameter
    while (x <= y) {                                // one octant; mirror the rest
        if (filled) {
            hspan(cv, c.x - x, c.x + x, c.y + y, col);
            hspan(cv, c.x - x, c.x + x, c.y - y, col);
            hspan(cv, c.x - y, c.x + y, c.y + x, col);
            hspan(cv, c.x - y, c.x + y, c.y - x, col);
        } else {
            cv.setPixel(c.x + x, c.y + y, col); cv.setPixel(c.x - x, c.y + y, col);
            cv.setPixel(c.x + x, c.y - y, col); cv.setPixel(c.x - x, c.y - y, col);
            cv.setPixel(c.x + y, c.y + x, col); cv.setPixel(c.x - y, c.y + x, col);
            cv.setPixel(c.x + y, c.y - x, col); cv.setPixel(c.x - y, c.y - x, col);
        }
        x++;
        if (p < 0) p += 2 * x + 1;                  // midpoint inside: keep y
        else { y--; p += 2 * (x - y) + 1; }         // midpoint outside: step y down
    }
}

void ellipseMidpoint(Canvas& cv, Point c, int rx, int ry, Color col, bool filled) {
    auto plot4 = [&](int x, int y) {                // mirror into 4 quadrants
        if (filled) {
            hspan(cv, c.x - x, c.x + x, c.y + y, col);
            hspan(cv, c.x - x, c.x + x, c.y - y, col);
        } else {
            cv.setPixel(c.x + x, c.y + y, col); cv.setPixel(c.x - x, c.y + y, col);
            cv.setPixel(c.x + x, c.y - y, col); cv.setPixel(c.x - x, c.y - y, col);
        }
    };
    double rx2 = (double)rx * rx, ry2 = (double)ry * ry;
    int x = 0, y = ry;
    double px = 0, py = 2 * rx2 * y;
    // Region 1: the curve is flatter than 45 degrees, so step in x
    double p = ry2 - rx2 * ry + 0.25 * rx2;
    while (px < py) {
        plot4(x, y);
        x++; px += 2 * ry2;
        if (p < 0) p += ry2 + px;
        else { y--; py -= 2 * rx2; p += ry2 + px - py; }
    }
    // Region 2: the curve is steeper than 45 degrees, so step in y
    p = ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1.0) * (y - 1.0) - rx2 * ry2;
    while (y >= 0) {
        plot4(x, y);
        y--; py -= 2 * rx2;
        if (p > 0) p += rx2 - py;
        else { x++; px += 2 * ry2; p += rx2 - py + px; }
    }
}
