#include "MarchingCube.h"

using namespace std;

void MarchingCube::drawMesh()
{
	int size = 16;

	GLint iX, iY, iZ;
	for (iX = 0; iX < size; iX++)
		for (iY = 0; iY < size; iY++)
			for (iZ = 0; iZ < size; iZ++)
			{
				_marchCube(iX*1, iY*1, iZ*1, 1);
			}
}

GLvoid MarchingCube::_marchCube(GLfloat fX, GLfloat fY, GLfloat fZ, GLfloat fScale)
{
	//extern GLint aiCubeEdgeFlags[256];
	//extern GLint a2iTriangleConnectionTable[256][16];

	GLint iCorner, iVertex, iVertexTest, iEdge, iTriangle, iFlagIndex, iEdgeFlags;
	GLfloat fOffset;
	ofColor sColor;
	GLfloat afCubeValue[8];
	ofVec3f asEdgeVertex[12];
	ofVec3f asEdgeNorm[12];

	//Make a local copy of the values at the cube's corners
	for (iVertex = 0; iVertex < 8; iVertex++)
	{
		afCubeValue[iVertex] = _sample(fX + a2fVertexOffset[iVertex][0] * fScale,
			fY + a2fVertexOffset[iVertex][1] * fScale,
			fZ + a2fVertexOffset[iVertex][2] * fScale);
	}

	//Find which vertices are inside of the surface and which are outside
	iFlagIndex = 0;
	for (iVertexTest = 0; iVertexTest < 8; iVertexTest++)
	{
		if (afCubeValue[iVertexTest] <= targetValue)
			iFlagIndex |= 1 << iVertexTest;
	}

	//Find which edges are intersected by the surface
	iEdgeFlags = aiCubeEdgeFlags[iFlagIndex];

	//If the cube is entirely inside or outside of the surface, then there will be no intersections
	if (iEdgeFlags == 0)
	{
		return;
	}

	//Find the point of intersection of the surface with each edge
	//Then find the normal to the surface at those points
	for (iEdge = 0; iEdge < 12; iEdge++)
	{
		//if there is an intersection on this edge
		if (iEdgeFlags & (1 << iEdge))
		{
			fOffset = _getOffset(afCubeValue[a2iEdgeConnection[iEdge][0]],
				afCubeValue[a2iEdgeConnection[iEdge][1]], targetValue);

			asEdgeVertex[iEdge].x = fX + (a2fVertexOffset[a2iEdgeConnection[iEdge][0]][0] + fOffset * a2fEdgeDirection[iEdge][0]) * fScale;
			asEdgeVertex[iEdge].y = fY + (a2fVertexOffset[a2iEdgeConnection[iEdge][0]][1] + fOffset * a2fEdgeDirection[iEdge][1]) * fScale;
			asEdgeVertex[iEdge].z = fZ + (a2fVertexOffset[a2iEdgeConnection[iEdge][0]][2] + fOffset * a2fEdgeDirection[iEdge][2]) * fScale;

			_getNormal(asEdgeNorm[iEdge], asEdgeVertex[iEdge].x, asEdgeVertex[iEdge].y, asEdgeVertex[iEdge].z);
		}
	}


	//Draw the triangles that were found.  There can be up to five per cube
	for (iTriangle = 0; iTriangle < 5; iTriangle++)
	{
		if (a2iTriangleConnectionTable[iFlagIndex][3 * iTriangle] < 0)
			break;

		glBegin(GL_POLYGON);
		for (iCorner = 0; iCorner < 3; iCorner++)
		{
			iVertex = a2iTriangleConnectionTable[iFlagIndex][3 * iTriangle + iCorner];

			
			_getColor(sColor, asEdgeVertex[iVertex], asEdgeNorm[iVertex]);
			glColor3f(sColor.r, sColor.g, sColor.b);
			glNormal3f(asEdgeNorm[iVertex].x, asEdgeNorm[iVertex].y, asEdgeNorm[iVertex].z);
			glVertex3f(asEdgeVertex[iVertex].x, asEdgeVertex[iVertex].y, asEdgeVertex[iVertex].z);
			
		}
		glEnd();
	}
}

GLfloat MarchingCube::_sample(GLfloat fX, GLfloat fY, GLfloat fZ)
{
	GLfloat fHeight = 20.0*(seed + sqrt((0.5 - fX)*(0.5 - fX) + (0.5 - fZ)*(0.5 - fZ)));
	fHeight = 1.5 + 0.1*(sinf(fHeight) + cosf(fHeight));
	GLdouble fResult = (fHeight - fY)*50.0;

	//if (fX < 0.01f || fX > 15.99f) fResult = 0;
	//if (fY < 0.01f || fY > 15.99f) fResult = 0;
	//if (fZ < 0.01f || fZ > 15.99f) fResult = 0;

	//cout << fY << "\n";
	//fResult = sinf(fX*360) * sinf(fZ* 360) * cosf(fY* 360);
	//else fResult = 0.1f;

	return fResult;
	//return game::PerlinNoise::getInstance().Noise3D(fX, fY, fZ);
	//return 0.1f;
	/*float r = sinf(fX) * cosf(fZ) * sinf(fY);

	r = CLAMP(r, 0, 1);

	return r;

	ofVec3f source0 = ofVec3f(0, 0, 0);
	ofVec3f source1 = ofVec3f(1, 1, 1);
	ofVec3f source2 = ofVec3f(0, -1, 0);

	/*GLdouble fResult = 0.0;
	GLdouble fDx, fDy, fDz;
	fDx = fX - source0.x;
	fDy = fY - source0.y;
	fDz = fZ - source0.z;
	fResult += 0.5 / (fDx*fDx + fDy*fDy + fDz*fDz);

	fDx = fX - source1.x;
	fDy = fY - source1.y;
	fDz = fZ - source1.z;
	fResult += 1.0 / (fDx*fDx + fDy*fDy + fDz*fDz);

	fDx = fX - source2.x;
	fDy = fY - source2.y;
	fDz = fZ - source2.z;
	fResult += 1.5 / (fDx*fDx + fDy*fDy + fDz*fDz);

	return fResult;

	GLdouble fResult = 0.0;
	GLdouble fDx, fDy, fDz;
	fDx = fX - source0.x;
	fDy = fY - source0.y;
	fResult += 0.5 / (fDx*fDx + fDy*fDy);

	fDx = fX - source1.x;
	fDz = fZ - source1.z;
	fResult += 0.75 / (fDx*fDx + fDz*fDz);

	fDy = fY - source2.y;
	fDz = fZ - source2.z;
	fResult += 1.0 / (fDy*fDy + fDz*fDz);

	return fResult;*/
}

//vGetNormal() finds the gradient of the scalar field at a point
//This gradient can be used as a very accurate vertx normal for lighting calculations
GLvoid MarchingCube::_getNormal(ofVec3f &rfNormal, GLfloat fX, GLfloat fY, GLfloat fZ)
{
	rfNormal.x = _sample(fX - 0.01, fY, fZ) - _sample(fX + 0.01, fY, fZ);
	rfNormal.y = _sample(fX, fY - 0.01, fZ) - _sample(fX, fY + 0.01, fZ);
	rfNormal.z = _sample(fX, fY, fZ - 0.01) - _sample(fX, fY, fZ + 0.01);
	//vNormalizeVector(rfNormal, rfNormal);
	rfNormal.normalize();
}

//vGetColor generates a color from a given position and normal of a point
GLvoid MarchingCube::_getColor(ofColor &rfColor, ofVec3f &rfPosition, ofVec3f &rfNormal)
{
	GLfloat fX = rfNormal.x;
	GLfloat fY = rfNormal.y;
	GLfloat fZ = rfNormal.z;
	rfColor.r = (fX > 0.0 ? fX : 0.0) + (fY < 0.0 ? -0.5*fY : 0.0) + (fZ < 0.0 ? -0.5*fZ : 0.0);
	rfColor.g = (fY > 0.0 ? fY : 0.0) + (fZ < 0.0 ? -0.5*fZ : 0.0) + (fX < 0.0 ? -0.5*fX : 0.0);
	rfColor.b = (fZ > 0.0 ? fZ : 0.0) + (fX < 0.0 ? -0.5*fX : 0.0) + (fY < 0.0 ? -0.5*fY : 0.0);
}

//fGetOffset finds the approximate point of intersection of the surface
// between two points with the values fValue1 and fValue2
GLfloat MarchingCube::_getOffset(GLfloat fValue1, GLfloat fValue2, GLfloat fValueDesired)
{
	GLdouble fDelta = fValue2 - fValue1;

	if (fDelta == 0.0)
	{
		return 0.5;
	}
	return (fValueDesired - fValue1) / fDelta;
}

