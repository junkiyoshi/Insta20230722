#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 50, true, true, true);
	this->word = "01";
}

//--------------------------------------------------------------
void ofApp::update() {


}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	ofSeedRandom(39);
	for (int x = -500; x <= 450; x += 50){

		for (int y = -400; y <= 450; y += 50) {

			auto location = glm::vec3(x, y, 100);
			int word_index = ofMap(ofNoise(location.x * 0.005, location.y * 0.005, ofGetFrameNum() * 0.1), 0, 1, 0, this->word.size());

			ofPath chara_path = this->font.getCharacterAsPoints(this->word[word_index], true, false);
			vector<ofPolyline> outline = chara_path.getOutline();

			ofFill();
			ofSetColor(0);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				ofNextContour(true);

				outline[outline_index] = outline[outline_index].getResampledByCount(50);
				auto vertices = outline[outline_index].getVertices();
				for (auto& vertex : vertices) {

					glm::vec3 v = location + vertex;
					auto rotate_deg = ofMap(ofNoise(glm::length(v) * 0.002 - ofGetFrameNum() * 0.01), 0, 1, -360, 360);
					auto rotation = glm::rotate(glm::mat4(), rotate_deg * (float)DEG_TO_RAD, glm::vec3(1, 1, 1));
					v = glm::vec4(v, 0) * rotation;
					ofVertex(v);
				}
			}
			ofEndShape(true);

			ofNoFill();
			ofSetColor(255);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				ofNextContour(true);

				outline[outline_index] = outline[outline_index].getResampledByCount(50);
				auto vertices = outline[outline_index].getVertices();
				for (auto& vertex : vertices) {

					glm::vec3 v = location + vertex;
					auto rotate_deg = ofMap(ofNoise(glm::length(v) * 0.002 - ofGetFrameNum() * 0.01), 0, 1, -360, 360);
					auto rotation = glm::rotate(glm::mat4(), rotate_deg * (float)DEG_TO_RAD, glm::vec3(1, 1, 1));
					v = glm::vec4(v, 0) * rotation;
					ofVertex(v);
				}
			}
			ofEndShape(true);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}