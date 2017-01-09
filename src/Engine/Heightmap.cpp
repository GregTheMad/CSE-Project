#include "Heightmap.h"

namespace engine
{
	void Heightmap::Initialize()
	{
		if (!m_texture.loadImage("Textures/England_Heightmap.png"))
			ofLog(OF_LOG_ERROR, "Error while loading Nightsky Texture");
		m_texture.update();
		float offset = static_cast<float>(m_resolution) / 2;

		for (int x = 0; x < m_resolution; x++)
		{
			for (int y = 0; y < m_resolution; y++)
			{
				m_mesh.addVertex(ofVec3f(x*m_scale - offset, m_texture.getColor(x,y).r * 3000, y*m_scale - offset));
			}
			cout << std::to_string(m_texture.getColor(x, 500).r) + "\n";
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