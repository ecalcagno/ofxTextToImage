//
//  ofxTextToImage.h
//  ofxTextToImage
//
//  Created by esteban on 1/15/15.
//
//

#include "ofxScene.h"
#include "ofxRectangleObject.h"
#include "ofxSosoRenderer.h"
#include "ofxImageObject.h"
#include "ofxTextObject.h"
#include "ofxLetterTextObject.h"
#include "ofxCircleObject.h"
#include "ofxAnimation.h"
#include "ofxLineSegmentObject.h"
#include "ofxDynamicPolygonObject.h"

void MoveText(ofxLetterTextObject *Text[], ofxLetterTextObject *Text1[],ofPoint ventana, vector <ofPoint> CurrentWindow, int NroTexto, float Time1, float Time2, int color);

void TextToImageConverter(int TextoInicial, int TextoFinal, ofxLetterTextObject *Text[], int Imagen,vector<ofImage> Images, vector<int> ImagePixelCounter, vector< vector <ofPoint> > PixelsPosition, vector <ofPoint> CurrentWindow, float escala, float pixel, float xcorr, float ycorr, float Time1, float Time2);

void TextInitPosition(ofxLetterTextObject *Text[], int NumberOfText);

void LettersExplotion(ofxLetterTextObject *Text[], int begin, int end);

void MoveNoise(ofxLetterTextObject *Text[], int NroTexto, float menor, float mayor, float Time1, float Time2);

void ShakeLetters(ofxLetterTextObject *Text[], int NroTexto, float menor, float mayor, float Time1, float Time2);

void FadeInText(ofxLetterTextObject *Text[], int NroTexto, float Time1, float Time2);

void FadeOutText(ofxLetterTextObject *Text[], int NroTexto, float Time1, float Time2);

void puntoLinea(ofxLetterTextObject *Text[], int TextoInicial, int TextoFinal, float pixel, float xcorr, float ycorr, float Time1, float Time2);
