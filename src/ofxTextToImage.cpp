#include "ofxTextToImage.h"

//--------------------------------------------------------------
//MOVE TEXT
//Function for move texts to differents locations
void MoveText(ofxLetterTextObject *Text[], ofxLetterTextObject *Text1[],ofPoint ventana, vector <ofPoint> CurrentWindow, int NroTexto, float Time1, float Time2, int color)
{
    //Homes position for each part of text
    ofVec3f letterHome;
    int CounterPantalla1 = 0;
    Text[NroTexto]->setTrans(CurrentWindow[NroTexto].x, CurrentWindow[NroTexto].y, 0);
    
    
    for(int k=0; k < Text[NroTexto]->letters.size(); k++)
    {
        letterHome = Text1[NroTexto]->letters[k]->home;	//Grab letter home position.
        
        Text[NroTexto]->letters[k]->doMessage3f(OF_TRANSLATE, k*Time1, Time2, OF_EASE_OUT, (letterHome.x-CurrentWindow[NroTexto].x)+ventana.x, (letterHome.y - CurrentWindow[NroTexto].y) + ventana.y ,letterHome.z);
        
        CounterPantalla1++;
        
        //ESCALA
        Text[NroTexto]->letters[k]->doMessage1f(OF_SCALE, 0.05, 1, OF_EASE_OUT, 1);
        
        if(color == 1)
        {
            //COLOR
            Text[NroTexto]->letters[k]->doMessage3f(OF_SETCOLOR, 0.05, 1, OF_EASE_OUT, 255,255, 255);
        }
        
        Text[NroTexto]->letters[k]->home.x = (letterHome.x-CurrentWindow[52].x)+ventana.x;
        Text[NroTexto]->letters[k]->home.y = (letterHome.y - CurrentWindow[52].y) + ventana.y;
        
        
    }
    
    if(CounterPantalla1 == Text[NroTexto]->letters.size()-1)
    {
        CurrentWindow[NroTexto] = ventana;
        //Textos[0]->setTrans(VentanaActual[0].x, VentanaActual[0].y, 0);
        CounterPantalla1 = 0;
    }
    
}

//--------------------------------------------------------------
//TEXT TO IMAGE CONVERTER
//Function to convert text in image
void TextToImageConverter(int TextoInicial, int TextoFinal, ofxLetterTextObject *Text[], int Imagen, vector<ofImage> Images, vector<int> ImagePixelCounter, vector< vector <ofPoint> > PixelsPosition, vector <ofPoint> CurrentWindow, float escala, float pixel, float xcorr, float ycorr, float Time1, float Time2)
{
    for(int u=TextoInicial; u<TextoFinal; u++)
    {
        
        for(int k=0; k < Text[u]->letters.size(); k++)
        {
            //Hacemos que el posicionamiento de las letras sea ramdom
            int indice2 = ofRandom(0, ImagePixelCounter[Imagen]);
            
            
            //TEXTO
            Text[u]->letters[k]->doMessage3f(OF_TRANSLATE, k*Time1,Time2,OF_EASE_OUT,
                                             //POSICION X
                                             (PixelsPosition[Imagen][indice2].x - CurrentWindow[u].x + xcorr)*escala,
                                             //POSICION Y0
                                             (-PixelsPosition[Imagen][indice2].y + Images[Imagen].getHeight()/2 - CurrentWindow[u].y + ycorr)*escala,
                                             //POSICION Z
                                             0);
            
            //ESCALA
            Text[u]->letters[k]->doMessage1f(OF_SCALE, k*Time1, Time2, OF_EASE_OUT, pixel);
            //COLOR
            Text[u]->letters[k]->doMessage3f(OF_SETCOLOR, k*0.09, 0.1, OF_EASE_OUT, 255, 255, 255);
            
        }
    }
}

//--------------------------------------------------------------
//TEXT INIT POSITION
//Function to return a text to its initial position
void TextInitPosition(ofxLetterTextObject *Text[], int NumberOfText)
{
    //Homes position for each part of text
    ofVec3f letterHome;
    
    for(int u=0; u<NumberOfText;u++)
    {
        for(int i=0; i < Text[u]->letters.size(); i++)
        {
            
            
            //SE GUARDA LA POSICION INICIAL
            letterHome = Text[u]->letters[i]->home;	//Grab letter home position.
            
            //VOLVER AL PUNTO DE ORIGEN
            
            //TRANSLADAMOS
            Text[u]->letters[i]->doMessage3f(OF_TRANSLATE, 0.009, 1, OF_EASE_OUT, letterHome.x, letterHome.y,letterHome.z);
            
            Text[u]->letters[i]->doMessage1f(OF_SCALE, 0.009, 1, OF_EASE_OUT, 1);
            
            Text[u]->letters[i]->doMessage3f(OF_SETCOLOR, 0.009, 1, OF_EASE_OUT, 255, 255, 255);
        }
    }
}

//--------------------------------------------------------------
//LETTERS EXPLOTION
//Function to distribute letters of a texts simulating explotion effect
void LettersExplotion(ofxLetterTextObject *Text[], int begin, int end)
{
    int direction = 1;
    
    //Homes position for each part of text
    ofVec3f letterHome;
    
    for(int u=begin; u<end;u++)
    {
        
        for(int i=0; i < Text[u]->letters.size(); i++)
        {
            
            Text[u]->letters[i]->stopMessages();
            
            //VOLVER AL PUNTO DE ORIGEN
            
            //TRANSLADAMOS
            Text[u]->letters[i]->doMessage3f(OF_TRANSLATE, 0.09, 10, OF_EASE_OUT, direction*ofRandom(1000, 1500),ofRandom(-1000, 1000),letterHome.z);
            direction *= -1;
        }
    }
    
}

////////////////////////////////////////////////////////////////////////////
//MOVENOISE
void MoveNoise(ofxLetterTextObject *Text[], int NroTexto, float menor, float mayor, float Time1, float Time2)
{
    
    //Homes position for each part of text
    ofVec3f letterHome;
    
    for(int k=0; k < Text[NroTexto]->letters.size(); k++)
    {
        letterHome = Text[NroTexto]->letters[k]->home;	//Grab letter home position.
        
        Text[NroTexto]->letters[k]->doMessage3f(OF_TRANSLATE, k*Time1, Time2, OF_EASE_OUT, letterHome.x + ofRandom(menor,mayor), letterHome.y + ofRandom(menor,mayor) ,letterHome.z);
        
    }
}

//////////////////////////////////////////////////////////////////////////
//SHAKE LETTERS
//Functions to shake letters to a text
void ShakeLetters(ofxLetterTextObject *Text[], int NroTexto, float menor, float mayor, float Time1, float Time2)
{
    //ESCALA
    for(int k=0; k < Text[NroTexto]->letters.size(); k++)
    {
        Text[NroTexto]->letters[k]->doMessage1f(OF_SCALE, k*Time1, Time2, OF_EASE_OUT, ofRandom(0.5,2));
    }
}


////////////////////////////////////////////////////////////////////////////
//FADE IN TEXT
//Function to perform a fade-in effects to texts
void FadeInText(ofxLetterTextObject *Text[], int NroTexto, float Time1, float Time2)
{
    //COLOR
    for(int k=0; k < Text[NroTexto]->letters.size(); k++)
    {
        Text[NroTexto]->letters[k]->doMessage3f(OF_SETCOLOR, k*Time1, Time2, OF_EASE_OUT, 255, 255, 255);
    }
}

////////////////////////////////////////////////////////////////////////////
//FADE OUT TEXT
//Function to perform a fade-out effects to text
void FadeOutText(ofxLetterTextObject *Text[], int NroTexto, float Time1, float Time2)
{
    //COLOR
    for(int k=0; k < Text[NroTexto]->letters.size(); k++)
    {
        Text[NroTexto]->letters[k]->doMessage3f(OF_SETCOLOR, k*Time1, Time2, OF_EASE_OUT, 0, 0, 0);
    }
}

////////////////////////////////////////////////////////////////////////////
//PUNTOLINEA
void puntoLinea(ofxLetterTextObject *Text[], int TextoInicial, int TextoFinal, float pixel, float xcorr, float ycorr, float Time1, float Time2)
{
    for(int u=TextoInicial; u<TextoFinal; u++)
    {
        
        for(int k=0; k < Text[u]->letters.size(); k++)
        {
            
            
            
            //TEXTO
            Text[u]->letters[k]->doMessage3f(OF_TRANSLATE, k*Time1,Time2,OF_EASE_OUT,
                                             //POSICION X
                                             xcorr,
                                             //POSICION Y0
                                             ycorr,
                                             //POSICION Z
                                             0);
            
            //ESCALA
            Text[u]->letters[k]->doMessage1f(OF_SCALE, k*Time1, Time2, OF_EASE_OUT, pixel);
            
            
        }
    }
    
    
}
