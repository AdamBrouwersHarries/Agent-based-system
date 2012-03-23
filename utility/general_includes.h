#ifndef GENERAL_INCLUDES_H
#define GENERAL_INCLUDES_H
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>
//simple double "equality" comparison
bool d_e(double a, double b) {
    return abs(a - b) < 0.00001;
}
//calculates if p2 is clockwise of p1 with respect to the origin
int clockwise(int x1, int y1, int x2, int y2) {
    return (x2 * y1) - (x1 * y2);
}
#endif //GENERAL_INCLUDES_H