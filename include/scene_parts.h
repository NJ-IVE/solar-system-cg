#pragma once
#include "canvas.h"
void drawStarfield(Canvas& cv, int count);         // A  src/scene_a.cpp
void drawMeteors(Canvas& cv);                       // A  src/scene_a.cpp
void drawSun(Canvas& cv, Point c, int r);           // B  src/scene_b.cpp
void drawOrbitsAndPlanets(Canvas& cv, Point sun);   // B  src/scene_b.cpp
void drawAsteroidBelt(Canvas& cv, Point sun);       // B  src/scene_b.cpp
void drawComet(Canvas& cv);                         // C  src/scene_c.cpp
