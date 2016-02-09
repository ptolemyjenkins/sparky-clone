#pragma once
#include <iostream>
#include <algorithm>

namespace sparky { namespace maths {

	struct vec4
	{
		float x;
		float y;
		float z;
		float w;

		vec4();
		vec4(const float& x, const float& y, const float& z, const float& w);

		float dot(const vec4& other) const;
		vec4 cross(const vec4& other) const;

		float length() const;
		vec4& normalised();
		float max();
		vec4& add(const vec4& other);
		vec4& subtract(const vec4& other);
		vec4& multiply(const vec4& other);
		vec4& divide(const vec4& other);

		vec4& add(const float& other);
		vec4& subtract(const float& other);
		vec4& multiply(const float& other);
		vec4& divide(const float& other);

		vec4 set(const float& x, const float& y, const float& z, const float& w);
		vec4& returnX();
		vec4& returnY();
		vec4& returnZ();
		vec4& returnW();

		friend vec4 operator+(vec4 left,const vec4& right);
		friend vec4 operator-(vec4 left, const vec4& right);
		friend vec4 operator*(vec4 left, const vec4& right);
		friend vec4 operator/(vec4 left, const vec4& right);

		vec4& operator+=(const vec4& other);
		vec4& operator-=(const vec4& other);
		vec4& operator*=(const vec4& other);
		vec4& operator/=(const vec4& other);

		friend vec4 operator+(vec4 left, const float& right);
		friend vec4 operator-(vec4 left, const float& right);
		friend vec4 operator*(vec4 left, const float& right);
		friend vec4 operator/(vec4 left, const float& right);

		vec4& operator+=(const float& other);
		vec4& operator-=(const float& other);
		vec4& operator*=(const float& other);
		vec4& operator/=(const float& other);

		bool operator ==(const vec4& other);
		bool operator !=(const vec4& other);

		friend std::ostream& operator<<(std::ostream& stream, const vec4& vector);
	};


} }