#pragma once
#include "ofMain.h"

namespace engine
{
	class Transform
	{
	public:
		explicit Transform();
		explicit Transform(const ofVec3f& tran);
		Transform(const Transform& tran);
		~Transform();
		ofVec3f& getPosition();
		ofVec3f& getScale();
		ofQuaternion& getRotation();
		const ofVec3f& getEulerRotation() const;
		void setPosition(const ofVec3f& position);
		void setScale(const ofVec3f& scale);
		void setRotation(const ofQuaternion& rotation);
		const ofMatrix4x4 getTransformMatrix() const;
	private:
		ofVec3f m_position;
		ofVec3f m_scale;
		ofQuaternion m_rotation;
	};
}