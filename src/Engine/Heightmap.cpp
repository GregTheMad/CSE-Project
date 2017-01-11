#include "Heightmap.h"

namespace engine
{
	void Heightmap::Initialize()
	{
		ofLog(OF_LOG_NOTICE, "Initializing Heightmap");

		if (!m_texture.loadImage("Textures/England_Heightmap.png"))
			ofLog(OF_LOG_ERROR, "Error while loading Heightmap texture");		

		float offset = (static_cast<float>(m_resolution) / 2) * m_scale;
		float sx = m_texture.getWidth() / static_cast<float>(m_resolution);
		float sy = m_texture.getHeight() / static_cast<float>(m_resolution);
		float heightscale = 10.0f / 128.0f;

		for (float x = 0; x < m_resolution; x++)
		{
			for (float y = 0; y < m_resolution; y++)
			{
				m_mesh.addVertex(ofVec3f(x*m_scale - offset, m_texture.getColor(x * sx, y *sy).r * heightscale, y*m_scale - offset));
				m_mesh.addTexCoord(ofVec2f(x / m_resolution, y / m_resolution));
			}
		}

		for (int x = 0; x < m_resolution - 1; x++)
		{
			for (int y = 0; y < m_resolution - 1; y++)
			{
				m_mesh.addIndex(x + y* m_resolution);               // 0
				m_mesh.addIndex((x + 1) + y* m_resolution);           // 1
				m_mesh.addIndex(x + (y + 1)* m_resolution);           // 10
				m_mesh.addNormal(ofVec3f(0, 1, 0));

				m_mesh.addIndex((x + 1) + y* m_resolution);           // 1
				m_mesh.addIndex((x + 1) + (y + 1)* m_resolution);       // 11
				m_mesh.addIndex(x + (y + 1)* m_resolution);           // 10
				m_mesh.addNormal(ofVec3f(0, 1, 0));
			}
		}
	}

	void Heightmap::Draw()
	{
		glEnable(GL_TEXTURE_2D);
		ofSetColor(0, 100, 0, 255);
		m_texture.getTextureReference().bind();
		m_mesh.draw();
		m_texture.getTextureReference().unbind();
		glDisable(GL_TEXTURE_2D);
	}

	void Heightmap::Update(float deltaTime)
	{

	}
}