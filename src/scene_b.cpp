#include "scene_parts.h"
#include "shapes.h"
#include "polygon.h"
#include "color.h"
#include <cmath>
#include <random>
#include <string>
#include <vector>

struct Planet { std::string name; int rx; int r; float hue, sat, val, angleDeg; };

//        name       orbit  size  hue   sat    val    angle
static const std::vector<Planet> PLANETS = {
    {"Mercury", 110,  6,  30, 0.20f, 0.70f,  20},
    {"Venus",   160, 10,  40, 0.50f, 0.95f, 150},
    {"Earth",   215, 11, 210, 0.70f, 0.90f,  60},
    {"Mars",    275,  8,  10, 0.80f, 0.85f, 200},
    {"Jupiter", 380, 26,  30, 0.45f, 0.90f, 330},
    {"Saturn",  450, 20,  45, 0.45f, 0.95f, 120},
    {"Uranus",  515, 14, 185, 0.40f, 0.95f, 250},
    {"Neptune", 580, 13, 225, 0.75f, 0.90f,  30},
};

// Position on a tilted orbit (ellipse with ry = 0.4 * rx).
static Point onOrbit(Point sun, int rx, float angleDeg) {
    float t = angleDeg * 3.14159265f / 180.0f;
    float ry = rx * 0.4f;
    return { sun.x + (int)std::lround(rx * std::cos(t)), sun.y + (int)std::lround(ry * std::sin(t)) };
}

void drawSun(Canvas& cv, Point c, int r) {
    for (int g = 30; g >= 0; g -= 3) {               // glow: big dim circles first, bright core last
        float v = 0.35f + 0.65f * (30 - g) / 30.0f;
        circleMidpoint(cv, c, r + g, hsvToRgb(35.0f + (30 - g) * 0.5f, 0.9f, v), true);
    }
}

void drawOrbitsAndPlanets(Canvas& cv, Point sun) {
    Color orbitCol{70, 70, 100};
    for (const Planet& p : PLANETS)                  // orbits first, so planets sit on top
        ellipseMidpoint(cv, sun, p.rx, (int)(p.rx * 0.4f), orbitCol, false);
    for (const Planet& p : PLANETS) {
        Point pos = onOrbit(sun, p.rx, p.angleDeg);
        if (p.name == "Saturn") {                    // the ring: two thin ellipses
            ellipseMidpoint(cv, pos, p.r * 2 + 6, p.r / 2 + 3, {200, 180, 140}, false);
            ellipseMidpoint(cv, pos, p.r * 2 + 3, p.r / 2 + 2, {170, 150, 110}, false);
        }
        circleMidpoint(cv, pos, p.r, hsvToRgb(p.hue, p.sat, p.val), true);
        if (p.name == "Earth")                       // the Moon
            circleMidpoint(cv, {pos.x + p.r + 8, pos.y - 6}, 3, {200, 200, 200}, true);
    }
}

void drawAsteroidBelt(Canvas& cv, Point sun) {
    std::mt19937 rng(7);                             // fixed seed = same belt every run
    std::uniform_real_distribution<float> ang(0, 360), rad(320, 345), size(3, 6), jitter(0.7f, 1.1f);
    for (int i = 0; i < 45; i++) {
        Point c = onOrbit(sun, (int)rad(rng), ang(rng));   // between Mars and Jupiter
        float s = size(rng);
        std::vector<Point> pts;
        for (int k = 0; k < 7; k++) {                // 7 jagged corners = a rock
            float t = k * 2 * 3.14159265f / 7;
            float rr = s * jitter(rng);
            pts.push_back({c.x + (int)std::lround(rr * std::cos(t)), c.y + (int)std::lround(rr * std::sin(t))});
        }
        scanlineFill(cv, pts, {120, 110, 100});
        drawPolygon(cv, pts, {160, 150, 140});
    }
}
