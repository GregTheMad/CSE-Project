#include "LODModel.h"

namespace engine
{
	LODModel::~LODModel()
	{
	}

	void LODModel::Initialize()
	{
		m_mesh.load(m_filepath);
	};

	void LODModel::Draw()
	{
		glPushMatrix();
		
		glTranslatef(m_transform.getPosition().x, m_transform.getPosition().y, m_transform.getPosition().z);
		glRotatef(m_transform.getRotation().getEuler().x, 1, 0, 0);
		glRotatef(m_transform.getRotation().getEuler().y, 0, 1, 0);
		glRotatef(m_transform.getRotation().getEuler().z, 0, 0, 1);
		glScalef(m_transform.getScale().x, m_transform.getScale().y, m_transform.getScale().z);

		/*ofTranslate(m_transform.getPosition()->x, m_transform.getPosition()->y, m_transform.getPosition()->z);
		ofRotate(m_transform.getRotation()->getEuler().x, 1, 0, 0);
		ofRotate(m_transform.getRotation()->getEuler().y, 0, 1, 0);
		ofRotate(m_transform.getRotation()->getEuler().z, 0, 0, 1);
		ofScale(m_transform.getScale()->x, m_transform.getScale()->y, m_transform.getScale()->z);*/

		GLfloat matrix[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
		ofMatrix4x4 m(matrix);
		float f = m.getTranslation().length();

		for (size_t i = 0; i < m_meshs.size(); i++)
		{
			if (f < m_distances[i])
			{
				m_meshs[i].draw();
				break;
			}
		}

		glPopMatrix();
	};

	void LODModel::Update(float deltaTime)
	{

	};

	void LODModel::addLOD(string filepath, float maxDistance)
	{
		ofMesh m;
		m.load(filepath);
		m_meshs.push_back(m);
		m_distances.push_back(maxDistance);
	}
}