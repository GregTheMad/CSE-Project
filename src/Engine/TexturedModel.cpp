#include "TexturedModel.h"

namespace engine 
{
	TexturedModel::TexturedModel(string filepath) : m_mesh_path(filepath)
	{

	}

	void TexturedModel::Initialize()
	{
		ofLog(OF_LOG_NOTICE, "Initializing TexturedModel: " + m_mesh_path);

		ofLog(OF_LOG_NOTICE, "---Loading Mesh");
		if ( !m_mesh_path.empty())
		{
			ofxAssimpModelLoader m;
			m.loadModel(m_mesh_path);
			m_mesh = m.getMesh(0);
			m_mesh.enableTextures();
		}

		ofLog(OF_LOG_NOTICE, "---Loading Texture");
		if (!m_diffuse_path.empty())
		{
			ofImage i;
			i.load(m_diffuse_path);
			m_diffuse.allocate(i.getWidth(), i.getHeight(), GL_RGBA);
			m_diffuse = i.getTexture();
		}
	}

	void TexturedModel::Update(float deltaTime){}

	void TexturedModel::Draw() {
		glPushMatrix();

		glTranslatef(m_transform.getPosition().x, m_transform.getPosition().y, m_transform.getPosition().z);
		glRotatef(m_transform.getRotation().getEuler().x, 1, 0, 0);
		glRotatef(m_transform.getRotation().getEuler().y, 0, 1, 0);
		glRotatef(m_transform.getRotation().getEuler().z, 0, 0, 1);
		glScalef(m_transform.getScale().x, m_transform.getScale().y, m_transform.getScale().z);
		
		
		//Binding Texture
		glEnable(GL_TEXTURE_2D);
		glColor3f(1, 1, 1);

		m_diffuse.bind();

		//drawing Mesh
		m_mesh.enableTextures();
		m_mesh.draw();

		//Unbinding Texture

		m_diffuse.unbind();
		glDisable(GL_TEXTURE_2D);

		glPopMatrix();
	}

	void TexturedModel::addTexture(TextureType type, string filepath)
	{
		if (type == TextureType::Diffuse)
		{
			m_diffuse_path = filepath;
		}
	}
}