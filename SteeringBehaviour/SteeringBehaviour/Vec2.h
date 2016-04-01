#pragma once
class Vec2
{
public:
	Vec2();
	Vec2(float x, float y);
	
	void	operator=(const Vec2 &rhs);
	void	operator+=(const Vec2 &rhs);
	Vec2	operator+(const Vec2 &rhs) const;
	Vec2	operator-(const Vec2 &rhs) const;
	Vec2	operator*(const float &rhs) const;
	Vec2	operator*(const Vec2 &rhs) const;
	Vec2	operator/(const float &rhs) const;
	bool	operator==(const Vec2 &rhs) const;
	Vec2	invert() const;
	Vec2	rotate(float angle) const;
	Vec2	normalize() const;
	float	length() const;
	float	lengthSqrt() const;
	float	getAngle() const;
	float	dot(const Vec2& rhs) const;

public:
	float x;
	float y;
	const float m_Pi = 3.1415927410125732421875f;
	const float m_Epsilon = 0.00001f;
};