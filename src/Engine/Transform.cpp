#include "Transform.h"

namespace engine
{
	Transform::Transform() :
		m_position(ofVec3f()),
		m_scale(ofVec3f(1,1,1)),
		m_rotation(ofQuaternion())
	{
	}

	Transform::Transform(const ofVec3f& tran) :
		m_position(ofVec3f(tran)),
		m_scale(ofVec3f(1,1,1)),
		m_rotation(ofQuaternion())
	{}

	Transform::Transform(const Transform& tran) :
		m_position(ofVec3f(tran.m_position)),
		m_scale(ofVec3f(tran.m_scale)),
		m_rotation(ofQuaternion(tran.m_rotation))
	{}

	Transform::~Transform()
	{
	}

	ofVec3f& Transform::getPosition()
	{
		return m_position;
	}

	ofVec3f& Transform::getScale()
	{
		return m_scale;
	}

	ofQuaternion& Transform::getRotation()
	{
		return m_rotation;
	}

	const ofVec3f& Transform::getEulerRotation() const
	{
		return m_rotation.getEuler();
	}

	void Transform::setPosition(const ofVec3f& position) {
		delete &m_position;
		m_position = position;
	}

	void Transform::setScale(const ofVec3f& scale) {
		delete &m_scale;
		m_scale = scale;
	}

	void Transform::setRotation(const ofQuaternion& rotation) {

		delete &m_rotation;
		m_rotation = rotation;
	}
}