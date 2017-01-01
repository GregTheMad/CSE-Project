#include "Heightmap.h"

namespace engine
{
	void Heightmap::Initialize()
	{
		if (!m_texture.loadImage("Milkyway_Skybox.jpg"))
			ofLog(OF_LOG_ERROR, "Error while loading Nightsky Texture");

		float offset = static_cast<float>(m_resolution) / 2;

		for (int x = 0; x < m_resolution; x++)
		{
			for (int y = 0; y < m_resolution; y++)
			{
				m_mesh.addVertex(ofVec3f(x*m_scale - offset, 0.0f, y*m_scale - offset));
			}
		}

		for (int x = 0; x < m_resolution - 1; x++)
		{
			for (int y = 0; y < m_resolution - 1; y++)
			{
				m_mesh.addIndex(x + y* m_resolution);               // 0
				m_mesh.addIndex((x + 1) + y* m_resolution);           // 1
				m_mesh.addIndex(x + (y + 1)* m_resolution);           // 10

				m_mesh.addIndex((x + 1) + y* m_resolution);           // 1
				m_mesh.addIndex((x + 1) + (y + 1)* m_resolution);       // 11
				m_mesh.addIndex(x + (y + 1)* m_resolution);           // 10
			}
		}
	}

	void Heightmap::Draw()
	{
		m_mesh.draw();
	}

	void Heightmap::Update(float deltaTime)
	{

	}
}