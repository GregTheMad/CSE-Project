#pragma once
#include "GameObject.h"

namespace engine
{
	class LODModel :
		public GameObject
	{
	public:
		inline LODModel(string filepath, size_t lodLevels) : m_filepath(filepath), m_lodLevels(lodLevels)
		{};
		~LODModel();
		virtual void Initialize() override;
		virtual void Draw() override;
		virtual void Update(float deltaTime) override;
		void addLOD(string filepath, float maxDistance);
	private:
		string m_filepath;
		size_t m_lodLevels;
		ofMesh m_mesh;
		vector<ofMesh> m_meshs;
		vector<float> m_distances;
	};
}