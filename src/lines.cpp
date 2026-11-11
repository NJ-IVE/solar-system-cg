#include "lines.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>

void lineDDA(Canvas& cv, Point a, Point b, Color col) {
    int dx = b.x - a.x, dy = b.y - a.y;
    int steps = std::max(std::abs(dx), std::abs(dy));   // number of pixels on the longer axis
    if (steps == 0) { cv.setPixel(a.x, a.y, col); return; }
    float xInc = dx / (float)steps, yInc = dy / (float)steps;
    float x = a.x, y = a.y;
    for (int i = 0; i <= steps; i++) {
        cv.setPixel((int)std::lround(x), (int)std::lround(y), col);
        x += xInc; y += yInc;
    }
}

void lineBresenham(Canvas& cv, Point a, Point b, Color col) {
    int dx = std::abs(b.x - a.x), dy = -std::abs(b.y - a.y);
    int sx = a.x < b.x ? 1 : -1, sy = a.y < b.y ? 1 : -1;   // works in all 8 directions
    int err = dx + dy;                                       // integer error term
    int x = a.x, y = a.y;
    while (true) {
        cv.setPixel(x, y, col);
        if (x == b.x && y == b.y) break;
        int e2 = 2 * err;
        if (e2 >= dy) { err += dy; x += sx; }   // time to step in x
        if (e2 <= dx) { err += dx; y += sy; }   // time to step in y
    }
}

static int regionCode(double x, double y, int xmin, int ymin, int xmax, int ymax) {
    int code = 0;
    if (x < xmin) code |= 1; else if (x > xmax) code |= 2;   // left / right
    if (y < ymin) code |= 4; else if (y > ymax) code |= 8;   // above / below
    return code;
}

bool clipLine(Point& a, Point& b, int xmin, int ymin, int xmax, int ymax) {
    double x0 = a.x, y0 = a.y, x1 = b.x, y1 = b.y;
    int c0 = regionCode(x0, y0, xmin, ymin, xmax, ymax);
    int c1 = regionCode(x1, y1, xmin, ymin, xmax, ymax);
    while (true) {
        if ((c0 | c1) == 0) {                       // both inside: accept
            a = {(int)std::lround(x0), (int)std::lround(y0)};
            b = {(int)std::lround(x1), (int)std::lround(y1)};
            return true;
        }
        if (c0 & c1) return false;                  // both outside on the same side: reject
        int out = c0 ? c0 : c1;                     // pick an endpoint that is outside
        double x, y;
        if (out & 8)      { x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0); y = ymax; }
        else if (out & 4) { x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0); y = ymin; }
        else if (out & 2) { y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0); x = xmax; }
        else              { y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0); x = xmin; }
        if (out == c0) { x0 = x; y0 = y; c0 = regionCode(x0, y0, xmin, ymin, xmax, ymax); }
        else           { x1 = x; y1 = y; c1 = regionCode(x1, y1, xmin, ymin, xmax, ymax); }
    }
}
