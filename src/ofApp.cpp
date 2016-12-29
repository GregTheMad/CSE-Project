#include "ofApp.h"

using namespace std;

ofCamera cam;
bool keyIsDown[256];
game::Skybox sky;
ofVec3f _forward;
float speed;
float speedBoost;
float deltaTime;
float timeOfDay;
float durationOfDay;

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 255, 0);
	ofEnableLighting();
	_color = ofColor(100, 149, 237);
	//cam = new ofCamera();
	cam.setPosition(20, 20, 20);
	ofNode asdf;
	asdf.setPosition(0, 0, 0);
	cam.lookAt(asdf.getGlobalPosition());
	cam.setFov(90);
	cam.setNearClip(0.1f);
	cam.setFarClip(1000.0f);
	

	_sun.setDirectional();
	_sun.enable();
	_sun.setPosition(0, 1, 0);

	sky.initialize();

	speed = 5.0f;
	speedBoost = 3.0f;

	deltaTime = 1.0f / 60.0f;

	timeOfDay = 0;
	durationOfDay = 30;

	hm_ = new Heightmap(100, 20.0f);
	hm_->Initialize();
}

MarchingCube mc;

//--------------------------------------------------------------
void ofApp::update()
{
	if (keyIsDown['e'])
	{
		_color.g -= 100;
	}

	_forward = cam.getLookAtDir();
	
	ofVec3f right = _forward.getCrossed(ofVec3f(0, 1, 0));
	right.normalize();

	ofVec3f up = -_forward.getCrossed(right);
	up.normalize();

	float boost = 1;
	if(keyIsDown[0])
	{
		boost = speedBoost;
	}

	if (keyIsDown['w'])
	{
		cam.setPosition(cam.getPosition() + _forward * speed * boost * deltaTime);
	}
	if (keyIsDown['s'])
	{
		cam.setPosition(cam.getPosition() - _forward * speed * boost * deltaTime);
	}

	if (keyIsDown['d'])
	{
		cam.setPosition(cam.getPosition() + right * speed * boost * deltaTime);
	}
	if (keyIsDown['a'])
	{
		cam.setPosition(cam.getPosition() - right * speed * boost * deltaTime);
	}

	if (keyIsDown[' '])
	{
		cam.setPosition(cam.getPosition() + up * speed * boost * deltaTime);
	}
	if (keyIsDown['c'])
	{
		cam.setPosition(cam.getPosition() - up * speed * boost * deltaTime);
	}

	timeOfDay += deltaTime / durationOfDay;

	if (timeOfDay > 1.0f) timeOfDay -= 1.0f;
	else if (timeOfDay < 0.0f) timeOfDay += 1.0f;

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(_color);
	glLoadIdentity();

	gluLookAt(_forward.x, _forward.y, _forward.z, 0, 0, 0, 0, 1, 0);

	//Draw Skybox
	ofDisableLighting();
	sky.draw(timeOfDay);
	ofEnableLighting();

	//Set Tags for Maching Cube rendering
	glEnable(GL_CULL_FACE);
	ofEnableDepthTest();
	cam.begin();

	//Set Sun orientation
	_sun.setOrientation(ofVec3f(-timeOfDay * 360, 90, 0));
	
	//Draw Maching Cube Mesh
	mc.drawMesh();

	//Draw Icosphere to show lighting.
	//Sphere has to be drawn with radius of -2 to have the normals correctly (for some unknown reason)
	ofSetColor(255, 255, 255);
	ofDrawIcoSphere(8,8,8,-2);

	hm_->Draw();

	cam.end();
	ofDisableDepthTest();
	glDisable(GL_CULL_FACE);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	//put pressed keys into array to handle them in update loop
	if (key >= 0 && key <= 255)
	keyIsDown[key] = true;

	//The length you have to go to get something simple like the Shift key in a proper way ...
	if (key == 2305 || key == 2306)
		keyIsDown[0] = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	//remove released keys from array to not handle them in update loop
	if (key >= 0 && key <= 255)
	keyIsDown[key] = false;

	if (key == 2305 || key == 2306)
		keyIsDown[0] = false;
}

//--------------------------------------------------------------
float previous_x = 0;
float previous_y = 0;
bool mouse_set = false;
void ofApp::mouseMoved(int x, int y )
{
	//Make sure there are values to compare later on on the first frame.
	if (!mouse_set)
	{
		previous_x = x;
		previous_y = y;
		mouse_set = true;
	}

	//Check if mouse has moved very far (left the window on one side, and entered on the other) to prevent bad camera movement.
	if ((abs(previous_x - (float)x)) >= 100 || (abs(previous_y - (float)y)) >= 100)
	{
		previous_x = x;
		previous_y = y;
	}

	cam.setOrientation(cam.getOrientationEuler() + ofVec3f(0,(previous_x - (float)x)*0.2f,0));

	//Check angle to make sure camera doesn't flip over or devides by 0.
	float xOrentation = cam.getOrientationEuler().x + ((previous_y - (float)y)*0.2f);

	if (xOrentation > -85 && xOrentation < 85)
		cam.setOrientation(cam.getOrientationEuler() + ofVec3f((previous_y - (float)y)*0.2f, 0, 0));

	previous_x = x;
	previous_y = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
	previous_x = x;
	previous_y = y;
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
