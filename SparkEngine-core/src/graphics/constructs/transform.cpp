#include "transform.h"

namespace sparky { namespace graphics {
	Transform::Transform()
	{
		pos.set(0, 0, 0);
		rot .set(0, 0, 0, 1);
		scale.set(1, 1, 1);
		oldPos.set(1, 0, 0);
		oldRot.set(1, 0, 0, 1);
		oldScale.set(2, 1, 1);
		parentMatrix = mat4::identity();
	}

	void Transform::update()
	{
		oldPos.set(pos);
		oldRot.set(rot);
		oldScale.set(scale);
	}

	bool Transform::hasChanged()
	{
		if (parent != 0 && (*parent).hasChanged()) return true;
		if (!(pos == oldPos)) return true;
		if (!(rot == oldRot)) return true;
		if (!(scale == oldScale)) return true;
		return false;
	}

	mat4& Transform::getParentMatrix()
	{
		if (parent != 0 && (*parent).hasChanged()) {
			parentMatrix = (*parent).getTransformation();
		}
		return parentMatrix;
	}

	void Transform::setParent(Transform *newParent)
	{
		parent = newParent;
	}

	mat4 Transform::getTransformation()
	{
		mat4 translationMatrix = mat4::translation(pos);
		mat4 rotationMatrix = rot.toRotationMatrix();
		mat4 scaleMatrix = mat4::scale(scale);
		return getParentMatrix() * (translationMatrix * (rotationMatrix * scaleMatrix));
	}

	void Transform::rotateTrans(const quaternion& rotation)
	{
		rot *= rotation;
	}

	void Transform::translateTrans(const vec3 & translation)
	{
		pos += translation;
	}

	void Transform::scaleTrans(const vec3 & scale_)
	{
		scale *= scale_;
	}

	void Transform::setRotation(const quaternion& rotation)
	{
		rot.set(rotation);
	}

	void Transform::setTranslation(const vec3 & translation)
	{
		pos.set(translation);
	}

	void Transform::setScale(const vec3 & scale_)
	{
		scale.set(scale_);
	}

	vec3 Transform::getTransformedPos()
	{
		return getParentMatrix() * pos;
	}

	quaternion Transform::getTransformedRot() const
	{
		quaternion parentRotation(0, 0, 0, 1);
		if (parent != 0) {
			parentRotation = (*parent).getTransformedRot();
		}
		return parentRotation * rot;
	}

	vec3 Transform::getTransformedScale() const
	{
		vec3 parentScale(1, 1, 1);
		if (parent != 0) {
			parentScale = (*parent).getTransformedScale();
		}
		return parentScale * scale;
	}

	


	
	


} }