#pragma once
#include "../renderable3DComponent.h"


namespace sparky { 
	class CoreEngine;
	namespace components {
	class camera : public architecture::Renderable3DComponent {
	private:
		maths::mat4 projection;
	public:
		camera();
		camera(float fov, float aspect, float zNear, float zFar);

		void addToEngine(CoreEngine* engine);

		maths::mat4 getViewProjection();

		void printState();
	};

} }