
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

//--------------------------------- Definir cores
#define BLUE     0.0, 0.0, 1.0, 1.0
#define RED		 1.0, 0.0, 0.0, 1.0
#define YELLOW	 1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define PI		 3.14159
#include "RgbImage.h"
//================================================================================
//===========================================================Variaveis e constantes

//------------------------------------------------------------ Sistema Coordenadas + objectos
GLint		wScreen=800, hScreen=600;		//.. janela (pixeis)
GLfloat		xC=10.0, yC=10.0, zC=10.0;		//.. Mundo  (unidades mundo)

//------------------------------------------------------------ Observador 
GLfloat  rVisao=20, aVisao=0.5*PI, incVisao=0.05;
GLfloat  angZoom=90;
GLfloat  incZoom=3;
GLfloat  raio=0.5;
GLfloat  angxy = 0;
GLfloat a, b, c = 0;
GLfloat x, z = 5;
GLfloat y = 1;
static GLfloat giro = 0.0;

//================================ Material 
GLfloat	Amb [3] = { 0.3, 0.3, 0.3 };
GLfloat Dif [3] = { 0.8, 0.8, 0.8 };
GLfloat Spec [3] = { 0.8, 0.8, 0.8 };
GLuint Coef = 1;
//================================ Material Gold
GLfloat ambg[3] = {0.24725, 0.1995, 0.0745};
GLfloat difg[3] = {0.75164, 0.60648, 0.22648};
GLfloat specg[3] = {0.628281, 0.555802, 0.366065};
GLfloat coefg = 0.4;
//================================ Material candeeiro
GLfloat ambc[3] = {1.0,1.0,1.0};
GLfloat difc[3] = {1.0, 1.0, 1.0};
GLfloat specc[3] = {1.0, 1.0, 1.0};
GLfloat coefc = 1.0;
//=========================================================== PAREDES
GLboolean   frenteVisivel=1;
static GLuint     faceC[] = {8,11, 10,  9};
static GLuint     faceA[] = {0, 3, 2, 1};
static GLuint     faceB[] = {4, 5, 6, 7};
static GLuint     faceD[] = {12, 13, 14, 15};
static GLuint	  chao[] = {16, 17, 18, 19};
static GLuint	  tecto[] = {20, 21, 22, 23};


//============================================================ Texturas
GLuint   texture[7];
RgbImage imag;
GLfloat luzGlobalCorAmb[3] ={0.5, 0.5, 0.5};
//============================================== Luz 0;
GLfloat pos[3] = {0 , 0, 0};
GLfloat ambiente[4] = {1.0, 1.0, 1.0, 1};
GLfloat difuse[4] = {1.0,1.0,1.0,1}; 
GLfloat	constante = 0.5; 
GLfloat linear = 0.05;
GLfloat quadr = 0.5;

//==========================================
GLfloat posicao[4]= {0, 0, 0, 1.0};
GLfloat dir[4]= {0, -1.0, 0, 1.0};
GLfloat exponent = 1;
GLfloat cut = 80;
GLfloat difusa[4] = {1.0,1.0,1.0,1};
GLfloat especular[4] = {1.0,1.0,1.0,1};  


static GLfloat vertices[]={
	//…………………………………………………… faceA
         0, 0, 0,	// 0 
         0,   15,  0,	// 1 
         15,   15, 0,	// 2 
         15,  0, 0,	// 3 
	//…………………………………………………… faceB;
        0,  0,0,	// 4 
        0,  15, 0,	// 5 
        0,  15, 15,	// 6 
        0,  0,15,	// 7 
	//……………………………………………………… faceC
        0,  0,  15,	 // 8 
        0,  15, 15,	 // 9 
        15,  15, 15, // 10 
        15,  0,  15, // 11
	//---------------------- face D
		15, 15, 0,	//12
		15, 0, 0,	//13
		15, 0, 15, //14
		15, 15, 15,  //15
	//---------------------- chao primeiro andar
		0, 0, 0, //16 
		0, 0, 15, //17
		15, 0, 15, //18
		15, 0, 0, //19
   //-------------------------- teto da casa
   		0, 15, 0, //20
   		0, 15, 15, //21
   		15, 15, 15, //22
   		15, 15, 0, //23
	
		  
	
}; 

static GLfloat normais[] = { //normais da casa
    //…………………………………………………………………………………………………… FaceA
	  0.0,  0.0,  1.0,
      0.0,  0.0,  1.0,
      0.0,  0.0,  1.0,
      0.0,  0.0,  1.0,
	//…………………………………………………………………………………………………… FaceB
	   1.0,  0.0,  0.0,
       1.0,  0.0,  0.0,
       1.0,  0.0,  0.0,
       1.0,  0.0,  0.0,
	//…………………………………………………………………………………………………… FaceC
	   0.0,  0.0,  -1.0,
       0.0,  0.0,  -1.0,
       0.0,  0.0,  -1.0,
       0.0,  0.0,  -1.0,
    //====================================== FaceD
	   -1.0, 0.0, 0.0,
	   -1.0, 0.0, 0.0,
	   -1.0, 0.0, 0.0,
	   -1.0, 0.0, 0.0,
	//======================================= Chao
	    0.0, 1.0, 0.0,
	    0.0, 1.0, 0.0,
	    0.0, 1.0, 0.0,
	    0.0, 1.0, 0.0,
	//======================================= Teto
	    0.0, -1.0, 0.0,
	    0.0, -1.0, 0.0,
	    0.0, -1.0, 0.0,
	    0.0, -1.0, 0.0,
}; 

static GLfloat cores[] = {  //cores das paredes, chao e teto
	//…………………………………………………………………………………………………… faceA
	  1.0,  0.0, 0.0,	// 0 
      1.0,  0.0, 0.0,	// 1 
      1.0,  1.0, 0.0,	// 2 
      1.0,  1.0, 0.0,	// 3 
	//…………………………………………………………………………………………………… faceB
	  0.0,  1.0, 1.0,	// 4 
      0.0,  1.0, 1.0,	// 5 
      0.0,  1.0, 0.0,	// 6 
      0.0,  1.0, 0.0,	// 7 
	//…………………………………………………………………………………………………… faceC
	  0.0,  0.0, 1.0,	// 8 
      0.0,  0.0, 1.0,	// 9 
      1.0,  0.0, 1.0,	// 10 
      1.0,  0.0, 1.0,	// 11 
       //-------------------------------------- faceD
      0.0, 0.0, 0.0,     //12
      0.0,  0.0, 1.0,	// 13
      1.0,  0.0, 1.0,	// 14 
      1.0,  0.0, 1.0,	// 15 
    //-------------------------------------- chao
	  1.0,  0.1, 0.6,	// 16 
      1.0,  0.2, 0.0,	// 17 
      1.0,  0.3, 0.4,	// 18 
      1.0,  0.4, 0.3,	//  19	
    //-------------------------------------- teto
      0.9, 0.3, 0.9, // 20
      0.9, 0.4, 0.8, //21
      0.9, 0.5, 0.7, //22
      0.9, 0.6, 0.6, //23

};
static GLfloat arrayTexture[]={ 
	//------------------------------ textura faceA
	0.0, 0.0, //1
	0.0, 2.0, //2
	2.0, 2.0, //3
	2.0, 0.0, //4
   	//------------------------------ textura faceB
	0.0, 0.0, //5
	0.0, 2.0, //6
	2.0, 2.0, //7
	2.0, 0.0, //8
	//------------------------------ textura faceC
	0.0, 0.0, //9
	0.0, 2.0, //10
	2.0, 2.0, //11
	2.0, 0.0, //12
	//------------------------------ textura faceD
	0.0, 0.0, //12
	0.0, 2.0, //13
	2.0, 2.0, //14
	2.0, 0.0, //15
	//------------------------------ Textura chao
	0.0, 0.0, //13
	0.0, 3.0,  //14
	3.0, 3.0, //15
	3.0, 0.0, //16

};
void initTexturas()
{   
	//----------------------------------------- parede
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	imag.LoadBmpFile("wall.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());   		   
	//=================================================== madeira	
	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	imag.LoadBmpFile("madeira.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());  
	//===================================================== ecrã
	glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	imag.LoadBmpFile("windows.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData()); 
	//==================================================== chao
	glGenTextures(1, &texture[3]);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	imag.LoadBmpFile("chao.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData()); 
	//-------------------------------------------------- tecto
	glGenTextures(1, &texture[4]);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	imag.LoadBmpFile("cement.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData()); 
	
	
}
void initLight(){
	glEnable (GL_LIGHTING);
	glEnable(GL_LIGHT0);	
	/*
	glLightfv(GL_LIGHT0, GL_POSITION, pos );
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente );
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difuse );
	glLightf (GL_LIGHT0, GL_CONSTANT_ATTENUATION, constante);
	glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION, linear ) ;
	glLightf (GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quadr );
	*/	//…………………………………………………………………………………………………………………………………………… Ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);
	//…………………………………………………………………………………………………………………………………………… Foco
	glLightfv(GL_LIGHT0, GL_POSITION,      pos );
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
	glLightf (GL_LIGHT0, GL_SPOT_EXPONENT , exponent);
    glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,   cut);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,       difusa );   
	glLightfv(GL_LIGHT0, GL_SPECULAR,      especular  );
	
}


//================================================================================
//=========================================================================== INIT

void inicializa(void)
{
	
	
	glClearColor(BLACK);		//………………………………………………………………………………Apagar
	initTexturas();
	glEnable(GL_DEPTH_TEST);	//………………………………………………………………………………Profundidade
	glShadeModel(GL_SMOOTH);	//………………………………………………………………………………Interpolacao de cores	
	
	glVertexPointer(3, GL_FLOAT, 0, vertices); //………………………………………Vertex arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
    glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, cores);
    glEnableClientState(GL_COLOR_ARRAY);	
    glTexCoordPointer(2, GL_FLOAT, 0, arrayTexture); 
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}
void Material(){
		glMaterialfv ( GL_FRONT, GL_AMBIENT, Amb );
		glMaterialfv ( GL_FRONT, GL_DIFFUSE, Dif );
		glMaterialfv ( GL_FRONT, GL_SPECULAR, Spec );
		glMaterialf ( GL_FRONT, GL_SHININESS, Coef );
}
void Gold(){
		glMaterialfv ( GL_FRONT_AND_BACK, GL_AMBIENT, ambg );
		glMaterialfv ( GL_FRONT_AND_BACK, GL_DIFFUSE, difg );
		glMaterialfv ( GL_FRONT_AND_BACK, GL_SPECULAR, specg );
		glMaterialf ( GL_FRONT_AND_BACK, GL_SHININESS, coefg );
}
void materialcand(){
		glMaterialfv ( GL_FRONT_AND_BACK, GL_AMBIENT, ambc );
		glMaterialfv ( GL_FRONT_AND_BACK, GL_DIFFUSE, difc );
		glMaterialfv ( GL_FRONT_AND_BACK, GL_SPECULAR, specc );
		glMaterialf ( GL_FRONT_AND_BACK, GL_SHININESS, coefc );
}
void desenhaMesa(){
		
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  0.5, 0.5 ); //face canto esquerdo//
			glVertex3f( 0.5,  0.5, -0.5 ); 
			glVertex3f( 0.5,  -0.5, -0.5 ); 
		    glVertex3f( 0.5,  -0.5,  0.5); 
		glEnd();

		glBegin(GL_QUADS);		  	
			glVertex3f( 0.5,  0.5, 0.5 ); //face cima//
			glVertex3f( 0.5,  0.5, -0.5 ); 
		    glVertex3f( -0.5,  0.5, -0.5 ); 
		    glVertex3f( -0.5,  0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		 	glVertex3f( 0.5,  0.5, -0.5 ); //face frente;
			glVertex3f( 0.5,  -0.5, -0.5 ); 
			glVertex3f( -0.5,  -0.5, -0.5 ); 
			glVertex3f( -0.5,  0.5,  -0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( -0.5,  0.5, 0.5 ); //face direita;//
			glVertex3f( -0.5,  -0.5, 0.5 ); 
			glVertex3f( -0.5,  -0.5, -0.5 ); 
			glVertex3f( -0.5,  0.5,  -0.5); 
		glEnd();
}
void drawScene(){

	Material();

	glPushMatrix();   //desenha paredes, chao e teto da casa.
		glEnable(GL_TEXTURE_2D); 
		glBindTexture(GL_TEXTURE_2D,texture[0]);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, faceA);
	
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, faceB);
		
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, faceC);
		
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, faceD);
		glDisable(GL_TEXTURE_2D);
		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[3]);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, chao);		
		glDisable(GL_TEXTURE_2D);
		
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tecto);
		
	glPopMatrix();
		                                
	for (int i = 0; i < 13; i++){   //faz escada
		glPushMatrix();				
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glBindTexture(GL_TEXTURE_2D,texture[1]);
			glTranslatef(2.5,0.25+i*0.5,i+2);
			glScalef(5,0.5,1);
				if (i==12)
					glScalef(1,1,2);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,0.0f);  	glVertex3f( 0.5,  0.5, 0.5 ); //face canto esquerdo
				glTexCoord2f(1.0f,0.0f);    glVertex3f( 0.5,  -0.5,  0.5);
				glTexCoord2f(1.0f,1.0f);	glVertex3f( 0.5,  -0.5, -0.5 );
				glTexCoord2f(0.0f,1.0f);	glVertex3f( 0.5,  0.5, -0.5 ); 
			glEnd();
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,0.0f);  	glVertex3f( 0.5,  0.5, 0.5 ); //face cima
				glTexCoord2f(0.0f,1.0f);	glVertex3f( 0.5,  0.5, -0.5 ); 
				glTexCoord2f(1.0f,1.0f);    glVertex3f( -0.5,  0.5, -0.5 ); 
				glTexCoord2f(1.0f,0.0f);     glVertex3f( -0.5,  0.5,  0.5); 
			glEnd();
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,0.0f);  	glVertex3f( 0.5,  0.5, 0.5 ); //face tras
				glTexCoord2f(1.0f,0.0f);  	glVertex3f( -0.5,  0.5,  0.5); 
				glTexCoord2f(1.0f,1.0f);   	glVertex3f( -0.5,  -0.5, 0.5 ); 
				glTexCoord2f(0.0f,1.0f);	glVertex3f( 0.5,  -0.5, 0.5 ); 		
			glEnd();
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,0.0f);  	glVertex3f( 0.5,  -0.5, 0.5 );  // face baixo
				glTexCoord2f(0.0f,1.0f);	glVertex3f( 0.5,  -0.5, -0.5 ); 
				glTexCoord2f(1.0f,1.0f);    glVertex3f( -0.5,  -0.5, -0.5 ); 
				glTexCoord2f(1.0f,0.0f);    glVertex3f( -0.5,  -0.5,  0.5); 
			glEnd();
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,0.0f);  	glVertex3f( 0.5,  0.5, -0.5 ); //face frente;
				glTexCoord2f(0.0f,1.0f);	glVertex3f( 0.5,  -0.5, -0.5 ); 
				glTexCoord2f(1.0f,1.0f);	glVertex3f( -0.5,  -0.5, -0.5 ); 
				glTexCoord2f(1.0f,0.0f);	glVertex3f( -0.5,  0.5,  -0.5); 
			glEnd();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
	glPushMatrix(); //desenha mesa;
		Gold();
		glTranslatef(10,0.5,8);
		glScalef(2.2,1,1.5);
		desenhaMesa();

	glPopMatrix();
	glPushMatrix();// desenha ecrã
		glColor4f(0.8, 0.2, 0.2, 1);
		glTranslatef(10,1.25,8);
		glScalef(0.7,0.5,0.5);
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  0.5, 0.5 ); //face canto esquerdo//
			glVertex3f( 0.5,  0.5, -0.5 ); 
			glVertex3f( 0.5,  -0.5, -0.5 ); 
		    glVertex3f( 0.5,  -0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  0.5, 0.5 ); //face cima//
			glVertex3f( 0.5,  0.5, -0.5 ); 
		    glVertex3f( -0.5,  0.5, -0.5 ); 
		    glVertex3f( -0.5,  0.5,  0.5); 
		glEnd();
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D,texture[2]);
		glBegin(GL_QUADS);
			glTexCoord2f(1.0f,1.0f);	glVertex3f( 0.5,  0.5, 0.5 ); //face tras
			glTexCoord2f(1.0f,0.0f);	glVertex3f( 0.5,  -0.5, 0.5 ); 
			glTexCoord2f(0.0f,0.0f);   	glVertex3f( -0.5,  -0.5, 0.5 ); 
			glTexCoord2f(0.0f,1.0f);	glVertex3f( -0.5,  0.5,  0.5); 
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		 	glVertex3f( 0.5,  0.5, -0.5 ); //face frente;
			glVertex3f( 0.5,  -0.5, -0.5 ); 
			glVertex3f( -0.5,  -0.5, -0.5 ); 
			glVertex3f( -0.5,  0.5,  -0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  -0.5, 0.5 );  // face baixo
			glVertex3f( 0.5,  -0.5, -0.5 ); 
		    glVertex3f( -0.5,  -0.5, -0.5 ); 
		    glVertex3f( -0.5,  -0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( -0.5,  0.5, 0.5 ); //face direita;//
			glVertex3f( -0.5,  -0.5, 0.5 ); 
			glVertex3f( -0.5,  -0.5, -0.5 ); 
			glVertex3f( -0.5,  0.5,  -0.5); 
		glEnd();
		glTranslatef(0,0,-0.60);//parte de tras do computador
		glScalef(1.4,1.2,1.2);
		glBegin(GL_QUADS);
		  	glVertex3f( 0.25,  0.25, 0.25 ); //face canto esquerdo//
			glVertex3f( 0.25,  0.25, -0.25 ); 
			glVertex3f( 0.25,  -0.25, -0.25 ); 
		    glVertex3f( 0.25,  -0.25,  0.25); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( -0.25,  0.25, 0.25 ); //face direita;//
			glVertex3f( -0.25,  -0.25, 0.25 ); 
			glVertex3f( -0.25 ,  -0.25, -0.25 ); 
			glVertex3f( -0.25,  0.25,  -0.25); 
		glEnd();
		glColor4f(1.0, 0.6, 0.8, 1);
		glBegin(GL_QUADS);
		  	glVertex3f( 0.25,  0.25, 0.25 ); //face cima
			glVertex3f( 0.25,  0.25, -0.25 ); 
		    glVertex3f( -0.25,  0.25, -0.25 ); 
		    glVertex3f( -0.25,  0.25,  0.25); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( 0.25,  -0.25, 0.25 );  // face baixo
			glVertex3f( 0.25,  -0.25, -0.25 ); 
		    glVertex3f( -0.25,  -0.25, -0.25 ); 
		    glVertex3f( -0.25,  -0.25,  0.25); 
		glEnd();
		glBegin(GL_QUADS);
		 	glVertex3f( 0.25,  0.25, -0.25 ); //face frente;
			glVertex3f( 0.25,  -0.25, -0.25 ); 
			glVertex3f( -0.25,  -0.25, -0.25 ); 
			glVertex3f( -0.25,  0.25,  -0.25); 
		glEnd();
	glPopMatrix();
	glPushMatrix(); //desenha teclado
		glColor4f(0, 0, 0, 1);
		glTranslatef(10,1.035,8.5);
		glScalef(0.9,0.07,0.3);
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  0.5, 0.5 ); //face canto esquerdo//
			glVertex3f( 0.5,  0.5, -0.5 ); 
			glVertex3f( 0.5,  -0.5, -0.5 ); 
		    glVertex3f( 0.5,  -0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  0.5, 0.5 ); //face cima//
			glVertex3f( 0.5,  0.5, -0.5 ); 
		    glVertex3f( -0.5,  0.5, -0.5 ); 
		     glVertex3f( -0.5,  0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  0.5, 0.5 ); //face tras
			glVertex3f( 0.5,  -0.5, 0.5 ); 
		   	glVertex3f( -0.5,  -0.5, 0.5 ); 
		  	glVertex3f( -0.5,  0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		 	glVertex3f( 0.5,  0.5, -0.5 ); //face frente;
			glVertex3f( 0.5,  -0.5, -0.5 ); 
			glVertex3f( -0.5,  -0.5, -0.5 ); 
			glVertex3f( -0.5,  0.5,  -0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  -0.5, 0.5 );  // face baixo
			glVertex3f( 0.5,  -0.5, -0.5 ); 
		    glVertex3f( -0.5,  -0.5, -0.5 ); 
		    glVertex3f( -0.5,  -0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( -0.5,  0.5, 0.5 ); //face direita;//
			glVertex3f( -0.5,  -0.5, 0.5 ); 
			glVertex3f( -0.5,  -0.5, -0.5 ); 
			glVertex3f( -0.5,  0.5,  -0.5); 
		glEnd();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(9, 4.5, 8);
		glTranslatef(0, 2, 0);
		
		glRotatef(giro, 0, 1, 0); // definindo o giro em torno do eixo y;
		glRotatef(20, 1, 0, 0);  //25 graus de rotação para o lado;
		glTranslatef(0, -2, 0);
		materialcand();
		glutSolidSphere(0.2, 200, 200); //desenhar candeeiro
		initLight(); // desenha luz;
		glutWireSphere(0.5, 10, 10); // armação de fora
		glTranslatef(0, 1, 0);
		glScalef(0.02,2,0.02);
		
		glutSolidCube(1);
		
	glPopMatrix();
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D,texture[4]);
		glTranslatef(10, 6.75, 7.5);
		glScalef(10, 0.5, 15);	
		glColor4f(0.4, 0.4, 0.4, 1);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f,1.0f);  	glVertex3f( 0.5,  0.5, 0.5 ); //face canto esquerdo//
		glTexCoord2f(1.0f,0.0f);	glVertex3f( 0.5,  0.5, -0.5 ); 
		glTexCoord2f(0.0f,0.0f);    glVertex3f( 0.5,  -0.5, -0.5 ); 
		glTexCoord2f(0.0f,1.0f);    glVertex3f( 0.5,  -0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f,1.0f);  	glVertex3f( 0.5,  0.5, 0.5 ); //face cima//
		glTexCoord2f(1.0f,0.0f);	glVertex3f( 0.5,  0.5, -0.5 ); 
		glTexCoord2f(0.0f,0.0f);    glVertex3f( -0.5,  0.5, -0.5 ); 
		glTexCoord2f(0.0f,1.0f);    glVertex3f( -0.5,  0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f,1.0f);  	glVertex3f( 0.5,  0.5, 0.5 ); //face tras
		glTexCoord2f(1.0f,0.0f);	glVertex3f( 0.5,  -0.5, 0.5 ); 
		glTexCoord2f(0.0f,0.0f);   	glVertex3f( -0.5,  -0.5, 0.5 ); 
		glTexCoord2f(0.0f,1.0f);  	glVertex3f( -0.5,  0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f,1.0f); 	glVertex3f( 0.5,  0.5, -0.5 ); //face frente;
		glTexCoord2f(1.0f,0.0f);	glVertex3f( 0.5,  -0.5, -0.5 ); 
		glTexCoord2f(0.0f,0.0f);	glVertex3f( -0.5,  -0.5, -0.5 ); 
		glTexCoord2f(0.0f,1.0f);	glVertex3f( -0.5,  0.5,  -0.5); 
		glEnd();
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f,1.0f);  	glVertex3f( 0.5,  -0.5, 0.5 );  // face baixo
		glTexCoord2f(1.0f,0.0f);	glVertex3f( 0.5,  -0.5, -0.5 ); 
		glTexCoord2f(0.0f,0.0f);    glVertex3f( -0.5,  -0.5, -0.5 ); 
		glTexCoord2f(0.0f,1.0f);    glVertex3f( -0.5,  -0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f,1.0f);  	glVertex3f( -0.5,  0.5, 0.5 ); //face direita;//
		glTexCoord2f(1.0f,0.0f);	glVertex3f( -0.5,  -0.5, 0.5 ); 
		glTexCoord2f(0.0f,0.0f);	glVertex3f( -0.5,  -0.5, -0.5 ); 
		glTexCoord2f(0.0f,1.0f);	glVertex3f( -0.5,  0.5,  -0.5); 
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	glPushMatrix();
		glColor4f(0.8,0,1,1);
		glTranslatef(9,8.5,9.5);
		glScalef(3,0.3,4);
		glBegin(GL_QUADS); 				//tampo mesa
		  	glVertex3f( 0.5,  0.5, 0.5 ); //face canto esquerdo//
			glVertex3f( 0.5,  0.5, -0.5 ); 
			glVertex3f( 0.5,  -0.5, -0.5 ); 
		    glVertex3f( 0.5,  -0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  0.5, 0.5 ); //face cima//
			glVertex3f( 0.5,  0.5, -0.5 ); 
		    glVertex3f( -0.5,  0.5, -0.5 ); 
		     glVertex3f( -0.5,  0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  0.5, 0.5 ); //face tras
			glVertex3f( 0.5,  -0.5, 0.5 ); 
		   	glVertex3f( -0.5,  -0.5, 0.5 ); 
		  	glVertex3f( -0.5,  0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		 	glVertex3f( 0.5,  0.5, -0.5 ); //face frente;
			glVertex3f( 0.5,  -0.5, -0.5 ); 
			glVertex3f( -0.5,  -0.5, -0.5 ); 
			glVertex3f( -0.5,  0.5,  -0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  -0.5, 0.5 );  // face baixo
			glVertex3f( 0.5,  -0.5, -0.5 ); 
		    glVertex3f( -0.5,  -0.5, -0.5 ); 
		    glVertex3f( -0.5,  -0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( -0.5,  0.5, 0.5 ); //face direita;//
			glVertex3f( -0.5,  -0.5, 0.5 ); 
			glVertex3f( -0.5,  -0.5, -0.5 ); 
			glVertex3f( -0.5,  0.5,  -0.5); 
		glEnd();
	glPopMatrix();
	glPushMatrix();        //perna 1
		glColor4f(0,1,0,1);
		glTranslatef(10,7.7,11);
		glScalef(0.5,1.5,0.5);
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  0.5, 0.5 ); //face canto esquerdo//
			glVertex3f( 0.5,  0.5, -0.5 ); 
			glVertex3f( 0.5,  -0.5, -0.5 ); 
		    glVertex3f( 0.5,  -0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  0.5, 0.5 ); //face cima//
			glVertex3f( 0.5,  0.5, -0.5 ); 
		    glVertex3f( -0.5,  0.5, -0.5 ); 
		     glVertex3f( -0.5,  0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  0.5, 0.5 ); //face tras
			glVertex3f( 0.5,  -0.5, 0.5 ); 
		   	glVertex3f( -0.5,  -0.5, 0.5 ); 
		  	glVertex3f( -0.5,  0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		 	glVertex3f( 0.5,  0.5, -0.5 ); //face frente;
			glVertex3f( 0.5,  -0.5, -0.5 ); 
			glVertex3f( -0.5,  -0.5, -0.5 ); 
			glVertex3f( -0.5,  0.5,  -0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  -0.5, 0.5 );  // face baixo
			glVertex3f( 0.5,  -0.5, -0.5 ); 
		    glVertex3f( -0.5,  -0.5, -0.5 ); 
		    glVertex3f( -0.5,  -0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( -0.5,  0.5, 0.5 ); //face direita;//
			glVertex3f( -0.5,  -0.5, 0.5 ); 
			glVertex3f( -0.5,  -0.5, -0.5 ); 
			glVertex3f( -0.5,  0.5,  -0.5); 
		glEnd();
	glPopMatrix();
	glPushMatrix();            //perna 2
		glColor4f(0,0,1,1);
		glTranslatef(8,7.7,11);
		glScalef(0.5,1.5,0.5);
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  0.5, 0.5 ); //face canto esquerdo//
			glVertex3f( 0.5,  0.5, -0.5 ); 
			glVertex3f( 0.5,  -0.5, -0.5 ); 
		    glVertex3f( 0.5,  -0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  0.5, 0.5 ); //face cima//
			glVertex3f( 0.5,  0.5, -0.5 ); 
		    glVertex3f( -0.5,  0.5, -0.5 ); 
		     glVertex3f( -0.5,  0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  0.5, 0.5 ); //face tras
			glVertex3f( 0.5,  -0.5, 0.5 ); 
		   	glVertex3f( -0.5,  -0.5, 0.5 ); 
		  	glVertex3f( -0.5,  0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		 	glVertex3f( 0.5,  0.5, -0.5 ); //face frente;
			glVertex3f( 0.5,  -0.5, -0.5 ); 
			glVertex3f( -0.5,  -0.5, -0.5 ); 
			glVertex3f( -0.5,  0.5,  -0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  -0.5, 0.5 );  // face baixo
			glVertex3f( 0.5,  -0.5, -0.5 ); 
		    glVertex3f( -0.5,  -0.5, -0.5 ); 
		    glVertex3f( -0.5,  -0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( -0.5,  0.5, 0.5 ); //face direita;//
			glVertex3f( -0.5,  -0.5, 0.5 ); 
			glVertex3f( -0.5,  -0.5, -0.5 ); 
			glVertex3f( -0.5,  0.5,  -0.5); 
		glEnd();
	glPopMatrix();

	glPushMatrix();         //perna 3
		glColor4f(1,0,0,1);
		glTranslatef(10,7.7,8);
		glScalef(0.5,1.5,0.5);
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  0.5, 0.5 ); //face canto esquerdo//
			glVertex3f( 0.5,  0.5, -0.5 ); 
			glVertex3f( 0.5,  -0.5, -0.5 ); 
		    glVertex3f( 0.5,  -0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  0.5, 0.5 ); //face cima//
			glVertex3f( 0.5,  0.5, -0.5 ); 
		    glVertex3f( -0.5,  0.5, -0.5 ); 
		     glVertex3f( -0.5,  0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  0.5, 0.5 ); //face tras
			glVertex3f( 0.5,  -0.5, 0.5 ); 
		   	glVertex3f( -0.5,  -0.5, 0.5 ); 
		  	glVertex3f( -0.5,  0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		 	glVertex3f( 0.5,  0.5, -0.5 ); //face frente;
			glVertex3f( 0.5,  -0.5, -0.5 ); 
			glVertex3f( -0.5,  -0.5, -0.5 ); 
			glVertex3f( -0.5,  0.5,  -0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  -0.5, 0.5 );  // face baixo
			glVertex3f( 0.5,  -0.5, -0.5 ); 
		    glVertex3f( -0.5,  -0.5, -0.5 ); 
		    glVertex3f( -0.5,  -0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( -0.5,  0.5, 0.5 ); //face direita;//
			glVertex3f( -0.5,  -0.5, 0.5 ); 
			glVertex3f( -0.5,  -0.5, -0.5 ); 
			glVertex3f( -0.5,  0.5,  -0.5); 
		glEnd();
	glPopMatrix();
	glPushMatrix();       //perna 4
		
		glColor4f(0,1,0,1);
		glTranslatef(8,7.7,8);
		glScalef(0.5,1.5,0.5);
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  0.5, 0.5 ); //face canto esquerdo//
			glVertex3f( 0.5,  0.5, -0.5 ); 
			glVertex3f( 0.5,  -0.5, -0.5 ); 
		    glVertex3f( 0.5,  -0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  0.5, 0.5 ); //face cima//
			glVertex3f( 0.5,  0.5, -0.5 ); 
		    glVertex3f( -0.5,  0.5, -0.5 ); 
		     glVertex3f( -0.5,  0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  0.5, 0.5 ); //face tras
			glVertex3f( 0.5,  -0.5, 0.5 ); 
		   	glVertex3f( -0.5,  -0.5, 0.5 ); 
		  	glVertex3f( -0.5,  0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		 	glVertex3f( 0.5,  0.5, -0.5 ); //face frente;
			glVertex3f( 0.5,  -0.5, -0.5 ); 
			glVertex3f( -0.5,  -0.5, -0.5 ); 
			glVertex3f( -0.5,  0.5,  -0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( 0.5,  -0.5, 0.5 );  // face baixo
			glVertex3f( 0.5,  -0.5, -0.5 ); 
		    glVertex3f( -0.5,  -0.5, -0.5 ); 
		    glVertex3f( -0.5,  -0.5,  0.5); 
		glEnd();
		glBegin(GL_QUADS);
		  	glVertex3f( -0.5,  0.5, 0.5 ); //face direita;//
			glVertex3f( -0.5,  -0.5, 0.5 ); 
			glVertex3f( -0.5,  -0.5, -0.5 ); 
			glVertex3f( -0.5,  0.5,  -0.5); 
		glEnd();
	glPopMatrix();
	glTranslatef(9,9,9);
	glutSolidTeapot(0.5);
}
void girodisp(void){
	giro += 1;
	if (giro > 360.0){
		giro -= 360.00;
	}                                                                
		
	glutPostRedisplay();    
}

void display(void){
  	

	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	

	glViewport (0, 0, wScreen, hScreen);								
	glMatrixMode(GL_PROJECTION);										
	glLoadIdentity();													
	gluPerspective(angZoom, (float)wScreen/hScreen, 0.1, 3*zC);			
	glMatrixMode(GL_MODELVIEW);											
	glLoadIdentity();													
	


	//-------------------------------------------------------------- observador
	gluLookAt(x,y,z, a, y, c, 0, 1, 0);

	//…………………………………………………………………………………………………………………………………………………………Objectos/modelos

	
	drawScene(); 	
	glEnable(GL_NORMALIZE);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Actualizacao
	glutSwapBuffers();
}


//======================================================= EVENTOS
void keyboard(unsigned char key, int xx, int yy){
	
	
	switch (key) {
	case 'S':
	case 's':
		y-=0.5;
		glutPostRedisplay();
	break;

	case 'w':
	case 'W':
		y+=0.5;
		glutPostRedisplay();
	break;
	
//--------------------------- Escape
	case 27:
		exit(0);    
	break;	
  }

}



void teclasNotAscii(int key, int xx, int yy){
 
	if(key == GLUT_KEY_UP){
			x = a;
			z = c;
		}
		
	 if(key == GLUT_KEY_DOWN){
			a = x + raio*cos(angxy-3.14159);
			c = z + raio*sin(angxy-3.14159);
			x = a;
			z = c;
			
		}
								
		if (key == GLUT_KEY_LEFT){
			angxy-=0.1;
			
		}
		if (key == GLUT_KEY_RIGHT){
			angxy+=0.1;
		}
		
		a = x + raio*cos(angxy);
		c = z + raio*sin(angxy);
	glutPostRedisplay();	

}
				  
		
		


int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize (wScreen, hScreen); 
	glutInitWindowPosition (300, 100); 
	glutCreateWindow (" |Andar-'Cima' 'Baixo'|    |Rodar -'Esquerda/Direita'|   |Para Cima -'W'| |Para Baixo -'S'| ");
  
	inicializa();
	glutIdleFunc(girodisp);   


	glutSpecialFunc(teclasNotAscii); 
	glutDisplayFunc(display); 
	glutKeyboardFunc(keyboard);
	
	glutMainLoop();

	return 0;
}

              
