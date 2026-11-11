
#pragma once
#include "canvas.h"
#include <vector>
void drawPolygon(Canvas& cv, const std::vector<Point>& pts, Color col);
void scanlineFill(Canvas& cv, const std::vector<Point>& pts, Color col);
void boundaryFill(Canvas& cv, Point seed, Color fill, Color boundary);

