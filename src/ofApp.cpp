#include "ofApp.h"

using namespace std;

ofCamera cam;
bool keyIsDown[256];
ofVec3f _forward;
float speed;
float speedBoost;
float deltaTime;

engine::T2Model* ttest;
engine::T2Model* ttest2;

ofApp::~ofApp() {
	for (vector<engine::GameObject*>::iterator m = scene.begin(); m != scene.end(); m++)
	{
		delete *m;
	}

	scene.clear();
}

//--------------------------------------------------------------
void ofApp::setup(){

	ofEnableNormalizedTexCoords();
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

	speed = 5.0f;
	speedBoost = 3.0f;

	deltaTime = 1.0f / 60.0f;

	m_skybox = new engine::Skybox();
	m_skybox->Initialize();
	m_skybox->DurationOfDay = 30;

	hm_ = new engine::Heightmap(100, 20.0f);
	hm_->Initialize();

	scene.push_back(new engine::TexturedModel("Models/Bunny_T.ply"));
	dynamic_cast<engine::TexturedModel*>(scene.back())->addTexture(engine::TextureType::Diffuse, "Textures/Bunny_N.png");
	scene.back()->m_transform.getPosition() = ofVec3f(0, 10, 0);
	scene.back()->m_transform.getRotation() *= ofQuaternion(-90, ofVec3f(1, 0, 0));
	scene.back()->Initialize();

	//engine::LODModel t = engine::LODModel("Models/Suzanne0.ply", 0);

	//testmodel = new engine::LODModel("Models/Suzanne0.ply", 0);

	//dynamic_cast<engine::LODModel*>(testmodel)->addLOD("Models/Suzanne0.ply", 10.0f);
	//dynamic_cast<engine::LODModel*>(testmodel)->addLOD("Models/Suzanne1.ply", 20.0f);
	//dynamic_cast<engine::LODModel*>(testmodel)->addLOD("Models/Suzanne2.ply", 3000.0f);
	////testmodel->Initialize();

	scene.push_back(new engine::LODModel("Dragon", 0));
	dynamic_cast<engine::LODModel*>(scene.back())->addLOD("Models/Dragon0.ply", 10.0f);
	dynamic_cast<engine::LODModel*>(scene.back())->addLOD("Models/Dragon1.ply", 20.0f);
	dynamic_cast<engine::LODModel*>(scene.back())->addLOD("Models/Dragon2.ply", 3000.0f);
	scene.back()->m_transform.getPosition() = ofVec3f(-10, 10, 10);
	scene.back()->m_transform.getScale() = ofVec3f(2, 2, 2);

	scene.push_back(new engine::LODModel("Bunny", 0));
	dynamic_cast<engine::LODModel*>(scene.back())->addLOD("Models/Bunny0.ply", 10.0f);
	dynamic_cast<engine::LODModel*>(scene.back())->addLOD("Models/Bunny1.ply", 20.0f);
	dynamic_cast<engine::LODModel*>(scene.back())->addLOD("Models/Bunny2.ply", 3000.0f);
	scene.back()->m_transform.getPosition() = ofVec3f(0, 10, 10);
	scene.back()->m_transform.getScale() = ofVec3f(2, 2, 2);

	scene.push_back(new engine::LODModel("Horse", 0));
	dynamic_cast<engine::LODModel*>(scene.back())->addLOD("Models/Horse0.ply", 10.0f);
	dynamic_cast<engine::LODModel*>(scene.back())->addLOD("Models/Horse1.ply", 20.0f);
	dynamic_cast<engine::LODModel*>(scene.back())->addLOD("Models/Horse2.ply", 3000.0f);
	scene.back()->m_transform.getPosition() = ofVec3f(-20, 10, 10);
	scene.back()->m_transform.getScale() = ofVec3f(2, 2, 2);

	scene.push_back(new engine::LODModel("BunnySkeleton", 0));
	dynamic_cast<engine::LODModel*>(scene.back())->addLOD("Models/BunnyS.ply", 100.0f);
	scene.back()->m_transform.getPosition() = ofVec3f(0, 10, 20);
	scene.back()->m_transform.getScale() = ofVec3f(2, 2, 2);

	//Transparent Objects
	transparentScene.push_back(new engine::TransparentModel("Models/Bunny0.ply", 0.5f));
	transparentScene.back()->m_transform.getPosition() = ofVec3f(0, 10, 20);
	transparentScene.back()->m_transform.getScale() = ofVec3f(2, 2, 2);

	transparentScene.push_back(new engine::TransparentModel("Models/Dragon0.ply", 0.8f));
	transparentScene.back()->m_transform = engine::Transform(ofVec3f(-10.0f, 10.0f, 20.0f));
	transparentScene.back()->m_transform.getScale() = ofVec3f(2, 2, 2);

	transparentScene.push_back(new engine::TransparentModel("Models/Horse0.ply", 0.8f));
	transparentScene.back()->m_transform = engine::Transform(ofVec3f(-20.0f, 10.0f, 20.0f));
	transparentScene.back()->m_transform.getScale() = ofVec3f(2, 2, 2);

	//tRenderingOrder = *new map<float, int>();
	//tRenderingOrder.clear();

	//Initializing
	for (vector<engine::GameObject*>::iterator m = scene.begin(); m != scene.end(); m++)
	{
		dynamic_cast<engine::GameObject*>(*m)->Initialize();
	}

	for (vector<engine::GameObject*>::iterator m = transparentScene.begin(); m != transparentScene.end(); m++)
	{
		dynamic_cast<engine::GameObject*>(*m)->Initialize();
	}

	cout << "test";
}

MarchingCube mc;

//--------------------------------------------------------------
void ofApp::update()
{
	deltaTime = ofGetLastFrameTime();

	m_skybox->Update(deltaTime);

	/*for (vector<engine::GameObject*>::iterator m = scene.begin(); m != scene.end(); m++)
	{
		dynamic_cast<engine::GameObject*>(*m)->Update(deltaTime);
	}*/

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
	else if (keyIsDown['s'])
	{
		cam.setPosition(cam.getPosition() - _forward * speed * boost * deltaTime);
	}

	if (keyIsDown['d'])
	{
		cam.setPosition(cam.getPosition() + right * speed * boost * deltaTime);
	}
	else if (keyIsDown['a'])
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
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(_color);
	glLoadIdentity();

	glPushMatrix();
	gluLookAt(_forward.x, _forward.y, _forward.z, 0, 0, 0, 0, 1, 0);
	//Draw Skybox	
	m_skybox->Draw();	
	glPopMatrix();

	//Set Tags for Maching Cube rendering
	glEnable(GL_CULL_FACE);
	ofEnableDepthTest();
	cam.begin();

	//Set Sun orientation
	_sun.setOrientation(ofVec3f(-m_skybox->TimeOfDay * 360, 90, 0));
	
	//Draw Maching Cube Mesh
	//mc.drawMesh();

	//Draw Icosphere to show lighting.
	//Sphere has to be drawn with radius of -2 to have the normals correctly (for some unknown reason)
	ofSetColor(255, 255, 255);
	ofDrawIcoSphere(8,8,8,-2);
	
	hm_->Draw();
	//testmodel->Draw();

	for (vector<engine::GameObject*>::iterator m = scene.begin(); m != scene.end(); m++)
	{
		dynamic_cast<engine::GameObject*>(*m)->Draw();
	}
	
	//ttest->Draw();
	//ttest2->Draw();

	for (vector<engine::GameObject*>::iterator m = scene.begin(); m != scene.end(); m++)
	{
		dynamic_cast<engine::GameObject*>(*m)->Draw();
	}

	float f;
	
	//for (vector<engine::GameObject*>::iterator m = transparentScene.begin(); m != transparentScene.end(); m++)
	for (size_t i = 0; i < transparentScene.size(); i++)
	{
		//dynamic_cast<engine::GameObject*>(*m)->Draw();
		f = ofVec3f(transparentScene[i]->m_transform.getPosition() - cam.getPosition()).length();

		tRenderingOrder.insert(make_pair(-f, i));
	}

	//for (auto m = tRenderingOrder.end(); m != tRenderingOrder.begin(); m--)
	for (auto m : tRenderingOrder)
	{
		transparentScene[m.second]->Draw();
	}
	tRenderingOrder.clear();

	cam.end();
	ofDisableDepthTest();
	glDisable(GL_CULL_FACE);

	//Drawing UI
	glLoadIdentity();
	ofSetColor(255, 0, 0, 255);
	ofDrawBitmapString("Frametime: " + std::to_string(ofGetLastFrameTime()), 10, 10, 10);
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
void ofApp::mouseMoved(int x, int y )
{
	
}

//--------------------------------------------------------------
float previous_x = 0;
float previous_y = 0;
bool mouse_set = false;
void ofApp::mouseDragged(int x, int y, int button){
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

	cam.setOrientation(cam.getOrientationEuler() + ofVec3f(0, (previous_x - (float)x)*0.2f, 0));

	//Check angle to make sure camera doesn't flip over or devides by 0.
	float xOrentation = cam.getOrientationEuler().x + ((previous_y - (float)y)*0.2f);

	if (xOrentation > -85 && xOrentation < 85)
		cam.setOrientation(cam.getOrientationEuler() + ofVec3f((previous_y - (float)y)*0.2f, 0, 0));

	previous_x = x;
	previous_y = y;
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
