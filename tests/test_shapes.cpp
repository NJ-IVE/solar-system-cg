#include "canvas.h"
#include "shapes.h"
#include "polygon.h"
#include <cmath>
#include <vector>

int main() {
    Canvas cv(600, 400, {0, 0, 0});
    circleMidpoint(cv, {120, 120}, 80, {255, 255, 255});            // outline
    circleMidpoint(cv, {120, 120}, 40, {255, 200, 0}, true);        // filled
    ellipseMidpoint(cv, {380, 120}, 180, 60, {100, 180, 255});      // outline
    ellipseMidpoint(cv, {380, 120}, 60, 25, {100, 180, 255}, true); // filled
    std::vector<Point> star;                                         // 5-point star
    for (int k = 0; k < 10; k++) {
        double t = -3.14159265 / 2 + k * 3.14159265 / 5;
        int r = (k % 2 == 0) ? 100 : 40;                             // outer, inner, outer...
        star.push_back({300 + (int)(r * std::cos(t)), 290 + (int)(r * std::sin(t))});
    }
    scanlineFill(cv, star, {255, 80, 80});
    cv.savePPM("out/test_shapes.ppm");
}
