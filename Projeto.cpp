
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





//=========================================================== PAREDES
GLboolean   frenteVisivel=1;
static GLuint     faceC[] = {8,9, 10,  11};
static GLuint     faceA[] = {0, 3, 2, 1};
static GLuint     faceB[] = {4, 5, 6, 7};
static GLuint     faceD[] = {12, 13, 14, 15};
static GLuint	  chao[] = {16, 17, 18, 19};
static GLuint	  tecto[] = {20, 21, 22, 23};


//============================================================ Texturas
GLuint   texture[4];
RgbImage imag;


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

static GLfloat normais[] = {
    //…………………………………………………………………………………………………… x=tam (Esquerda)
	  1.0,  0.0,  0.0,
      1.0,  0.0,  0.0,
      1.0,  0.0,  0.0,
      1.0,  0.0,  0.0,
	//…………………………………………………………………………………………………… x=tam (Direita)
	   1.0,  0.0,  0.0,
       1.0,  0.0,  0.0,
       1.0,  0.0,  0.0,
       1.0,  0.0,  0.0,
	//…………………………………………………………………………………………………… y=tam (Cima)
	   0.0,  1.0,  0.0,
       0.0,  1.0,  0.0,
       0.0,  1.0,  0.0,
       0.0,  1.0,  0.0,
    
}; 

static GLfloat cores[] = {
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
      0.0, 0.0, 0.0,     //8
      0.0,  0.0, 1.0,	// 9 
      1.0,  0.0, 1.0,	// 10 
      1.0,  0.0, 1.0,	// 11 
    //-------------------------------------- chao
	  1.0,  0.1, 0.6,	// 12 
      1.0,  0.2, 0.0,	// 13 
      1.0,  0.3, 0.4,	// 14 
      1.0,  0.4, 0.3,	//  15	
    //-------------------------------------- teto
      0.9, 0.3, 0.9, // 16
      0.9, 0.4, 0.8, //17
      0.9, 0.5, 0.7, //18
      0.9, 0.6, 0.6, //19

};
static GLfloat arrayTexture[]={ 
	//------------------------------ textura faceA
	0.0, 0.0, //1
	0.0, 1.0, //2
	1.0, 1.0, //3
	1.0, 0.0, //4

};
void initTexturas()
{   
	//----------------------------------------- parede
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	imag.LoadBmpFile("chao.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
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








void drawScene(){
	
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[0]);
		
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, faceA);
		glDisable(GL_TEXTURE_2D);
		
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, faceB);
		
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, faceC);
		
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, faceD);
		
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, chao);
		
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tecto);
		
	glPopMatrix();
		                                
	for (int i = 0; i < 13; i++){   //faz escada
		glPushMatrix();				
			glColor4f(1.0, 0.6, 0.8, 1);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,texture[1]);
			glTranslatef(2.5,0.25+i*0.5,i+2);
			glScalef(5,0.5,1);
				if (i==12)
					glScalef(1,1,2);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,0.0f);  	glVertex3f( 0.5,  0.5, 0.5 ); //face canto esquerdo
				glTexCoord2f(0.0f,1.0f);	glVertex3f( 0.5,  0.5, -0.5 ); 
				glTexCoord2f(1.0f,1.0f);	glVertex3f( 0.5,  -0.5, -0.5 ); 
				glTexCoord2f(1.0f,0.0f);    glVertex3f( 0.5,  -0.5,  0.5); 
			glEnd();
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,0.0f);  	glVertex3f( 0.5,  0.5, 0.5 ); //face cima
				glTexCoord2f(0.0f,1.0f);	glVertex3f( 0.5,  0.5, -0.5 ); 
				glTexCoord2f(1.0f,1.0f);    glVertex3f( -0.5,  0.5, -0.5 ); 
				glTexCoord2f(1.0f,0.0f);     glVertex3f( -0.5,  0.5,  0.5); 
			glEnd();
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f,0.0f);  	glVertex3f( 0.5,  0.5, 0.5 ); //face tras
				glTexCoord2f(0.0f,1.0f);	glVertex3f( 0.5,  -0.5, 0.5 ); 
				glTexCoord2f(1.0f,1.0f);   	glVertex3f( -0.5,  -0.5, 0.5 ); 
				glTexCoord2f(1.0f,0.0f);  	glVertex3f( -0.5,  0.5,  0.5); 
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
		glColor4f(0.5, 0.5, 0.5, 1);
		glTranslatef(10,0.5,8);
		glScalef(2.2,1,1.5);
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
		glTranslatef(0,0,-0.60);//parte de tras do ecrã do computador
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
		glColor4f(1.0, 0.6, 0.8, 1);
		glTranslatef(0, 2, 0);
		glRotatef(giro, 0, 1, 0); // definindo o giro em torno do eixo y;
		glRotatef(25, 1, 0, 0);  //25 graus de rotação para o lado;
		glTranslatef(0, -2, 0);
		glutSolidSphere(0.2, 200, 200); //desenhar candeeiro
		glColor4f(0, 0, 0, 1);
		glutWireSphere(0.5, 10, 10); // armação de fora
		glTranslatef(0, 1, 0);
		glScalef(0.02,2,0.02);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		
		glTranslatef(10, 6.75, 7.5);
		glScalef(10, 0.5, 15);	
		glColor4f(0.4, 0.4, 0.4, 1);
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
	giro += 3;
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

              
