#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetLineWidth(2);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	ofColor color;
	vector<int> hex_list = { 0x247BA0, 0x70C1B3, 0xB2DBBF, 0xF3FFBD, 0xFF1654 };
	for (auto hex : hex_list) {

		color.setHex(hex);
		this->color_list.push_back(color);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	int span = 180;
	auto radius = 80;
	for (int x = span * 0.5; x < ofGetWidth() + span * 0.5; x += span) {

		for (int y = span * 0.5; y < ofGetHeight() + span * 0.5; y += span) {

			ofPushMatrix();
			ofTranslate(x, y);

			int color_index = ofRandom(this->color_list.size());

			for (int i = 0; i < 6; i++) {

				vector<glm::vec2> vertices;
				for (int k = 0; k < 3; k++) {

					auto deg = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, -360, 360);
					vertices.push_back(glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));

					ofFill();
					ofSetColor(this->color_list[color_index]);
					ofDrawCircle(vertices.back(), 3);
				}

				ofFill();
				ofSetColor(this->color_list[color_index], 180);
				ofBeginShape();
				ofVertices(vertices);
				ofEndShape(true);

				ofNoFill();
				ofSetColor(this->color_list[color_index]);
				ofBeginShape();
				ofVertices(vertices);
				ofEndShape(true);

				color_index = (color_index + 1) % this->color_list.size();
			}

			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}