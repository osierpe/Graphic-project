
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
GLfloat x, y, z = 5;







//=========================================================== PAREDES
GLboolean   frenteVisivel=1;
static GLuint     faceC[] = {8,9, 10,  11};
static GLuint     faceA[] = {0, 3, 2, 1};
static GLuint     faceB[] = {4, 5, 6, 7};
static GLuint     faceD[] = {12, 15, 14, 13};



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
        tam,  0,  tam,	// 8 
        2*tam,  0, tam,	// 9 
        2*tam,  tam, tam,	// 10 
         tam,  tam,  tam,	// 11
	//---------------------- face D
		tam, 0, -tam,	//12
		2*tam, 0, -tam,	//13
		2*tam, tam, -tam, //14
		tam, tam, -tam,  //15
	
		
	
		  
	
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
    //--------------------------------------
};
//------------------------------------------------------------ Cores
static GLfloat cores[]={
	//…………………………………………………………………………………………………… x=tam (Esquerda) - Red
	  1.0,  0.0, 0.0,	// 0 
      1.0,  0.0, 0.0,	// 1 
      1.0,  1.0, 0.0,	// 2 
      1.0,  1.0, 0.0,	// 3 
	//…………………………………………………………………………………………………… x=2*tam (Direita) - Green
	  0.0,  1.0, 1.0,	// 4 
      0.0,  1.0, 1.0,	// 5 
      0.0,  1.0, 0.0,	// 6 
      0.0,  1.0, 0.0,	// 7 
	//…………………………………………………………………………………………………… y=tam (Cima) - Blue
	  0.0,  0.0, 1.0,	// 8 
      0.0,  0.0, 1.0,	// 9 
      1.0,  0.0, 1.0,	// 10 
      1.0,  0.0, 1.0,	// 11 
    //--------------------------------------
	  0.0,  0.0, 1.0,	// 8 
      0.0,  0.0, 1.0,	// 9 
      1.0,  0.0, 1.0,	// 10 
      1.0,  0.0, 1.0,	// 11 	
      
    
}; 









//================================================================================
//=========================================================================== INIT
void inicializa(void)
{
	glClearColor(BLACK);		//………………………………………………………………………………Apagar
	glEnable(GL_DEPTH_TEST);	//………………………………………………………………………………Profundidade
	glShadeModel(GL_SMOOTH);	//………………………………………………………………………………Interpolacao de cores	

	glEnable(GL_CULL_FACE);		//………………………………………………………………………………Faces visiveis
	glCullFace(GL_BACK);		//………………………………………………………………………………Mostrar so as da frente
		
	glVertexPointer(3, GL_FLOAT, 0, vertices); //………………………………………Vertex arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
    glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, cores);
    glEnableClientState(GL_COLOR_ARRAY);	
}



void drawEixos()
{	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo X
	glColor4f(RED);
	glBegin(GL_LINES);
		glVertex3i( 0, 0, 0); 
		glVertex3i(10, 0, 0); 
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Y
	glColor4f(GREEN);
	glBegin(GL_LINES);
		glVertex3i(0,  0, 0); 
		glVertex3i(0, 10, 0); 
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Z
	glColor4f(BLUE);
	glBegin(GL_LINES);
		glVertex3i( 0, 0, 0); 
		glVertex3i( 0, 0,10); 
	glEnd();

}	




void drawScene(){
	
	//=================================================== Qual o lado ?
    if (frenteVisivel)
	    glCullFace(GL_BACK);  //glFrontFace(GL_CW);
	else
	    glCullFace(GL_FRONT);  //glFrontFace(GL_CCW);

	
	//==================================== MESA	
	//glColorPointer(3, GL_FLOAT, 0, cor);	 podia ser modificada a cor !
    /*glPushMatrix();	
		//?? 
		//?? direita
		//glTranslatef(2.0,2.0,2.0);*/
		glColor4f(RED);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, faceA);
		glColor4f(GREEN);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, faceB);
		/*
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, faceC);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, faceD);
	*/
	glPopMatrix();
	glColor4f(YELLOW);
	glPushMatrix();				//==================================== Primeiro degrau
		glTranslatef(2.5,0.25,5);
		glScalef(5,0.5,1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glColor4f(BLUE);
		glTranslatef(2.5,0.75,6);
		glScalef(5,0.5,1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glColor4f(YELLOW);
		glTranslatef(2.5,1.25,7);
		glScalef(5,0.5,1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glColor4f(BLUE);
		glTranslatef(2.5,1.75,8);
		glScalef(5,0.5,1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glColor4f(YELLOW);
		glTranslatef(2.5,2.25,9);
		glScalef(5,0.5,1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glColor4f(BLUE);
		glTranslatef(2.5,2.75,10);
		glScalef(5,0.5,1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
		glColor4f(YELLOW);
		glTranslatef(2.5,3.25,11);
		glScalef(5,0.5,1);
		glutSolidCube(1);
	glPopMatrix();

	
}

void display(void){
  	
	//================================================================= APaga ecran/profundidade
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	
	//================================================================= NAO MOFIFICAR
	glViewport (0, 0, wScreen, hScreen);								// ESQUECER PoR AGORA
	glMatrixMode(GL_PROJECTION);										// ESQUECER PoR AGORA
	glLoadIdentity();													// ESQUECER PoR AGORA
	gluPerspective(angZoom, (float)wScreen/hScreen, 0.1, 3*zC);			// ESQUECER PoR AGORA
	glMatrixMode(GL_MODELVIEW);											// ESQUECER PoR AGORA	
	glLoadIdentity();													// ESQUECER PoR AGORA
	//================================================================= NAO MOFIFICAR


	//-------------------------------------------------------------- observador
	gluLookAt(x,1,z, a, 1, c, 0, 1, 0);

	//…………………………………………………………………………………………………………………………………………………………Objectos/modelos
	drawEixos(); 
	drawScene(); 	
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Actualizacao
	glutSwapBuffers();
}


//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y){
	
	
	switch (key) {
	case 'f':
	case 'F':
		frenteVisivel=!frenteVisivel;
		glutPostRedisplay();
		break;

	case 'A':
	case 'a':
		//??
		glutPostRedisplay();
	break;

	case 'S':
	case 's':
		//??
		glutPostRedisplay();
	break;

	case 'e':
	case 'E':
		//??
		glutPostRedisplay();
	break;

	case 'd':
	case 'D':
		//??
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
		
			x = a ;
			z = c	;
		}
		/*
		if(key == GLUT_KEY_DOWN){
			x -= a;
			z -=c;
		}
		*/
		/*	
		if (obsP[1]>yC)
			obsP[1]=yC;
		if (obsP[1]<-yC)
			obsP[1]=-yC;
	*/
		if (key == GLUT_KEY_LEFT){
			angxy-=0.1;
			
		}
		if (key == GLUT_KEY_RIGHT){
			angxy+=0.1;
		}
		
		a = x + raio*cos(angxy);
		c = z + raio*sin(angxy);
		printf("%f, %f\n", a, c);
		/*
		obsP[0]=rVisao*cos(aVisao);
		obsP[2]=rVisao*sin(aVisao);
	*/

	glutPostRedisplay();	

}


//======================================================= MAIN
//======================================================= MAIN
int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize (wScreen, hScreen); 
	glutInitWindowPosition (300, 100); 
	glutCreateWindow (" |Observador:'SETAS'|        |Andar-'Cima'|        |Rodar -'e/d'| ");
  
	inicializa();
	
	glutSpecialFunc(teclasNotAscii); 
	glutDisplayFunc(display); 
	glutKeyboardFunc(keyboard);
	
	glutMainLoop();

	return 0;
}



