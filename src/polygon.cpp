#include "polygon.h"
#include "lines.h"
#include <algorithm>
#include <cmath>

void drawPolygon(Canvas& cv, const std::vector<Point>& pts, Color col) {
    for (size_t i = 0; i < pts.size(); i++)          // join each vertex to the next, last to first
        lineBresenham(cv, pts[i], pts[(i + 1) % pts.size()], col);
}

void scanlineFill(Canvas& cv, const std::vector<Point>& pts, Color col) {
    if (pts.size() < 3) return;
    int ymin = pts[0].y, ymax = pts[0].y;
    for (const Point& p : pts) { ymin = std::min(ymin, p.y); ymax = std::max(ymax, p.y); }
    for (int y = ymin; y <= ymax; y++) {
        std::vector<int> xs;                         // where edges cross this row
        for (size_t i = 0; i < pts.size(); i++) {
            Point a = pts[i], b = pts[(i + 1) % pts.size()];
            if (a.y == b.y) continue;                // skip horizontal edges
            if (a.y > b.y) std::swap(a, b);          // make a the top end
            if (y < a.y || y >= b.y) continue;       // count top vertex, not bottom
            double x = a.x + (double)(y - a.y) * (b.x - a.x) / (b.y - a.y);
            xs.push_back((int)std::lround(x));
        }
        std::sort(xs.begin(), xs.end());
        for (size_t k = 0; k + 1 < xs.size(); k += 2)
            for (int x = xs[k]; x <= xs[k + 1]; x++) cv.setPixel(x, y, col);
    }
}

// Stretch goal (week 5): fills outward from a seed until it hits the boundary colour.
// Uses an explicit stack, not recursion, so big areas don't crash.
void boundaryFill(Canvas& cv, Point seed, Color fill, Color boundary) {
    std::vector<Point> stack{seed};
    while (!stack.empty()) {
        Point p = stack.back(); stack.pop_back();
        if (p.x < 0 || p.y < 0 || p.x >= cv.width() || p.y >= cv.height()) continue;
        Color c = cv.getPixel(p.x, p.y);
        if (c == boundary || c == fill) continue;
        cv.setPixel(p.x, p.y, fill);
        stack.push_back({p.x + 1, p.y}); stack.push_back({p.x - 1, p.y});
        stack.push_back({p.x, p.y + 1}); stack.push_back({p.x, p.y - 1});
    }
}
