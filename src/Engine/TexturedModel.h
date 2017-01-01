#pragma once

#include "GameObject.h"
#include "ofxAssimpModelLoader.h"

namespace engine
{
	enum class TextureType {
		Diffuse,
		Normal,
		AmbientOcclusion
	};

	class TexturedModel : public GameObject
	{
	public:
		TexturedModel(string filepath);
		inline ~TexturedModel() {};
		virtual void Initialize() override;
		virtual void Draw() override;
		virtual void Update(float deltaTime) override;
		void addTexture(engine::TextureType type, string filepath);
	private:
		string m_diffuse_path;
		ofTexture m_diffuse;
		string m_mesh_path;
		ofMesh m_mesh;
	};
}