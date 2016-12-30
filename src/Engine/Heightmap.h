#pragma once
#include "GameObject.h"

namespace engine
{
	class Heightmap :
		public GameObject
	{
	public:
		explicit inline Heightmap(size_t res, float scale) : m_resolution(res), m_scale(scale)
		{	};
		inline ~Heightmap() {};
		virtual void Initialize() override;
		virtual void Draw() override;
		virtual void Update(float deltaTime) override;
	private:
		size_t m_resolution;
		float m_scale;
		ofMesh m_mesh;
		ofImage m_texture;
	};
}