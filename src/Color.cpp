// File:    Color.cpp
// Author:  Danilo Peixoto
// Date:    05/08/2018

#include <Color.h>
#include <Global.h>

#include <cmath>

Color3::Color3() : r(0), g(0), b(0) {}
Color3::Color3(const Color3 & color3) : r(color3.r), g(color3.g), b(color3.b) {}
Color3::Color3(double r, double g, double b) : r(r), g(g), b(b) {}
Color3::~Color3() {}

double & Color3::operator [](size_t i) {
    return (&r)[i];
}
const double & Color3::operator [](size_t i) const {
    return (&r)[i];
}
Color3 Color3::operator +() const {
    return *this;
}
Color3 Color3::operator -() const {
    return Color3(-r, -g, -b);
}
Color3 Color3::operator +(const Color3 & rhs) const {
    return Color3(*this) += rhs;
}
Color3 Color3::operator -(const Color3 & rhs) const {
    return Color3(*this) -= rhs;
}
Color3 Color3::operator *(double rhs) const {
    return Color3(*this) *= rhs;
}
Color3 operator *(double lhs, const Color3 & rhs) {
    return rhs * lhs;
}
Color3 Color3::operator /(double rhs) const {
    return Color3(*this) /= rhs;
}
Color3 & Color3::operator +=(const Color3 & rhs) {
    r += rhs.r;
    g += rhs.g;
    b += rhs.b;

    return *this;
}
Color3 & Color3::operator -=(const Color3 & rhs) {
    r -= rhs.r;
    g -= rhs.g;
    b -= rhs.b;

    return *this;
}
Color3 & Color3::operator *=(double rhs) {
    r *= rhs;
    g *= rhs;
    b *= rhs;

    return *this;
}
Color3 & Color3::operator /=(double rhs) {
    r /= rhs;
    g /= rhs;
    b /= rhs;

    return *this;
}
bool Color3::operator ==(const Color3 & rhs) const {
    return r == rhs.r && g == rhs.g && b == rhs.b;
}
bool Color3::operator !=(const Color3 & rhs) const {
    return !(*this == rhs);
}
std::ostream & operator <<(std::ostream & lhs, const Color3 & rhs) {
    return lhs << '(' << rhs.r << ' ' << rhs.g << ' ' << rhs.b << ')';
}

Color3 & Color3::applyGamma(double gamma) {
    double t = 1.0 / gamma;

    r = std::pow(r, t);
    g = std::pow(g, t);
    b = std::pow(b, t);

    return *this;
}
Color3 & Color3::applyExposure(double exposure) {
    double t = std::pow(2.0, exposure);

    r *= t;
    g *= t;
    b *= t;

    return *this;
}
Color3 & Color3::saturate() {
    r = clamp(r, 0, 1.0);
    g = clamp(g, 0, 1.0);
    b = clamp(b, 0, 1.0);

    return *this;
}

Color4::Color4() : r(0), g(0), b(0), a(0) {}
Color4::Color4(const Color4 & color4) : r(color4.r), g(color4.g), b(color4.b), a(color4.a) {}
Color4::Color4(double r, double g, double b, double a) : r(r), g(g), b(b), a(a) {}
Color4::~Color4() {}

double & Color4::operator [](size_t i) {
    return (&r)[i];
}
const double & Color4::operator [](size_t i) const {
    return (&r)[i];
}
Color4 Color4::operator +() const {
    return *this;
}
Color4 Color4::operator -() const {
    return Color4(-r, -g, -b, a);
}
Color4 Color4::operator +(const Color4 & rhs) const {
    return Color4(*this) += rhs;
}
Color4 Color4::operator -(const Color4 & rhs) const {
    return Color4(*this) -= rhs;
}
Color4 Color4::operator *(double rhs) const {
    return Color4(*this) *= rhs;
}
Color4 operator *(double lhs, const Color4 & rhs) {
    return rhs * lhs;
}
Color4 Color4::operator /(double rhs) const {
    return Color4(*this) /= rhs;
}
Color4 & Color4::operator +=(const Color4 & rhs) {
    r += rhs.r;
    g += rhs.g;
    b += rhs.b;

    return *this;
}
Color4 & Color4::operator -=(const Color4 & rhs) {
    r -= rhs.r;
    g -= rhs.g;
    b -= rhs.b;

    return *this;
}
Color4 & Color4::operator *=(double rhs) {
    r *= rhs;
    g *= rhs;
    b *= rhs;

    return *this;
}
Color4 & Color4::operator /=(double rhs) {
    r /= rhs;
    g /= rhs;
    b /= rhs;

    return *this;
}
bool Color4::operator ==(const Color4 & rhs) const {
    return r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a;
}
bool Color4::operator !=(const Color4 & rhs) const {
    return !(*this == rhs);
}
std::ostream & operator <<(std::ostream & lhs, const Color4 & rhs) {
    return lhs << '(' << rhs.r << ' ' << rhs.g << ' ' << rhs.b << ' ' << rhs.a << ')';
}

Color4 & Color4::applyGamma(double gamma) {
    double t = 1.0 / gamma;

    r = std::pow(r, t);
    g = std::pow(g, t);
    b = std::pow(b, t);

    return *this;
}
Color4 & Color4::applyExposure(double exposure) {
    double t = std::pow(2.0, exposure);

    r *= t;
    g *= t;
    b *= t;

    return *this;
}
Color4 & Color4::saturate() {
    r = clamp(r, 0, 1.0);
    g = clamp(g, 0, 1.0);
    b = clamp(b, 0, 1.0);

    return *this;
}