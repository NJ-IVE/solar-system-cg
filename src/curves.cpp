#include "curves.h"
#include "lines.h"
#include <cmath>

std::vector<Point> bezier(const std::vector<Point>& ctrl, int segments) {
    std::vector<Point> out;
    if (ctrl.empty()) return out;
    for (int i = 0; i <= segments; i++) {
        double t = (double)i / segments;                     // 0 ... 1
        std::vector<double> xs, ys;
        for (const Point& p : ctrl) { xs.push_back(p.x); ys.push_back(p.y); }
        for (size_t k = ctrl.size() - 1; k > 0; k--)        // de Casteljau: shrink by one each round
            for (size_t j = 0; j < k; j++) {
                xs[j] = (1 - t) * xs[j] + t * xs[j + 1];
                ys[j] = (1 - t) * ys[j] + t * ys[j + 1];
            }
        out.push_back({(int)std::lround(xs[0]), (int)std::lround(ys[0])});
    }
    return out;
}

void drawPath(Canvas& cv, const std::vector<Point>& pts, Color col) {
    for (size_t i = 0; i + 1 < pts.size(); i++) lineBresenham(cv, pts[i], pts[i + 1], col);
}
