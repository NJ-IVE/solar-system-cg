#include "scene_parts.h"
#include "lines.h"
#include "color.h"
#include <random>

void drawStarfield(Canvas& cv, int count) {
    std::mt19937 rng(42);   // fixed seed = same sky every run
    std::uniform_int_distribution<int> rx(0, cv.width() - 1), ry(0, cv.height() - 1);
    std::uniform_real_distribution<float> hue(0.0f, 360.0f), sat(0.0f, 0.25f), bright(0.3f, 1.0f);
    for (int i = 0; i < count; i++) {
        int x = rx(rng), y = ry(rng);
        Color c = hsvToRgb(hue(rng), sat(rng), bright(rng));   // nearly white, slight tint
        cv.setPixel(x, y, c);
        if (i % 15 == 0) {                                      // every 15th star is a bigger "+"
            cv.setPixel(x + 1, y, c); cv.setPixel(x - 1, y, c);
            cv.setPixel(x, y + 1, c); cv.setPixel(x, y - 1, c);
        }
    }
}

void drawMeteors(Canvas& cv) {
    const int xmin = 20, ymin = 20, xmax = cv.width() - 21, ymax = cv.height() - 21;
    Color frame{60, 60, 80};                                    // the viewport frame
    lineBresenham(cv, {xmin, ymin}, {xmax, ymin}, frame);
    lineBresenham(cv, {xmax, ymin}, {xmax, ymax}, frame);
    lineBresenham(cv, {xmax, ymax}, {xmin, ymax}, frame);
    lineBresenham(cv, {xmin, ymax}, {xmin, ymin}, frame);
    Point starts[] = {{260, -40}, {520, 60}, {720, 10}, {200, 140}, {90, 40}};
    for (Point s : starts) {
        for (int k = 0; k < 3; k++) {                           // 3 strands per meteor, fading
            Point a{s.x + k, s.y}, b{s.x - 140 + k, s.y + 110};
            Color c = hsvToRgb(30.0f, 0.4f - 0.1f * k, 1.0f - 0.3f * k);
            if (clipLine(a, b, xmin, ymin, xmax, ymax)) lineBresenham(cv, a, b, c);
        }
    }
}
