// File:    Global.cpp
// Author:  Danilo Peixoto
// Date:    02/08/2018

#include <Global.h>

#include <cmath>

double degrees(double radians) {
    return radians * 180.0 * CGC_INV_PI;
}
double radians(double degrees) {
    return degrees * CGC_PI / 180.0;
}
double clamp(double value, double minimum, double maximum) {
    return std::fmax(minimum, std::fmin(maximum, value));
}