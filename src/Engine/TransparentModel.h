#pragma once

#include "GameObject.h"

namespace engine
{
	class TransparentModel : public GameObject
	{
	public:
		inline TransparentModel(string filepath, float alpha) : m_filepath(filepath), m_alpha(alpha)
		{
		}
		~TransparentModel();
		virtual void Initialize() override;
		virtual void Draw() override;
		virtual void Update(float deltaTime) override;
		void setAlpha(float alpha);
	private:
		string m_filepath;
		float m_alpha;
		ofMesh m_mesh;
	};
}