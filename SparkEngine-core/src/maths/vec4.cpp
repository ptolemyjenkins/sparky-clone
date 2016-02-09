#include "vec4.h"


namespace sparky { namespace maths {

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

		float vec4::dot(const vec4 & other) const
		{
			return (x * other.x + y * other.y + z * other.z + w * other.w);
		}

		vec4 vec4::cross(const vec4 & other) const
		{
			vec4 a((y * other.z - z * other.y), (z * other.x - x * other.z), (x * other.y - y * other.x), 1);
			return a;
		}

		float vec4::length() const
		{
			return sqrt(x * x + y * y + z * z + w * w);
		}

		vec4 & vec4::normalised()
		{
			float len = length();
			x /= len;
			y /= len;
			z /= len;
			w /= len;
			return *this;
		}

		float vec4::max()
		{
			return std::max(std::max(x, y), std::max(z, w));
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

} }