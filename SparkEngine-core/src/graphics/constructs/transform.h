#pragma once
#include "../../maths/maths.h"

namespace sparky {	namespace graphics {
	using namespace maths;
	class Transform
	{
	private:
		Transform *parent;
		mat4 parentMatrix;
		
		vec3 oldPos;
		quaternion oldRot;
		vec3 oldScale;
	public:
		vec3 pos;
		quaternion rot;
		vec3 scale;
	public:
		Transform();
		void update();
		bool hasChanged();
		void setParent(Transform *newParent);
	private:
		mat4& getParentMatrix();
	public:

		mat4 getTransformation();
		void rotateTrans(const quaternion& rotation);
		void translateTrans(const vec3& translation);
		void scaleTrans(const vec3& scale_);

		void setRotation(const quaternion& rotation);
		void setTranslation(const vec3& translation);
		void setScale(const vec3& scale_);

		vec3 getTransformedPos();
		quaternion getTransformedRot() const;
		vec3 getTransformedScale() const;
	};
	
} }