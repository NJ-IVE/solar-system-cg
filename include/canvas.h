#pragma once
#include <cstdint>
#include <string>
#include <vector>

struct Color { uint8_t r, g, b; };
struct Point { int x, y; };
inline bool operator==(Color a, Color b) { return a.r == b.r && a.g == b.g && a.b == b.b; }

class Canvas {
public:
    Canvas(int width, int height, Color bg);
    void setPixel(int x, int y, Color c);   // ignores pixels outside the image
    Color getPixel(int x, int y) const;
    int width() const { return w; }
    int height() const { return h; }
    bool savePPM(const std::string& path) const;
private:
    int w, h;
    std::vector<Color> pixels;              // row by row, top-left first
};
