#include "scene_parts.h"
#include "curves.h"
#include "shapes.h"
#include "color.h"
#include <cstdlib>

void drawComet(Canvas& cv) {
    Point head{1000, 140};

    // 1. Dotted trajectory
    auto path = bezier({{-40, 420}, {300, 60}, {750, 40}, head}, 400);
    for (size_t i = 0; i < path.size(); i += 3) cv.setPixel(path[i].x, path[i].y, {130, 150, 190});

    // 2. Tail: curves from the head, bending up and right, away from the sun
    for (int k = 0; k < 7; k++) {
        Point end{1270, 10 + k * 18};
        Point bend{1110 + k * 5, 60 + k * 12};
        Color col = hsvToRgb(195.0f, 0.35f, 0.95f - 0.1f * std::abs(k - 3));  // middle strand brightest
        drawPath(cv, bezier({head, bend, end}, 40), col);
    }

    // 3. Nucleus with a soft glow
    circleMidpoint(cv, head, 12, hsvToRgb(200.0f, 0.4f, 0.45f), true);
    circleMidpoint(cv, head, 7, {235, 245, 255}, true);
}
