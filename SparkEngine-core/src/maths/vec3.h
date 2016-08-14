#pragma once
#include <iostream>


namespace sparky { namespace maths {
	struct quaternion;
	struct vec3
	{
		float x;
		float y;
		float z;

		vec3();
		vec3(const float& x, const float& y, const float& z);

		vec3& add(const vec3& other);
		vec3& subtract(const vec3& other);
		vec3& multiply(const vec3& other);
		vec3& divide(const vec3& other);

		vec3& add(const float& other);
		vec3& subtract(const float& other);
		vec3& multiply(const float& other);
		vec3& divide(const float& other);

		float length() const;
		float max() const;
		float dot(const vec3& other) const;
		vec3 cross(const vec3& other) const;

		std::string display();
		
		vec3& absolute();
		vec3& normalised();
		vec3& lerp(const vec3& dest, const float& lerpFactor);
		vec3& rotate(const quaternion& rotation);

		vec3& set(const float& x, const float& y, const float& z);
		vec3& set(const vec3& other);

		vec3& returnX();
		vec3& returnY();
		vec3& returnZ();

		friend vec3 operator+(vec3 left,const vec3& right);
		friend vec3 operator-(vec3 left, const vec3& right);
		friend vec3 operator*(vec3 left, const vec3& right);
		friend vec3 operator/(vec3 left, const vec3& right);

		vec3& operator+=(const vec3& other);
		vec3& operator-=(const vec3& other);
		vec3& operator*=(const vec3& other);
		vec3& operator/=(const vec3& other);

		friend vec3 operator+(vec3 left, const float& right);
		friend vec3 operator-(vec3 left, const float& right);
		friend vec3 operator*(vec3 left, const float& right);
		friend vec3 operator/(vec3 left, const float& right);

		vec3& operator+=(const float& other);
		vec3& operator-=(const float& other);
		vec3& operator*=(const float& other);
		vec3& operator/=(const float& other);

		bool operator ==(const vec3& other);
		bool operator !=(const vec3& other);

		friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);
	};


} }