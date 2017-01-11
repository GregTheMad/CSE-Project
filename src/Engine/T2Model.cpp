#include "T2Model.h"

namespace engine
{
	T2Model::~T2Model()
	{}

	void T2Model::Initialize()
	{
		ofLog(OF_LOG_NOTICE, "Initializing T2Model: " + m_filepath);

		m_mesh.load(m_filepath);

		std::vector<ofPoint> v = m_mesh.getVertices();
		std::vector<size_t> i = m_mesh.getIndices();
		f = m_mesh.getUniqueFaces();

	}

	void T2Model::Update(float deltaTime)
	{

	}

	void T2Model::Draw()
	{
		glPushMatrix();
		//ofDisableDepthTest();

		glTranslatef(m_transform.getPosition().x, m_transform.getPosition().y, m_transform.getPosition().z);
		glRotatef(m_transform.getRotation().getEuler().x, 1, 0, 0);
		glRotatef(m_transform.getRotation().getEuler().y, 0, 1, 0);
		glRotatef(m_transform.getRotation().getEuler().z, 0, 0, 1);
		glScalef(m_transform.getScale().x, m_transform.getScale().y, m_transform.getScale().z);

		ofEnableAlphaBlending();

		ofSetColor(255, 0, 255, static_cast<int>(255 * m_alpha));

		//m_mesh.draw();

		for (size_t i = 0; i < f.size(); i++)
		{
			ofDrawTriangle(f[i].getVertex(0), f[i].getVertex(1), f[i].getVertex(2));
		}

		ofDisableAlphaBlending();

		//ofEnableDepthTest();
		glPopMatrix();
	}

	void T2Model::setAlpha(float alpha)
	{

	}
}