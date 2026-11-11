#include "canvas.h"
#include "curves.h"
#include <vector>

int main() {
    Canvas cv(500, 400, {0, 0, 0});
    std::vector<Point> ctrl{{40, 350}, {120, 40}, {380, 40}, {460, 350}};
    drawPath(cv, ctrl, {90, 90, 90});                       // control polygon in grey
    auto curve = bezier(ctrl, 100);
    for (const Point& p : curve) cv.setPixel(p.x, p.y, {255, 255, 255});  // dots: visible tonight
    drawPath(cv, curve, {255, 255, 255});                   // solid once A's lines are merged
    cv.savePPM("out/test_curves.ppm");
}
