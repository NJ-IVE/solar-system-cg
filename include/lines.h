
#pragma once
#include "canvas.h"
void lineDDA(Canvas& cv, Point a, Point b, Color col);
void lineBresenham(Canvas& cv, Point a, Point b, Color col);
bool clipLine(Point& a, Point& b, int xmin, int ymin, int xmax, int ymax);

