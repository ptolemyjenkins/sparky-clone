#pragma once
#include <iostream>
#include "maths_func.h"

namespace sparky { namespace maths {

	struct vec2
	{
		float x;
		float y;

		vec2();
		vec2(const float& x, const float& y);

		vec2& add(const vec2& other);
		vec2& subtract(const vec2& other);
		vec2& multiply(const vec2& other);
		vec2& divide(const vec2& other);

		vec2& add(const float& other);
		vec2& subtract(const float& other);
		vec2& multiply(const float& other);
		vec2& divide(const float& other);

		float length() const;
		float max() const;
		float dot(const vec2& other) const;
		
		vec2& normalised();
		vec2& lerp(const vec2& dest, const float& lerpFactor);
		vec2& rotate(const float& angle);

		vec2& set(const float& x, const float& y);
		vec2& set(const vec2& other);

		vec2& returnX();
		vec2& returnY();

		bool operator ==(const vec2& other);
		bool operator !=(const vec2& other);

		friend vec2 operator+(vec2 left,const vec2& right);
		friend vec2 operator-(vec2 left, const vec2& right);
		friend vec2 operator*(vec2 left, const vec2& right);
		friend vec2 operator/(vec2 left, const vec2& right);

		vec2& operator+=(const vec2& other);
		vec2& operator-=(const vec2& other);
		vec2& operator*=(const vec2& other);
		vec2& operator/=(const vec2& other);

		friend vec2 operator+(vec2 left, const float& right);
		friend vec2 operator-(vec2 left, const float& right);
		friend vec2 operator*(vec2 left, const float& right);
		friend vec2 operator/(vec2 left, const float& right);

		vec2& operator+=(const float& other);
		vec2& operator-=(const float& other);
		vec2& operator*=(const float& other);
		vec2& operator/=(const float& other);


		friend std::ostream& operator<<(std::ostream& stream, const vec2& vector);
	};


} }