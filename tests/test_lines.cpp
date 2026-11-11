#include "canvas.h"
#include "lines.h"
#include <cmath>

int main() {
    Canvas cv(400, 400, {0, 0, 0});
    for (int i = 0; i < 16; i++) {
        double t = i * 3.14159265 / 8;
        Point end{200 + (int)(180 * std::cos(t)), 200 + (int)(180 * std::sin(t))};
        if (i % 2 == 0) lineBresenham(cv, {200, 200}, end, {255, 255, 255});
        else            lineDDA(cv, {200, 200}, end, {255, 80, 80});
    }
    // Clipping check (Step 4): grey box = clip window, dim green = whole line, bright green = kept part
    Color grey{90, 90, 90};
    lineBresenham(cv, {100, 100}, {300, 100}, grey); lineBresenham(cv, {300, 100}, {300, 300}, grey);
    lineBresenham(cv, {300, 300}, {100, 300}, grey); lineBresenham(cv, {100, 300}, {100, 100}, grey);
    Point a{20, 380}, b{390, 250};
    lineBresenham(cv, a, b, {0, 90, 0});
    if (clipLine(a, b, 100, 100, 300, 300)) lineBresenham(cv, a, b, {0, 255, 0});
    cv.savePPM("out/test_lines.ppm");
}
