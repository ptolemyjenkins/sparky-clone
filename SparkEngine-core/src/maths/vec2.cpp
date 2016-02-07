#include "vec2.h"


namespace sparky {
	namespace maths {

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

		vec2 & vec2::normalised()
		{
			float len = length();
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
			double rad = toRadians(angle);
			double cosine = cos(rad);
			double sine = sin(rad);
			return set((float) (x * cosine - y * sine), (float) (x * sine + y * cosine));
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

	}
}