#pragma once

#include "resource.h"

COLORREF getTextColor(double speed);

int scaleColor(double speed, double minSpeed, double maxSpeed, double minColor = 0, double maxColor = 255, bool minToMax = true);

void playSound(double speed);