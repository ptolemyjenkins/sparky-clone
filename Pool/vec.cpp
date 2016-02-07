#include "vec.h"


vec2::vec2()
{
	x = 0.0f;
	y = 0.0f;

}

vec2::vec2(const float& x, const float& y)
{
	this->x = x;
	this->y = y;
}

vec2& vec2::add(const vec2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

vec2& vec2::subtract(const vec2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

vec2& vec2::multiply(const vec2& other)
{
	x *= other.x;
	y *= other.y;
	return *this;
}

vec2& vec2::divide(const vec2& other)
{
	x /= other.x;
	y /= other.y;
	return *this;
}

vec2 & vec2::add(const float & other)
{
	x += other;
	y += other;
	return *this;
}

vec2 & vec2::subtract(const float & other)
{
	x -= other;
	y -= other;
	return *this;
}

vec2 & vec2::multiply(const float & other)
{
	x *= other;
	y *= other;
	return *this;
}

vec2 & vec2::divide(const float & other)
{
	x /= other;
	y /= other;
	return *this;
}

float vec2::length() const
{
	return sqrt(x * x + y * y);
}

float vec2::max() const
{
	return (x<y) ? y : x;
}

float vec2::dot(const vec2 & other) const
{
	return (x * other.x + y * other.y);
}

float vec2::magCross(const vec2& other) const
{
	return (x * other.y - y * other.x);
}

vec2 & vec2::normalised()
{
	float len = length();
	if (len == 0) {
		return *this;
	}
	x /= len;
	y /= len;
	return *this;
}

vec2 & vec2::lerp(const vec2 & dest, const float& lerpFactor)
{
	return *this += (dest - *this) * lerpFactor;
}

vec2 & vec2::rotate(const float & angle)
{
	double rad = angle;
	double cosine = cos(rad);
	double sine = sin(rad);
	return set((float)(x * cosine - y * sine), (float)(x * sine + y * cosine));
}

vec2& vec2::set(const float & x, const float& y)
{
	this->x = x;
	this->y = y;
	return *this;
}

vec2 & vec2::set(const vec2 & other)
{
	*this = other;
	return *this;
}

vec2 & vec2::returnX()
{
	set(x, 0);
	return *this;
}

vec2 & vec2::returnY()
{
	set(0, y);
	return *this;
}

vec2 operator+(vec2 left, const vec2& right)
{
	return left.add(right);
}

vec2 operator-(vec2 left, const vec2& right)
{
	return left.subtract(right);
}

vec2 operator*(vec2 left, const vec2& right)
{
	return left.multiply(right);
}

vec2 operator/(vec2 left, const vec2& right)
{
	return left.divide(right);
}

vec2 & vec2::operator+=(const vec2 & other)
{
	return add(other);
}

vec2 & vec2::operator-=(const vec2 & other)
{
	return subtract(other);
}

vec2 & vec2::operator*=(const vec2 & other)
{
	return multiply(other);
}

vec2 & vec2::operator/=(const vec2 & other)
{
	return divide(other);
}

vec2 operator+(vec2 left, const float & right)
{
	return left.add(right);
}

vec2 operator-(vec2 left, const float & right)
{
	return left.subtract(right);
}

vec2 operator*(vec2 left, const float & right)
{
	return left.multiply(right);
}

vec2 operator/(vec2 left, const float & right)
{
	return left.divide(right);
}

vec2 & vec2::operator+=(const float & other)
{
	return add(other);
}

vec2 & vec2::operator-=(const float & other)
{
	return subtract(other);
}

vec2 & vec2::operator*=(const float & other)
{
	return multiply(other);
}

vec2 & vec2::operator/=(const float & other)
{
	return divide(other);
}

bool vec2::operator==(const vec2 & other)
{
	return x == other.x && y == other.y;
}

bool vec2::operator!=(const vec2 & other)
{
	return !(*this == other);
}

std::ostream& operator<<(std::ostream& stream, const vec2& vector)
{
	stream << "vec2: (" << vector.x << ", " << vector.y << ")";
	return stream;
}

vec4::vec4()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

vec4::vec4(const float& x, const float& y, const float& z, const float& w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

vec4& vec4::add(const vec4& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
	return *this;
}

vec4& vec4::subtract(const vec4& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
	return *this;
}

vec4& vec4::multiply(const vec4& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	w *= other.w;
	return *this;
}

vec4& vec4::divide(const vec4& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	w /= other.w;
	return *this;
}

vec4 & vec4::add(const float & other)
{
	x += other;
	y += other;
	z += other;
	w += other;
	return *this;
}

vec4 & vec4::subtract(const float & other)
{
	x -= other;
	y -= other;
	z -= other;
	w -= other;
	return *this;
}

vec4 & vec4::multiply(const float & other)
{
	x *= other;
	y *= other;
	z *= other;
	w *= other;
	return *this;
}

vec4 & vec4::divide(const float & other)
{
	x /= other;
	y /= other;
	z /= other;
	w /= other;
	return *this;
}

vec4 vec4::set(const float & x, const float & y, const float & z, const float & w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	return *this;
}

vec4 & vec4::returnX()
{
	set(x, 0, 0, 0);
	return *this;
}

vec4 & vec4::returnY()
{
	set(0, y, 0, 0);
	return *this;
}

vec4 & vec4::returnZ()
{
	set(0, 0, z, 0);
	return *this;
}

vec4 & vec4::returnW()
{
	set(0, 0, 0, w);
	return *this;
}

vec4 operator+(vec4 left, const vec4& right)
{
	return left.add(right);
}

vec4 operator-(vec4 left, const vec4& right)
{
	return left.subtract(right);
}

vec4 operator*(vec4 left, const vec4& right)
{
	return left.multiply(right);
}

vec4 operator/(vec4 left, const vec4& right)
{
	return left.divide(right);
}

vec4 & vec4::operator+=(const vec4 & other)
{
	return add(other);
}

vec4 & vec4::operator-=(const vec4 & other)
{
	return subtract(other);
}

vec4 & vec4::operator*=(const vec4 & other)
{
	return multiply(other);
}

vec4 & vec4::operator/=(const vec4 & other)
{
	return divide(other);
}

vec4 operator+(vec4 left, const float & right)
{
	return left.add(right);
}

vec4 operator-(vec4 left, const float & right)
{
	return left.subtract(right);
}

vec4 operator*(vec4 left, const float & right)
{
	return left.multiply(right);
}

vec4 operator/(vec4 left, const float & right)
{
	return left.divide(right);
}

vec4 & vec4::operator+=(const float & other)
{
	return add(other);
}

vec4 & vec4::operator-=(const float & other)
{
	return subtract(other);
}

vec4 & vec4::operator*=(const float & other)
{
	return multiply(other);
}

vec4 & vec4::operator/=(const float & other)
{
	return divide(other);
}

bool vec4::operator==(const vec4 & other)
{
	return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool vec4::operator!=(const vec4 & other)
{
	return !(*this == other);
}

std::ostream& operator<<(std::ostream& stream, const vec4& vector)
{
	stream << "vec4: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
	return stream;
}