#pragma once
#include <iostream>
#include "maths_func.h"
#include "vec3.h"
#include "mat4.h"
namespace sparky { namespace maths {
	struct quaternion
	{
		float x;
		float y;
		float z;
		float w;

		quaternion();
		quaternion(const float& x, const float& y, const float& z, const float& w);
		quaternion(const vec3& axis, const float& angle);
		quaternion(const mat4& rotation);
		quaternion& set(const float& x, const float& y, const float& z, const float& w);
		quaternion& set(const quaternion& other);

		float length() const;
		quaternion& normalised();
		quaternion conjugate() const;
		quaternion inverse() const;

		quaternion& add(const quaternion& other);
		quaternion& subtract(const quaternion& other);
		quaternion& multiply(const quaternion& other);
		quaternion& multiply(const vec3& other);
		quaternion& multiply(const float& other);
		quaternion& divide(const float& other);

		mat4 toRotationMatrix() const;

		float dot(const quaternion& other) const;
		quaternion& nLerp(const quaternion& dest, const float& lerpFactor, const bool& shortest);
		quaternion& sLerp(const quaternion& dest, const float& lerpFactor, const bool& shortest);

		vec3 getForward() const;
		vec3 getBack() const;
		vec3 getUp() const;
		vec3 getDown() const;
		vec3 getRight() const;
		vec3 getLeft() const;

		friend quaternion operator+(quaternion left, const quaternion& right);
		friend quaternion operator-(quaternion left, const quaternion& right);
		friend quaternion operator*(quaternion left, const quaternion& right);
		friend quaternion operator*(quaternion left, const vec3& right);
		friend quaternion operator*(quaternion left, const float& right);
		friend quaternion operator/(quaternion left, const float& right);

		quaternion& operator+=(const quaternion& other);
		quaternion& operator-=(const quaternion& other);
		quaternion& operator*=(const quaternion& other);
		quaternion& operator*=(const vec3& other);
		quaternion& operator*=(const float& other);
		quaternion& operator/=(const float& other);

		bool operator ==(const quaternion& other);
		bool operator !=(const quaternion& other);
		friend std::ostream& operator<<(std::ostream& stream, const quaternion& rotation);

	};
} }