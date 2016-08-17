#include "mat4.h"

namespace sparky { namespace maths {
	mat4::mat4()
	{
		for (int i = 0; i < 4 * 4; i++)
			elements[i] = 0.0f;
	}

	mat4::mat4(float diagonal)
	{
		for (int i = 0; i < 4 * 4; i++)
			elements[i] = 0.0f;
		elements[0 + 0 * 4] = diagonal;
		elements[1 + 1 * 4] = diagonal;
		elements[2 + 2 * 4] = diagonal;
		elements[3 + 3 * 4] = diagonal;
	}

	mat4 & mat4::set(int x, int y, float value)
	{
		elements[y + x * 4] = value;
		return *this;
	}

	float mat4::get(int x, int y) const
	{
		return elements[y + x * 4];
	}

	mat4 & mat4::multiply(const mat4 & other)
	{
		mat4 init = *this;
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				set(x, y, init.get(0, y) * other.get(x, 0) +
						  init.get(1, y) * other.get(x, 1) +
						  init.get(2, y) * other.get(x, 2) +
						  init.get(3, y) * other.get(x, 3));
			}
		}
		return *this;
	}

	vec3& mat4::transform(vec3& other) const
	{
		other.set(other.x * get(0, 0) + other.y * get(1, 0) + other.z * get(2, 0) + get(3, 0),
				  other.x * get(0, 1) + other.y * get(1, 1) + other.z * get(2, 1) + get(3, 1),
				  other.x * get(0, 2) + other.y * get(1, 2) + other.z * get(2, 2) + get(3, 2));
		return other;
	}

	vec4 & mat4::transform(vec4 & other) const
	{
		other.set(	other.x * get(0, 0) + other.y * get(1, 0) + other.z * get(2, 0) + other.w * get(3, 0),
					other.x * get(0, 1) + other.y * get(1, 1) + other.z * get(2, 1) + other.w * get(3, 1),
					other.x * get(0, 2) + other.y * get(1, 2) + other.z * get(2, 2) + other.w * get(3, 2),
					other.x * get(0, 3) + other.y * get(1, 3) + other.z * get(2, 3) + other.w * get(3, 3));
		return other;
	}

	void mat4::transpose()
	{
		mat4 result = *this;
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				set(x, y, result.get(y, x));
			}
		}
	}

	void mat4::display()
	{
		for (int y = 0; y < 4; y++)
		{
			util::Logging::log("[");
			for (int x = 0; x < 4; x++)
			{
				util::Logging::log(std::to_string(get(x, y)) + " ");
			}
			util::Logging::log("]\n");
		}
	}

	mat4 mat4::identity()
	{
		return mat4(1.0f);
	}

	mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		mat4 result(1.0f);
		result.elements[0 + 0 * 4] = 2.0f / (right - left);

		result.elements[1 + 1 * 4] = 2.0f / (top - bottom);

		result.elements[2 + 2 * 4] = 2.0f / (near - far);

		result.elements[0 + 3 * 4] = (left + right) / (left - right);
		result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result.elements[2 + 3 * 4] = (far + near) / (far - near);

		/*result.set(0, 0, (2 / (right - left)));
		result.set(1, 1, (2 / (top - bottom)));
		result.set(2, 2, (2 / (near - far)));
		result.set(3, 0, ((right + left) / (left - right)));
		result.set(3, 1, ((top + bottom) / (bottom - top)));
		result.set(3, 2, ((far + near) / (far - near)));*/
		return result;
	}

	mat4 mat4::perspective(float fov, float aspect, float near, float far)
	{
		fov = tan(toRadians(fov) / 2);
		mat4 result(0.0f);
		result.set(0, 0, (1 / (aspect * fov)));
		result.set(1, 1, (1 / fov));
		result.set(2, 2, (-(near + far) / (near - far)));
		result.set(2, 3, 1.0f);
		result.set(3, 2, (2 * (far * near) / (near - far)));
		return result;
	}

	mat4 mat4::translation(const vec3& translation)
	{
		mat4 result(1.0f);
		result.set(3, 0, translation.x);
		result.set(3, 1, translation.y);
		result.set(3, 2, translation.z);
		return result;
	}

	mat4 mat4::rotation(const vec3 & axis, float angle)
	{
		angle = toRadians(angle);
		float c = cos(angle);
		float s = sin(angle);
		float omc = 1 - c;
		vec3 naxis = axis;
		naxis.normalised();
		float x = naxis.x;
		float y = naxis.y;
		float z = naxis.z;

		mat4 result(1.0f);
		result.set(0, 0, x * x * omc + c);
		result.set(0, 1, x * y * omc + z * s);
		result.set(0, 2, x * z * omc - y * s);

		result.set(1, 0, x * y * omc - z * s);
		result.set(1, 1, y * y * omc + c);
		result.set(1, 2, y * z * omc + x * s);

		result.set(2, 0, x * z * omc + y * s);
		result.set(2, 1, y * z * omc - x * s);
		result.set(2, 2, z * z * omc + c);
		return result;
	}

	mat4 mat4::rotation(vec3 forward, vec3 up, vec3 right)
	{
		mat4 a(0.0f);
		vec3 f = forward.normalised();
		vec3 u = up.normalised();
		vec3 r = right.normalised();

		a.set(0, 0, r.x); a.set(1, 0, r.y); a.set(2, 0, r.z);
		a.set(0, 1, u.x); a.set(1, 1, u.y); a.set(2, 1, u.z);
		a.set(0, 2, f.x); a.set(1, 2, f.y); a.set(2, 2, f.z);
		a.set(3, 3, 1);
		return a;
	}

	mat4 mat4::rotation(vec3 forward, vec3 up)
	{
		vec3 right = forward.cross(up);

		return mat4::rotation(forward, up, right);
	}



	mat4 mat4::scale(const vec3 & scale)
	{
		mat4 result(1.0f);
		result.set(0, 0, scale.x);
		result.set(1, 1, scale.y);
		result.set(2, 2, scale.z);
		return result;
	}


	mat4 operator*(mat4 left, const mat4& right)
	{
		return left.multiply(right);
	}

	vec3& operator*(mat4 left, vec3 & right)
	{
		return left.transform(right);
	}

	mat4 & mat4::operator*=(const mat4 & other)
	{
		return multiply(other);
	}

	bool mat4::operator==(const mat4 & other)
	{
		for (int i = 0; i < 16; i++)
		{
			if (elements[i] != other.elements[i]) {
				return false;
			}
		}
		return true;
	}

	bool mat4::operator!=(const mat4 & other)
	{
		return !(*this == other);
	}

	std::ostream & operator<<(std::ostream & stream, const mat4 & matrix)
	{
		stream << std::endl
			   << "mat4: [" << matrix.get(0, 0) << ", " << matrix.get(1, 0) << ", " << matrix.get(2, 0) << ", " << matrix.get(3, 0) << "]" << std::endl
			   << "      [" << matrix.get(0, 1) << ", " << matrix.get(1, 1) << ", " << matrix.get(2, 1) << ", " << matrix.get(3, 1) << "]" << std::endl
			   << "      [" << matrix.get(0, 2) << ", " << matrix.get(1, 2) << ", " << matrix.get(2, 2) << ", " << matrix.get(3, 2) << "]" << std::endl
			   << "      [" << matrix.get(0, 3) << ", " << matrix.get(1, 3) << ", " << matrix.get(2, 3) << ", " << matrix.get(3, 3) << "]" << std::endl;
		return stream;
	}

} }