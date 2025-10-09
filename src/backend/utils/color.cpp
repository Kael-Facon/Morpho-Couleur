#include "color.hh"

void Color::to_gray(float r_ratio, float g_ratio, float b_ratio)
{
    float gray = r * r_ratio + g * g_ratio + b * b_ratio;

    r = gray;
    g = gray;
    b = gray;
}

uint8_t Color::get_gray(float r_ratio, float g_ratio, float b_ratio) const
{
    float gray = r * r_ratio + g * g_ratio + b * b_ratio;

    return gray * 255;
}

//Operator
Color& Color::operator=(const Color& col)
{
    r = col.r;
    g = col.g;
    b = col.b;

    return *this;
}

Color& Color::operator+=(const Color& col)
{
    r += col.r;
    g += col.g;
    b += col.b;

    return *this;
}

Color& Color::operator/=(const Color& col)
{
    r /= col.r;
    g /= col.g;
    b /= col.b;

    return *this;
} 

std::ostream& operator<<(std::ostream& out, const Color& col)
{
    return out << '(' << col.r << 
                  ", " << col.g <<
                  ", " << col.b << ")" << std::endl;
}