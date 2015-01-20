#include "testApp.h"

//Position of pixels of each images
vector< vector <ofPoint> > posicionesPixeles;
vector< vector <ofPoint> > pixelesImagenes;

vector<int> indicesPosiciones;

vector<int> contadorPosicionPixeles;
vector<int> contadorPixelesImagenes;

//IMAGES

//Number of images load
int cantidadImagenes = 40;

//Vector for images
vector<ofImage> imagenes;

//Vector for pixels of images
vector<ofPixels> pixeles;

//Vector for colors of pixels of images
vector<ofColor> colores;

//TEXTS

//Number of texts load
int cantidadTextos = 72;


vector<string> strs;
ofxLetterTextObject *Textos[72];
ofxLetterTextObject *Textos1[72];

ifstream fin[72];

//MODOS

int ImagenActual;

//POSICION TEXTOS
ofPoint PosTexto0;
ofPoint PosTexto1;

//UMBRAL DE EXTRACCION Y TAMA„O DE PIXEL
int UmbralPixeles = 60;
float PixelSize = 0.6;

//Arbitrary position of text fragments, indicated as windows
ofPoint Ventana1 = ofVec3f(-350,350);
ofPoint Ventana2 = ofVec3f(-130,350);
ofPoint Ventana3 = ofVec3f(90,350);
ofPoint Ventana4 = ofVec3f(310,350);

ofPoint Ventana5 = ofVec3f(-350,90);
ofPoint Ventana6 = ofVec3f(-130,90);
ofPoint Ventana7 = ofVec3f(90,90);
ofPoint Ventana8 = ofVec3f(310,90);

ofPoint Ventana9 = ofVec3f(-350,-200);
ofPoint Ventana10 = ofVec3f(-130,-200);
ofPoint Ventana11 = ofVec3f(90,-200);
ofPoint Ventana12 = ofVec3f(310,-200);

//Off the screen positions
ofPoint FueraDeCuadroIzquierda = ofVec3f(-350,0);
ofPoint FueraDeCuadroDerecha = ofVec3f(350,0);
ofPoint FueraDeCuadroArriba = ofVec3f(0,400);
ofPoint FueraDeCuadroAbajo = ofVec3f(0,-400);

//Current window where each text is positioned
vector <ofPoint> VentanaActual;

//POSICIONES ORIGINALES DE LOS TEXTOS
//DIVIDO POR FILAS Y COLUMNAS
// 1 2  3  4
// 5 6  7  8
// 9 10 11 12

//COLUMNA 1-5-9
//CASILLA 1 -> x = -275; y = 275
//CASILLA 5 -> x = -275; y = 90
//CASILLA 9 -> x = -275; y = -160

//COLUMNA 2-6-10
//CASILLA 2 -> x = -110; y = 275
//CASILLA 6 -> x = -100 y = 90
//CASILLA 10 -> x = -100; y = -160

//COLUMNA 3-7-11
//CASILLA 3 -> x = 70; y = 275
//CASILLA 7 -> x = 70; y = 90
//CASILLA 11 -> x = 70; y = -160

//COLUMNA 4-8-12
//CASILLA 4 -> x = 240; y = 275
//CASILLA 8 -> x = 240; y = 90
//CASILLA 12 -> x = 240; y = 160

float EscalaImagen = 0.3;
int escena = 0;

float timeEscena1=0;
float timeEscena2=0;
float timeEscena3=0;
float timeEscena4=0;
float timeEscena5=0;
float timeEscena6=0;
float timeEscena7=0;


//IMAGENES DE LA PRIMERA PARTE
int noImage = 0;
float timeEscena0 = 0;

float tiempo = 0;

int tiemble = 0;
int tiemble2 = 0;




int block1 = 0;
int block2 = 0;
int block3 = 0;
int block4 = 0;
int block5 = 0;
int block6 = 0;

int GeneralBloqued = 0;

//--------------------------------------------------------------
void testApp::setup(){

	ofSetWindowTitle("CORTAZARx100");
	
    //Replace the default ofGLRenderer with ofxSosoRenderer which has overriden setupScreen() and setupScreenPerspective().
	//This lets us set up the scene graph how we want to.
	//Warning: Up is up and down is down in this world.
    ofSetCurrentRenderer(ofPtr<ofBaseRenderer>(new ofxSosoRenderer(false)));
    
    //Create a scene.
	//The scene is a scene graph that renders objects added to its root and their children and their children's children and so on.
	//When the render mode of the scene is set to RENDER_ALPHA_DEPTH_SORTED, it handles sorting of both transparent and opaque objects in the z-axis.
    scene = new ofxScene(ofGetWidth(), ofGetHeight());
	scene->setBackgroundColor(0, 0, 0);
    
    
    
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    //REDIMENSIONO LOS VECTORES SEGUN LA CANTIDAD DE IMAGENES Y TEXTO
    imagenes.resize(cantidadImagenes);
    posicionesPixeles.resize(cantidadImagenes);
    pixelesImagenes.resize(cantidadImagenes);
    pixeles.resize(cantidadImagenes);
    contadorPosicionPixeles.resize(cantidadImagenes);
    contadorPixelesImagenes.resize(cantidadImagenes);
    colores.resize(cantidadImagenes);
    strs.resize(cantidadTextos);
    VentanaActual.resize(cantidadTextos);
    
    ///////////////////////////////////////////////////////////////////////
    
    //Inicializo contadores
    contadorPosicionPixeles[0] = 0;
    contadorPixelesImagenes[0] = 0;

    //imagenes a procesar;
    for(int repeticiones = 0; repeticiones<cantidadImagenes; repeticiones++)
    {
        imagenes[repeticiones].loadImage("imagenes/cortazar" + ofToString(repeticiones) + ".jpg");
        
        
        //imagenes[repeticiones].resize(200,333);
        
        //get the pixels from the image
        pixeles[repeticiones] = imagenes[repeticiones].getPixelsRef();
        
        
        
        for (int i = 0; i < posicionesPixeles.size(); i++)
        {
            posicionesPixeles[i].resize(imagenes[repeticiones].getWidth() * imagenes[repeticiones].getHeight());
        }
        
        for (int i = 0; i < pixelesImagenes.size(); i++)
        {
            pixelesImagenes[i].resize(imagenes[repeticiones].getWidth() * imagenes[repeticiones].getHeight());
        }
        
        
        //let's manipulate the pixels by iterating through them
        //or a rough bluescreen
        for(int y = 0; y < imagenes[repeticiones].getHeight(); y++)
        {
            for(int x = 0; x < imagenes[repeticiones].getWidth(); x++)
            {
                //if the blue is greater than the combination of  red and green together, delete that pixel
                colores[repeticiones] = imagenes[repeticiones].getColor(x, y);
                
                if(colores[repeticiones].b > UmbralPixeles && colores[repeticiones].g > UmbralPixeles && colores[repeticiones].r > UmbralPixeles)
                {
                    pixeles[repeticiones].setColor(x, y, ofColor::white);
                }
                
                if(colores[repeticiones].b < UmbralPixeles && colores[repeticiones].g < UmbralPixeles && colores[repeticiones].r < UmbralPixeles)
                {
                    pixelesImagenes[repeticiones][contadorPixelesImagenes[repeticiones]] = ofPoint(x, y, 0);
                    contadorPixelesImagenes[repeticiones]++;
                }
                
            }
            
        }
        
        contadorPosicionPixeles[repeticiones] = contadorPixelesImagenes[repeticiones];
        
        for(int p = 0; p < contadorPixelesImagenes[repeticiones]; p++)
        {
            
            posicionesPixeles[repeticiones][contadorPosicionPixeles[repeticiones]].x = pixelesImagenes[repeticiones][p].x;
            posicionesPixeles[repeticiones][contadorPosicionPixeles[repeticiones]].y = pixelesImagenes[repeticiones][p].y;
            contadorPosicionPixeles[repeticiones]--;
        }
        
    }
    
    //Load a font.
	//ofxSosoTrueTypeFont inherits from ofTrueTypeFont and adds some nice functionality, used by ofxTextObject.
	//Note: If the font has them, kerning pairs are loaded by default.
    
	font64 = new ofxSosoTrueTypeFont();
    font64->loadFont("typewriter.ttf", 24, true,  true, false, true);
    ///////////////////////////////////////////////////////////////////////
    //LEEMOS ARCHIVOS DE TEXTO Y LO METEMOS EN UN STRING
    
    for(int i = 0; i < cantidadTextos; i++)
    {
        
        fin[i].open( ofToDataPath("textos/texto" + ofToString(i) + ".txt").c_str() ); //open your text file
        
        while(fin[i]!=NULL) //as long as theres still text to be read
        {
            getline(fin[i], strs[i]); //get a line from the file, put it in the string
        }
        
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        //TEXTO1 - hay que castear por que sino no funca
        Textos[i] = new ofxLetterTextObject(font64, (char*) strs[i].c_str());
        Textos[i]->setTrans(0, 0, 0);
        Textos[i]->setColor(0, 0, 0);
        Textos[i]->setPointSize(12);
        Textos[i]->setLeading(12);
        Textos[i]->setColumnWidth(180);
        Textos[i]->setAlignment(OF_TEXT_ALIGN_LEFT);
        scene->getRoot()->addChild(Textos[i]);
        
        
        //TEXTOS-copia
        Textos1[i] = new ofxLetterTextObject(font64, (char*) strs[i].c_str());
        Textos1[i]->setTrans(0, 0, 0);
        Textos1[i]->setColor(0, 0, 0);
        Textos1[i]->setPointSize(12);
        Textos1[i]->setLeading(12);
        Textos1[i]->setColumnWidth(180);
        Textos1[i]->setAlignment(OF_TEXT_ALIGN_LEFT);
        
    }

    //Initial position of all text, outside the screen
    for(int k = 0; k < cantidadTextos; k++)
    {
    VentanaActual[k] = FueraDeCuadroAbajo;
        
    Textos[k]->setTrans(VentanaActual[k].x, VentanaActual[0].y, 0);
    Textos1[k]->setTrans(VentanaActual[k].x, VentanaActual[0].y, 0);
    }
    


}

//--------------------------------------------------------------
void testApp::update(){
    
	//Update the scene with the current time. This call propagates the idle() call to all objects as well.
	//Note: If you are capturing frames to create a movie, simply replace ofGetElapsedTimef() with a float variable that you increment by a fixed time interval each frame.
    scene->update(ofGetElapsedTimef());

}

//--------------------------------------------------------------
void testApp::draw(){

    //#################################################################################
    //#################################################################################
    //TEST: for this test used 12 text and 4 images.

        //Move different text to different locations
        if(GeneralBloqued == 1)
        {
            MoveText(Textos, Textos1,Ventana1, VentanaActual, 0, 0.1, 1, 1);
            MoveText(Textos, Textos1,Ventana2, VentanaActual, 1, 0.1, 1, 1);
            MoveText(Textos, Textos1,Ventana3, VentanaActual, 2, 0.1, 1, 1);
            MoveText(Textos, Textos1,Ventana4, VentanaActual, 3, 0.1, 1, 1);
            MoveText(Textos, Textos1,Ventana5, VentanaActual, 4, 0.1, 1, 1);
            MoveText(Textos, Textos1,Ventana6, VentanaActual, 5, 0.1, 1, 1);
            MoveText(Textos, Textos1,Ventana7, VentanaActual, 6, 0.1, 1, 1);
            MoveText(Textos, Textos1,Ventana8, VentanaActual, 7, 0.1, 1, 1);
            MoveText(Textos, Textos1,Ventana9, VentanaActual, 8, 0.1, 1, 1);
            MoveText(Textos, Textos1,Ventana10, VentanaActual, 9, 0.1, 1, 1);
            MoveText(Textos, Textos1,Ventana11, VentanaActual, 10, 0.1, 1, 1);
            MoveText(Textos, Textos1,Ventana12, VentanaActual, 11, 0.1, 1, 1);
            
            GeneralBloqued++;
        }
                    
        //Convert text in one image
        if(GeneralBloqued == 3)
        {
            TextToImageConverter(0, 12, Textos, 13, imagenes, contadorPixelesImagenes, posicionesPixeles,  VentanaActual, 3, 0.5, -150, -300, 0.001, 1);
            
            GeneralBloqued++;
        }
    
        //Other image
        if(GeneralBloqued == 5)
        {
            TextToImageConverter(0, 12, Textos,15, imagenes, contadorPixelesImagenes, posicionesPixeles, VentanaActual,3, 0.7, -150, -300, 0.001, 1);
            
            GeneralBloqued++;
        }
        
        //Other...
        if(GeneralBloqued == 7)
        {
            TextToImageConverter(0, 12, Textos,14, imagenes, contadorPixelesImagenes, posicionesPixeles,  VentanaActual,3, 0.5, -150, -300, 0.001, 1);
            
            GeneralBloqued++;
        }
    
        //Cortazar portrait and then turn around to begin
        if(GeneralBloqued == 9)
        {
            TextToImageConverter(0, 12, Textos,1 , imagenes, contadorPixelesImagenes, posicionesPixeles,  VentanaActual, 1 , 0.5, -150, 0, 0.1, 1);
            
            GeneralBloqued=0;
        }
 
    //#################################################################################
    //#################################################################################
    
    //Call draw on scene, which initiates the drawing of the root object.
    scene->draw();
    
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("Press 1 to change mode" , -600, 300);
    ofNoFill();

}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if(key == '1')
        {
            GeneralBloqued++;
        }

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}