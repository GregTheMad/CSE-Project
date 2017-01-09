#pragma once

#include "GameObject.h"

namespace engine
{
	class T2Model : public GameObject
	{
	public:
		inline T2Model(string filepath, float alpha) : m_filepath(filepath), m_alpha(alpha)
		{
		}
		~T2Model();
		virtual void Initialize() override;
		virtual void Draw() override;
		virtual void Update(float deltaTime) override;
		void setAlpha(float alpha);
	private:
		string m_filepath;
		float m_alpha;
		ofMesh m_mesh;

		std::vector<ofMeshFace> f;
	};
}
