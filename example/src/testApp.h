//ofxTextToImage, developed by Esteban Calcagno. 2014.
//
//ofxImageToText is an addons what allow convert letters of one o several texts
//in diferents images generating dinamics animations similar to particle system.
//
//This addon is based in ofxSoso.
//
//This addon was created for the instalation "Cortazar X 100" in conmemoration of centenary
//of Argentine writer Julio Cortazar.
//
//The texts used are fragments of various cortazar«s writings save in txt files into bin folder

#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
//Library for animate text
#include "ofxTextToImage.h"

//Library to file management (read and writer)
#include <fstream>

class testApp : public ofBaseApp{
	
public:
	
	void setup();
	void update();
	void draw();

	
	float 	counter;
	bool	bSmooth;
	
    ofTexture tex;
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxScene						*scene;
    
	ofxSosoTrueTypeFont             *font64;
	
    ofxImageObject					*image;

};

#endif

