#pragma once
#include <iostream>
#include "maths_func.h"
#include "vec3.h"
#include "vec4.h"


namespace sparky { namespace maths {
	struct mat4
	{
		union
		{
			float elements[4 * 4];
			vec4 columns[4];
		};

		mat4();
		mat4(float diagonal);

		mat4& set(int x, int y, float value);
		float get(int x, int y) const;

		mat4& multiply(const mat4& other);
		vec3& transform(vec3& other) const;
		vec4& transform(vec4& other) const;

		void transpose();
		void display();

		static mat4 identity();
		static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
		static mat4 perspective(float fov, float aspect, float near, float far);

		static mat4 translation(const vec3& translation);
		static mat4 rotation(const vec3& axis, float angle);
		static mat4 rotation(vec3 forward, vec3 up, vec3 right);
		static mat4 rotation(vec3 forward, vec3 up);
		static mat4 scale(const vec3& scale);

		friend mat4 operator*(mat4 left, const mat4& right);
		friend vec3& operator*(mat4 left, vec3& right);
		mat4& operator*=(const mat4& other);

		bool operator ==(const mat4& other);
		bool operator !=(const mat4& other);
		friend std::ostream& operator<<(std::ostream& stream, const mat4& matrix);
	};

} }