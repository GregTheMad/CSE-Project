#pragma once
#include "GameObject.h"

namespace engine
{
	class LODModel :
		public GameObject
	{
	public:
		inline LODModel(string name, size_t lodLevels) : m_name(name), m_lodLevels(lodLevels)
		{};
		~LODModel();
		virtual void Initialize() override;
		virtual void Draw() override;
		virtual void Update(float deltaTime) override;
		void addLOD(string filepath, float maxDistance);
	private:
		string m_name;
		size_t m_lodLevels;
		vector<ofMesh> m_meshs;
		vector<float> m_distances;
	};
}