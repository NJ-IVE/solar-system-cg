
#pragma once
#include "canvas.h"
Color hsvToRgb(float h, float s, float v);            // h: 0-360, s and v: 0-1
void rgbToHsv(Color c, float& h, float& s, float& v);

