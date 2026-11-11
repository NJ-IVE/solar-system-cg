#include "canvas.h"
#include "scene_parts.h"

int main() {
    Canvas cv(1280, 720, {5, 5, 20});   // dark space blue
    Point sun{640, 360};
    drawStarfield(cv, 600);
    drawOrbitsAndPlanets(cv, sun);
    drawSun(cv, sun, 50);
    drawAsteroidBelt(cv, sun);
    drawComet(cv);
    drawMeteors(cv);
    cv.savePPM("out/scene.ppm");
    return 0;
}
