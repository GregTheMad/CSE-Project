#pragma once

#include "ofMain.h"
#include "ofMath.h"
#include "MarchingCube.h"
#include "Skybox.h"
#include "engine/engine.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		~ofApp();
private:
	ofColor _color;
	ofLight _sun;

	engine::Skybox* m_skybox;

	engine::GameObject* hm_;
	engine::GameObject* testmodel;

	vector<engine::GameObject*> scene;
	vector<engine::GameObject*> transparentScene;
	map<float, int> tRenderingOrder;	
};
