#include "Vec2.h"
#include <math.h>

Vec2::Vec2()
	: x(0)
	, y(0)
{
}

Vec2::Vec2(float x, float y)
	: x(x)
	, y(y)
{
}

void Vec2::operator=(const Vec2& rhs)
{
	x = rhs.x;
	y = rhs.y;
}

void Vec2::operator+=(const Vec2& rhs)
{	
	x += rhs.x;
	y += rhs.y;
}

Vec2 Vec2::operator+(const Vec2& rhs) const
{
	Vec2 temp;
	temp.x = x + rhs.x;
	temp.y = y + rhs.y;
	return temp;
}

Vec2 Vec2::operator-(const Vec2& rhs) const
{
	Vec2 temp;
	temp.x = x - rhs.x;
	temp.y = y - rhs.y;
	return temp;
}

Vec2 Vec2::operator*(const float& rhs) const
{
	Vec2 temp;
	temp.x = x * rhs;
	temp.y = y * rhs;
	return temp;
}

Vec2 Vec2::operator*(const Vec2& rhs) const
{
	Vec2 temp;
	temp.x = x * rhs.x;
	temp.y = y * rhs.y;
	return temp;
}

Vec2 Vec2::operator/(const float& rhs) const
{
	Vec2 temp;
	temp.x = x / rhs;
	temp.y = y / rhs;
	return temp;
}

bool Vec2::operator==(const Vec2& rhs) const
{
	return rhs.x == x && rhs.y == y;
}

Vec2 Vec2::invert() const
{
	Vec2 temp;
	temp.x = -x;
	temp.y = -y;
	return temp;
}

Vec2 Vec2::rotate(float angle) const
{
	auto theta = angle * m_Pi / 180;
	auto l = this->getAngle();
	auto length = this->length();

	Vec2 temp;
	temp.x = cosf(theta + l)*length;
	temp.y = sinf(theta + l)*length;
	return temp;
}

Vec2 Vec2::normalize() const
{	
	auto length = this->length();
	if (length < m_Epsilon && length > -m_Epsilon) 
		length = 1;

	Vec2 temp;
	temp.x = x / length;
	temp.y = y / length;
	return temp;
}

float Vec2::length() const
{
	return sqrtf(powf(this->x, 2) + powf(this->y, 2));	
}

float Vec2::lengthSqrt() const
{
	return powf(this->x, 2) + powf(this->y, 2);
}

float Vec2::getAngle() const
{
	return atan2f(y, x);
}

float Vec2::dot(const Vec2& rhs) const
{
	return x * rhs.y + y * rhs.x;
}
