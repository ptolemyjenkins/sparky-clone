#include "quaternion.h"

namespace sparky {	namespace maths {

	quaternion::quaternion()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	quaternion::quaternion(const float & x, const float & y, const float & z, const float & w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	quaternion::quaternion(const vec3 & axis, const float & angle)
	{
		vec3 naxis = axis;
		naxis.normalised();
		float sinHalfAngle = sin(toRadians(angle) / 2);
		float cosHalfAngle = cos(toRadians(angle) / 2);

		x = naxis.x * sinHalfAngle;
		y = naxis.y * sinHalfAngle;
		z = naxis.z * sinHalfAngle;
		w = cosHalfAngle;
	}

	quaternion::quaternion(const mat4 & rotation)
	{
		float trace = rotation.get(0, 0) + rotation.get(1, 1) + rotation.get(2, 2);

		if (trace > 0) {
			float s = 0.5f / sqrt(trace + 1.0f);
			w = 0.25f / s;
			x = (rotation.get(2, 1) - rotation.get(1, 2)) * s;
			y = (rotation.get(0, 2) - rotation.get(2, 0)) * s;
			z = (rotation.get(1, 0) - rotation.get(0, 1)) * s;
		}
		else {
			if (rotation.get(0, 0) > rotation.get(1, 1) && rotation.get(0, 0) > rotation.get(2, 2)) {
				float s = 2.0f * sqrt(1.0f + rotation.get(0, 0) - rotation.get(1, 1) - rotation.get(2, 2));
				w = (rotation.get(2, 1) - rotation.get(1, 2)) / s;
				x = 0.25f * s;
				y = (rotation.get(0, 1) + rotation.get(1, 0)) / s;
				z = (rotation.get(0, 2) + rotation.get(2, 0)) / s;
			}
			else if (rotation.get(1, 1) > rotation.get(2, 2)) {
				float s = 2.0f * sqrt(1.0f + rotation.get(1, 1) - rotation.get(0, 0) - rotation.get(2, 2));
				w = (rotation.get(0, 1) - rotation.get(2, 0)) / s;
				x = (rotation.get(0, 1) + rotation.get(1, 0)) / s;
				y = 0.25f * s;
				z = (rotation.get(1, 2) + rotation.get(2, 1)) / s;
			}
			else {
				float s = 2.0f * sqrt(1.0f + rotation.get(2, 2) - rotation.get(0, 0) - rotation.get(1, 1));
				w = (rotation.get(1, 0) - rotation.get(0, 1)) / s;
				x = (rotation.get(0, 2) + rotation.get(2, 0)) / s;
				y = (rotation.get(2, 1) + rotation.get(1, 2)) / s;
				z = 0.25f * s;
			}
		}

		float length = sqrt(x * x + y * y + z * z + w * w);
		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}

	quaternion & quaternion::set(const float & x, const float & y, const float & z, const float & w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
		return *this;
	}

	quaternion & quaternion::set(const quaternion & other)
	{
		set(other.x, other.y, other.z, other.w);
		return *this;
	}

	float quaternion::length() const
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}

	quaternion & quaternion::normalised()
	{
		float len = length();
		x /= len;
		y /= len;
		z /= len;
		w /= len;
		return *this;
	}

	quaternion quaternion::conjugate() const
	{
		return quaternion(-x, -y, -z, w);
	}

	quaternion quaternion::inverse() const
	{
		return this->conjugate().divide(length()*length()).normalised();
	}

	quaternion & quaternion::add(const quaternion & other)
	{
		set(x + other.x, y + other.y, z + other.z, w + other.w);
		return *this;
	}

	quaternion & quaternion::subtract(const quaternion & other)
	{
		set(x - other.x, y - other.y, z - other.z, w - other.w);
		return *this;
	}

	quaternion & quaternion::multiply(const quaternion & other)
	{
		set(x * other.w + w * other.x + y * other.z - z * other.y,
			y * other.w + w * other.y + z * other.x - x * other.z,
			z * other.w + w * other.z + x * other.y - y * other.x,
			w * other.w - x * other.x - y * other.y - z * other.z);

		return *this;
	}

	quaternion& quaternion::multiply(const vec3 & other)
	{
		set(w * other.x + y * other.z - z * other.y,
			w * other.y + z * other.x - x * other.z,
			w * other.z + x * other.y - y * other.x,
			-x *other.x - y * other.y - z * other.z);

		return *this;
	}

	quaternion& quaternion::multiply(const float & other)
	{
		set(x * other, y * other, z * other, w * other);
		return *this;
	}

	quaternion& quaternion::divide(const float & other)
	{
		set(x / other, y / other, z / other, w / other);
		return *this;
	}

	mat4 quaternion::toRotationMatrix() const
	{
		vec3 forward(2.0f * (x * z - w * y), 2.0f * (y * z + w * x), 1.0f - 2.0f * (x * x + y * y));
		vec3 up(2.0f * (x * y + w * z), 1.0f - 2.0f * (x * x + z * z), 2.0f * (y * z - w * x));
		vec3 right(1.0f - 2.0f * (y * y + z * z), 2.0f * (x * y - w * z), 2.0f * (x * z + w * y));
		return mat4::rotation(forward, up, right);
	}

	float quaternion::dot(const quaternion & other) const
	{
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}

	quaternion & quaternion::nLerp(const quaternion & dest, const float & lerpFactor, const bool & shortest)
	{
		quaternion correctedDest = dest;
		if (shortest && this->dot(dest) < 0) {
			correctedDest = quaternion(-dest.x, -dest.y, -dest.z, -dest.w);
		}
		return (((correctedDest -= *this) *= lerpFactor) += *this).normalised();

	}

	quaternion & quaternion::sLerp(const quaternion & dest, const float & lerpFactor, const bool & shortest)
	{
		float EPSILON = 1e3f;

		float cosine = this->dot(dest);
		quaternion correctedDest = dest;

		if (shortest && cosine < 0) {
			cosine = -cosine;
			correctedDest.set(-dest.x, -dest.y, -dest.z, -dest.w);
		}

		if (abs(cosine) >= 1 - EPSILON) {
			return nLerp(correctedDest, lerpFactor, false);
		}
		

		float sine = sqrt(1.0f - cosine * cosine);
		float angle = atan2(sine, cosine);
		float invSin = 1.0f / sine;

		float srcFactor = sin((1.0f - lerpFactor) * angle) * invSin;
		float destFactor =  sin((lerpFactor)* angle) * invSin;

		return (*this *= srcFactor) += (correctedDest * destFactor);

	}

	vec3 quaternion::getForward() const
	{
		return vec3(0, 0, 1).rotate(*this);
	}

	vec3 quaternion::getBack() const
	{
		return vec3(0, 0, -1).rotate(*this);
	}

	vec3 quaternion::getUp() const
	{
		return vec3(0, 1, 0).rotate(*this);
	}

	vec3 quaternion::getDown() const
	{
		return vec3(0, -1, 0).rotate(*this);
	}

	vec3 quaternion::getRight() const
	{
		return vec3(-1, 0, 0).rotate(*this);
	}

	vec3 quaternion::getLeft() const
	{
		return vec3(1, 0, 0).rotate(*this);
	}


	quaternion operator+(quaternion left, const quaternion & right)
	{
		return left.add(right);
	}

	quaternion operator-(quaternion left, const quaternion & right)
	{
		return left.subtract(right);
	}

	quaternion operator*(quaternion left, const quaternion & right)
	{
		return left.multiply(right);
	}

	quaternion operator*(quaternion left, const vec3 & right)
	{
		return left.multiply(right);
	}

	quaternion operator*(quaternion left, const float & right)
	{
		return left.multiply(right);
	}

	quaternion operator/(quaternion left, const float & right)
	{
		return left.divide(right);
	}

	quaternion & quaternion::operator+=(const quaternion & other)
	{
		return add(other);
	}

	quaternion & quaternion::operator-=(const quaternion & other)
	{
		return subtract(other);
	}

	quaternion & quaternion::operator*=(const quaternion & other)
	{
		return multiply(other);
	}

	quaternion & quaternion::operator*=(const vec3 & other)
	{
		return multiply(other);
	}

	quaternion & quaternion::operator*=(const float & other)
	{
		return multiply(other);
	}

	quaternion & quaternion::operator/=(const float & other)
	{
		return divide(other);
	}

	bool quaternion::operator==(const quaternion & other)
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	bool quaternion::operator!=(const quaternion & other)
	{
		return !(*this == other);
	}

	std::ostream & operator<<(std::ostream & stream, const quaternion & rotation)
	{
		stream << "quaternion: (" << rotation.x << ", " << rotation.y << ", " << rotation.z << ", " << rotation.w << ")";
		return stream;
	}

} }

