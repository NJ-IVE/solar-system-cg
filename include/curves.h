
#pragma once
#include "canvas.h"
#include <vector>
std::vector<Point> bezier(const std::vector<Point>& ctrl, int segments);
void drawPath(Canvas& cv, const std::vector<Point>& pts, Color col);
