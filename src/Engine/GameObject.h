#pragma once
#include "ofMain.h"
#include "Transform.h"

namespace engine
{
	class GameObject
	{
	public:
		inline explicit GameObject() {
		};
		inline ~GameObject() {};
		inline virtual void Initialize() {};
		inline virtual void Draw() {};
		inline virtual void Update(float deltaTime) {};
		Transform m_transform;
	};
}