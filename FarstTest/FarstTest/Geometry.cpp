#include "Geometry.h"
#include "cassert"
#include "cmath"

Vector2::Vector2()
{
    x = 0.0f;
    y = 0.0f;
}

Vector2::Vector2(float inx, float iny)
{
    x = inx;
    y = iny;
}

Vector2 Vector2::operator+(const Vector2& val) const
{
    return {x + val.x, y + val.y};
}

Vector2 Vector2::operator-(const Vector2& val) const
{
    return {x - val.x, y - val.y};
}

Vector2 Vector2::operator*(float scale) const
{
    return {x * scale, y * scale};
}

Vector2 Vector2::operator/(float div) const
{
    assert(div != 0.0f);
    return {x / div, y / div};
}

void Vector2::operator+=(const Vector2& val)
{
    x += val.x;
    y += val.y;
}

void Vector2::operator-=(const Vector2& val)
{
    x -= val.x;
    y -= val.y;
}

void Vector2::operator*=(float scale)
{
    x *= scale;
    y *= scale;
}

void Vector2::operator/=(float div)
{
    assert(div != 0.0f);
    x /= div;
    y /= div;
}

bool Vector2::operator==(const Vector2& val)const
{
    return x == val.x && y == val.y;
}

float Vector2::Length() const
{
    return std::hypotf(x, y);
}

float Vector2::SqLength() const
{
    return x * x + y * y;
}

void Vector2::Normalize()
{
    float len = Length();
    if (len == 0.0f) return;
    
    x /= len;
    y /= len;
}

Vector2 Vector2::Normalized() const
{
    float len = Length();
    if (len == 0)
    {
        return { 0.0f, 0.0f };
    }
    return { x / len, y / len };
}

float Dot(const Vector2& lVal, const Vector2& rVal)
{
    // ‚©‚¯‚Ä‘«‚¹‚Î‚¢‚¢
    return lVal.x * rVal.x + lVal.y * rVal.y;
}
