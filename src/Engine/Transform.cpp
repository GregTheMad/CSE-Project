#include "Transform.h"

namespace engine
{
	Transform::Transform() :
		m_position(new ofVec3f()),
		m_scale(new ofVec3f(1,1,1)),
		m_rotation(new ofQuaternion())
	{
	}

	Transform::Transform(const ofVec3f& tran) :
		m_position(new ofVec3f(tran)),
		m_scale(new ofVec3f(1,1,1)),
		m_rotation(new ofQuaternion())
	{}

	Transform::Transform(const Transform& tran) :
		m_position(new ofVec3f(*tran.m_position)),
		m_scale(new ofVec3f(*tran.m_scale)),
		m_rotation(new ofQuaternion(*tran.m_rotation))
	{}

	Transform::~Transform()
	{
	}

	const ofVec3f* Transform::getPosition() const
	{
		return m_position;
	}

	const ofVec3f* Transform::getScale() const
	{
		return m_scale;
	}

	const ofQuaternion* Transform::getRotation() const
	{
		return m_rotation;
	}

	const ofVec3f* Transform::getEulerRotation() const
	{
		return &m_rotation->getEuler();
	}

	void Transform::setPosition(const ofVec3f& position) {
		delete m_position;
		*m_position = position;
	}

	void Transform::setScale(const ofVec3f& scale) {
		delete m_scale;
		*m_scale = scale;
	}

	void Transform::setRotation(const ofQuaternion& rotation) {

		delete m_rotation;
		*m_rotation = rotation;
	}
}