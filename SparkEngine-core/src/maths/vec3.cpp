#include "vec3.h"
#include "quaternion.h"

namespace sparky { namespace maths {

	vec3::vec3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	vec3::vec3(const float& x, const float& y, const float& z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	vec3& vec3::add(const vec3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	vec3& vec3::subtract(const vec3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	vec3& vec3::multiply(const vec3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	vec3& vec3::divide(const vec3& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	vec3 & vec3::add(const float & other)
	{
		x += other;
		y += other;
		z += other;
		return *this;
	}

	vec3 & vec3::subtract(const float & other)
	{
		x -= other;
		y -= other;
		z -= other;
		return *this;
	}

	vec3 & vec3::multiply(const float & other)
	{
		x *= other;
		y *= other;
		z *= other;
		return *this;
	}

	vec3 & vec3::divide(const float & other)
	{
		x /= other;
		y /= other;
		z /= other;
		return *this;
	}

	float vec3::length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	float vec3::max() const
	{
		float m = (x < y) ? y : x;
		return (m < z) ? z : m;
	}

	float vec3::dot(const vec3 & other) const
	{
		return (x * other.x + y * other.y + z * other.z);
	}

	vec3 vec3::cross(const vec3 & other) const
	{
		vec3 a((y * other.z - z * other.y), (z * other.x - x * other.z), (x * other.y - y * other.x));
		return a;
	}

	vec3 & vec3::absolute()
	{
		return set(abs(x), abs(y), abs(z));
	}

	vec3 & vec3::normalised()
	{
		float len = length();
		x /= len;
		y /= len;
		z /= len;
		return *this;
	}

	vec3 & vec3::lerp(const vec3 & dest, const float& lerpFactor)
	{
		return *this += (dest - *this) * lerpFactor;
	}
	
	vec3 & vec3::rotate(const quaternion& rotation)
	{
		quaternion conj = rotation.conjugate();
		quaternion w = rotation * (*this) * (conj);
		set(w.x, w.y, w.z);
		return *this;
	}

	vec3& vec3::set(const float & x, const float& y, const float& z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		return *this;
	}

	vec3 & vec3::set(const vec3 & other)
	{
		*this = other;
		return *this;
	}

	vec3 & vec3::returnX()
	{
		set(x, 0, 0);
		return *this;
	}

	vec3 & vec3::returnY()
	{
		set(0, y, 0);
		return *this;
	}

	vec3 & vec3::returnZ()
	{
		set(0, 0, z);
		return *this;
	}

	vec3 operator+(vec3 left, const vec3& right)
	{
		return left.add(right);
	}

	vec3 operator-(vec3 left, const vec3& right)
	{
		return left.subtract(right);
	}

	vec3 operator*(vec3 left, const vec3& right)
	{
		return left.multiply(right);
	}

	vec3 operator/(vec3 left, const vec3& right)
	{
		return left.divide(right);
	}

	vec3 & vec3::operator+=(const vec3 & other)
	{
		return add(other);
	}

	vec3 & vec3::operator-=(const vec3 & other)
	{
		return subtract(other);
	}

	vec3 & vec3::operator*=(const vec3 & other)
	{
		return multiply(other);
	}

	vec3 & vec3::operator/=(const vec3 & other)
	{
		return divide(other);
	}

	vec3 operator+(vec3 left, const float & right)
	{
		return left.add(right);
	}

	vec3 operator-(vec3 left, const float & right)
	{
		return left.subtract(right);
	}

	vec3 operator*(vec3 left, const float & right)
	{
		return left.multiply(right);
	}

	vec3 operator/(vec3 left, const float & right)
	{
		return left.divide(right);
	}

	vec3 & vec3::operator+=(const float & other)
	{
		return add(other);
	}

	vec3 & vec3::operator-=(const float & other)
	{
		return subtract(other);
	}

	vec3 & vec3::operator*=(const float & other)
	{
		return multiply(other);
	}

	vec3 & vec3::operator/=(const float & other)
	{
		return divide(other);
	}

	bool vec3::operator==(const vec3 & other)
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool vec3::operator!=(const vec3 & other)
	{
		return !(*this == other);
	}

	std::ostream& operator<<(std::ostream& stream, const vec3& vector)
	{
		stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		return stream;
	}

} }