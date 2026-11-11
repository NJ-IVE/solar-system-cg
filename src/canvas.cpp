#include "canvas.h"
#include <fstream>

Canvas::Canvas(int width, int height, Color bg)
    : w(width), h(height), pixels(width * height, bg) {}

void Canvas::setPixel(int x, int y, Color c) {
    if (x < 0 || y < 0 || x >= w || y >= h) return;
    pixels[y * w + x] = c;
}

Color Canvas::getPixel(int x, int y) const {
    if (x < 0 || y < 0 || x >= w || y >= h) return {0, 0, 0};
    return pixels[y * w + x];
}

// PPM = the simplest image format: a text header, then raw RGB bytes.
bool Canvas::savePPM(const std::string& path) const {
    std::ofstream f(path, std::ios::binary);
    if (!f) return false;
    f << "P6\n" << w << " " << h << "\n255\n";
    for (const Color& c : pixels) { f.put((char)c.r); f.put((char)c.g); f.put((char)c.b); }
    return true;
}
