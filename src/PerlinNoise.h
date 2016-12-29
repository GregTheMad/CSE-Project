#pragma once
#include "ofMath.h"
#include <math.h>

namespace game
{
	class PerlinNoise
	{
	protected:
		PerlinNoise(int seed);
	public:
		static PerlinNoise& getInstance();

		float FADE(float t);
		float LERP(float t, float a, float b);
		float GRAD1(int hash, float x);
		float GRAD2(int hash, float x, float y);
		float GRAD3(int hash, float x, float y, float z);
		float Noise1D(float x);
		float Noise2D(float x, float y);
		float Noise3D(float x, float y, float z);
		float FractalNoise1D(float x, int octNum, float frq, float amp);
		float FractalNoise2D(float x, float y, int octNum, float frq, float amp);
		float FractalNoise3D(float x, float y, float z, int octNum, float frq, float amp);
	private:
		const int B = 256;
		int* m_perm = new int[256 + 256];
	};
}
