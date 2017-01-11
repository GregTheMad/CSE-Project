#include "TransparentModel.h"

namespace engine
{ 
	TransparentModel::~TransparentModel()
	{}

	void TransparentModel::Initialize()
	{
		ofLog(OF_LOG_NOTICE, "Initializing TransparentModel: " + m_filepath);
		m_mesh.load(m_filepath);
	}

	void TransparentModel::Update(float deltaTime)
	{

	}

	void TransparentModel::Draw()
	{
		glPushMatrix();

		glTranslatef(m_transform.getPosition().x, m_transform.getPosition().y, m_transform.getPosition().z);
		glRotatef(m_transform.getRotation().getEuler().x, 1, 0, 0);
		glRotatef(m_transform.getRotation().getEuler().y, 0, 1, 0);
		glRotatef(m_transform.getRotation().getEuler().z, 0, 0, 1);
		glScalef(m_transform.getScale().x, m_transform.getScale().y, m_transform.getScale().z);

		ofEnableAlphaBlending();

		ofSetColor(255, 255, 255, static_cast<int>(255 * m_alpha));

		m_mesh.draw();

		ofDisableAlphaBlending();

		glPopMatrix();
	}

	void TransparentModel::setAlpha(float alpha)
	{

	}
}