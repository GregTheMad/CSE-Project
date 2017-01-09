#pragma once
#include "GameObject.h"
#include "ofxAssimpModelLoader.h"
#include "ofMath.h"

namespace engine
{
	class Skybox : public GameObject
	{
	public:
		Skybox();
		inline ~Skybox() {};
		virtual void Update(float deltaTime) override;
		virtual void Draw() override;
		virtual void Initialize() override;

		float DurationOfDay;
		float TimeOfDay;
	private:
		ofMesh background_mesh;
		ofTexture backgr_texture;
		ofMesh sun_mesh;
		ofMesh air_scatter_mesh_;
		ofImage nightsky_texture_;
	};
}