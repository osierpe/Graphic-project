
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

//================================================================================
//===========================================================Variaveis e constantes

//------------------------------------------------------------ Sistema Coordenadas + objectos
GLint		wScreen=800, hScreen=600;		//.. janela (pixeis)
GLfloat		xC=10.0, yC=10.0, zC=10.0;		//.. Mundo  (unidades mundo)

//------------------------------------------------------------ Observador 
GLfloat  rVisao=20, aVisao=0.5*PI, incVisao=0.05;
GLfloat	 dir[]  ={1, 0, 1};
GLfloat  passo[]={0,0,0};
GLfloat  obsP[] ={rVisao*cos(aVisao), 3.0, rVisao*sin(aVisao)};
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


GLfloat tam=2.0;
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






//================================================================================
//=========================================================================== INIT
void inicializa(void)
{
	glClearColor(BLACK);		//………………………………………………………………………………Apagar
	glEnable(GL_DEPTH_TEST);	//………………………………………………………………………………Profundidade
	glShadeModel(GL_SMOOTH);	//………………………………………………………………………………Interpolacao de cores	

	//glEnable(GL_CULL_FACE);		//………………………………………………………………………………Faces visiveis
	//glCullFace(GL_BACK);		//………………………………………………………………………………Mostrar so as da frente
		
	glVertexPointer(3, GL_FLOAT, 0, vertices); //………………………………………Vertex arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
    glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, cores);
    glEnableClientState(GL_COLOR_ARRAY);	
}








void drawScene(){
	

   /* if (frenteVisivel)
	    glCullFace(GL_BACK);  //glFrontFace(GL_CW);
	else
	    glCullFace(GL_FRONT);  //glFrontFace(GL_CCW); */
	

		
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, faceA);
		
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, faceB);
		
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, faceC);
		
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, faceD);
		
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, chao);
		
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tecto);
		                                
/*
	glPopMatrix();
	
	
		//?? 
		//?? direita
		//glTranslatef(2.0,2.0,2.0);*/	glColor4f(YELLOW);
	glPushMatrix();				//==================================== Primeiro degrau
		glTranslatef(2.5,0.25,2);
		glScalef(5,0.5,1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glColor4f(BLUE);
		glTranslatef(2.5,0.75,3);
		glScalef(5,0.5,1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glColor4f(YELLOW);
		glTranslatef(2.5,1.25,4);
		glScalef(5,0.5,1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glColor4f(BLUE);
		glTranslatef(2.5,1.75,5);
		glScalef(5,0.5,1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glColor4f(YELLOW);
		glTranslatef(2.5,2.25,6);
		glScalef(5,0.5,1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glColor4f(BLUE);
		glTranslatef(2.5,2.75,7);
		glScalef(5,0.5,1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glColor4f(YELLOW);
		glTranslatef(2.5,3.25,8);
		glScalef(5,0.5,1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glColor4f(BLUE);
		glTranslatef(2.5,3.75,9);
		glScalef(5,0.5,1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glColor4f(YELLOW);
		glTranslatef(2.5,4.25,10);
		glScalef(5,0.5,1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glColor4f(BLUE);
		glTranslatef(2.5,4.75,11);
		glScalef(5,0.5,1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glColor4f(YELLOW);
		glTranslatef(2.5,5.25,12);
		glScalef(5,0.5,1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glColor4f(BLUE);
		glTranslatef(2.5,5.75,13);
		glScalef(5,0.5,1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();		// ultimo degrau
		glColor4f(YELLOW);
		glTranslatef(2.5,6.25,14);
		glScalef(5,0.5,2);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(9, 4.5, 8);
		glColor4f(1.0, 0.6, 0.8, 1);
		glTranslatef(0, 2, 0);
		glRotatef(giro, 0, 1, 0); // definindo o giro em torno do eixo y;
		glRotatef(25, 1, 0, 0);  //25 graus de rotação para o lado;
		glTranslatef(0, -2, 0);
		glutSolidSphere(0.2, 200, 200); //desenhar candeeiro
		glColor4f(1.0, 1.0, 1.0, 1);
		glutWireSphere(0.5, 10, 10); // armação de fora
		glTranslatef(0, 1, 0);
		glScalef(0.02,2,0.02);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(10, 6.75, 7.5);
		glScalef(10, 0.5, 15);	
		glColor4f(0.4, 0.4, 0.4, 1);
		glutSolidCube(1);
		
	glPopMatrix();
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
	case 'f':
	case 'F':
		giro+=1;
		glutPostRedisplay();
		break;

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
		printf("%f, %f\n", a, c);
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

              
