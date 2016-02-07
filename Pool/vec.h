#pragma once
#include <iostream>

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
	float magCross(const vec2& other) const;

	vec2& normalised();
	vec2& lerp(const vec2& dest, const float& lerpFactor);
	vec2& rotate(const float& angle);

	vec2& set(const float& x, const float& y);
	vec2& set(const vec2& other);

	vec2& returnX();
	vec2& returnY();

	bool operator ==(const vec2& other);
	bool operator !=(const vec2& other);

	friend vec2 operator+(vec2 left, const vec2& right);
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

struct vec4
{
	float x;
	float y;
	float z;
	float w;

	vec4();
	vec4(const float& x, const float& y, const float& z, const float& w);

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

	friend vec4 operator+(vec4 left, const vec4& right);
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