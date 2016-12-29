#pragma once
#include "ofMain.h"
#include "ofMath.h"

namespace game
{
	class Skybox
	{
	public:
		void draw(float timeOfDay);
		void initialize();
	private:
		ofMesh background_mesh;
		ofTexture backgr_texture;
		ofMesh sun_mesh;
		float durationOfDay;
		ofMesh air_scatter_mesh_;
		ofImage nightsky_texture_;
	};
}