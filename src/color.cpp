#include "color.h"
#include <algorithm>
#include <cmath>

Color hsvToRgb(float h, float s, float v) {
    float c = v * s;                                         // chroma
    float hp = h / 60.0f;                                    // which 60-degree sector
    float x = c * (1 - std::fabs(std::fmod(hp, 2.0f) - 1));
    float r = 0, g = 0, b = 0;
    if      (hp < 1) { r = c; g = x; }
    else if (hp < 2) { r = x; g = c; }
    else if (hp < 3) { g = c; b = x; }
    else if (hp < 4) { g = x; b = c; }
    else if (hp < 5) { r = x; b = c; }
    else             { r = c; b = x; }
    float m = v - c;                                         // lift to the right brightness
    return { (uint8_t)((r + m) * 255 + 0.5f), (uint8_t)((g + m) * 255 + 0.5f), (uint8_t)((b + m) * 255 + 0.5f) };
}

void rgbToHsv(Color c, float& h, float& s, float& v) {
    float r = c.r / 255.0f, g = c.g / 255.0f, b = c.b / 255.0f;
    float mx = std::max({r, g, b}), mn = std::min({r, g, b}), d = mx - mn;
    v = mx;
    s = (mx == 0) ? 0 : d / mx;
    if (d == 0)       h = 0;
    else if (mx == r) h = 60 * std::fmod((g - b) / d, 6.0f);
    else if (mx == g) h = 60 * ((b - r) / d + 2);
    else              h = 60 * ((r - g) / d + 4);
    if (h < 0) h += 360;
}
