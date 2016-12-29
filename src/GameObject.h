#pragma once
#include "ofMain.h"

class GameObject
{
public:
	inline explicit GameObject() {};
	inline ~GameObject() {};
	inline virtual void Initialize() {};
	inline virtual void Draw() {};
	inline virtual void Update(float deltaTime) {};
};

