#pragma once

class ColorHSV {
public :
    ColorHSV()= default;
    ColorHSV (double h_, double s_, double v_) : h(h_), s(s_), v(v_) {};
    double h; // 0 - 360
    double s; // 0 - 1
    double v; // 0 - 1
};

inline bool operator==(const ColorHSV &c1, const ColorHSV &c2) {
    return c1.h == c2.h && c1.s == c2.s && c1.v == c2.v;
}

inline bool operator!=(const ColorHSV &c1, const ColorHSV &c2) {
    return !(c1 == c2);
}

inline ColorHSV operator*(double l, const ColorHSV &c) {
    return {c.h * l, c.s * l, c.v * l};
}

inline ColorHSV operator*(const ColorHSV &c, double l) {
    return l * c;
}

inline ColorHSV operator+(const ColorHSV &c1, const ColorHSV &c2) {
    return {c1.h + c2.h, c1.s + c2.s, c1.v + c2.v};
}

inline ColorHSV operator-(const ColorHSV &c1, const ColorHSV &c2) {
    return {c1.h - c2.h, c1.s - c2.s, c1.v - c2.v};
}

inline ColorHSV operator*(const ColorHSV &c1, const ColorHSV &c2) {
    return {c1.h * c2.h, c1.s * c2.s, c1.v * c2.v};
}

inline ColorHSV operator/(const ColorHSV &c, const double &l) {
    return {c.h / l, c.s / l, c.v / l};
}

inline ColorHSV cap(const ColorHSV &c) {
    ColorHSV color(c.h, c.s, c.v);

    if (color.h > 1.0)
        color.h = 1.0;
    if (color.s > 1.0)
        color.s = 1.0;
    if (color.v > 1.0)
        color.v = 1.0;

    if (color.h < 0.0)
        color.h = 0.0;
    if (color.s < 0.0)
        color.s = 0.0;
    if (color.v < 0.0)
        color.v = 0.0;

    return color;
}