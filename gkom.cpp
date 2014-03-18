/*
 * GKOM Lab. 3: OpenGL
 *
 * Program stanowi zaadaptowana wersje przykladu accnot.c.
 */

#include <windows.h>
#include <GL/gl.h>
#include "glut.h"
#include "plaszczka.h"
#include "otoczenie.h"
#include "particle.h"
#include "SOIL.h"
#include <iostream>

int frame_no = 0;
double mouseSpeed = 0.3;
double keySpeed = 0.3;

// do passive mouse movement
int lastx;
int lasty;

// rotacja klawiszy - info dla mouse movement
int current_xRotation = 0;
int current_yRotation = 0;

float ambientLevel = 0.5;
GLuint	texture[10];			// miejsce na tekstury
GLfloat light_diffuse[] = { 0.1, 0.1, 0.1, 1.0 };

int loadTextures()                                    // Load Bitmaps And Convert To Textures
{
	/* load an image file directly as a new OpenGL texture */
	texture[0] = SOIL_load_OGL_texture
		(
		//"img/niebieski.jpg",
		"img/gora.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	                         
	texture[1] = SOIL_load_OGL_texture
		(
		"img/plaszczkaDol.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	// textureBack
	texture[2] = SOIL_load_OGL_texture
		(
		"img/aqua4_bk.png",
		//"img/prawa_flipped.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	// textureDown
	texture[3] = SOIL_load_OGL_texture
		(
		//"img/sand.jpg",
		"img/aqua4_dn.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	// textureFront
	texture[4] = SOIL_load_OGL_texture
		(
		"img/aqua4_ft.png",
		//"img/prawa.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	// textureLeft
	texture[5] = SOIL_load_OGL_texture
		(
		"img/aqua4_lf.png",
		//"img/lewa_flipped.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	// textureRight
	texture[6] = SOIL_load_OGL_texture
		(
		"img/aqua4_rt.png",
		//"img/lewa.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	// textureUp
	texture[7] = SOIL_load_OGL_texture
		(
		"img/aqua4_up.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	texture[8] = SOIL_load_OGL_texture
		(
		"img/bubble.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	texture[9] = SOIL_load_OGL_texture
		(
		"img/shell.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	if (texture[0] == 0 || texture[1] == 0 || texture[2] == 0 || texture[3] == 0 || texture[4] == 0 
		|| texture[5] == 0 || texture[6] == 0 || texture[7] == 0 || texture[8] == 0 || texture[9] == 0)
		return false;


	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texture[8]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texture[9]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}

void init()
{
	if (loadTextures() == 0)
	{
		MessageBox(NULL, L"Nie zaladowano tekstur. Program moze nie dzialac poprawnie.", L"Blad", MB_OK);
	}

	GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightPosition2[] = { 0.0f, 20.0f, 0.0f, 1.0f };
	GLfloat LightPosition1[] = { 10.0f, 10.0f, 10.0f, 1.0f };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 10.0 };

	GLfloat ambient[] = { ambientLevel, ambientLevel, ambientLevel, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_specular);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition2);	// Position The Light

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);	// Position The Light

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glEnable(GL_LIGHTING);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

}

void keypressed(unsigned char key, int x, int y)
{
	// ruszanie kamerka
	// prawo
	if (key == 'a')
	{
		current_yRotation -= 1;
	}
	// lewo
	if (key == 's')
	{
		current_yRotation += 1;
		//glRotatef(1.0f, 0.0f, 1.0f, 0.0f);
	}
	// gora
	if (key == 'w')
	{
		current_xRotation -= 1;
		//glRotatef(-1.0f, 1.0f, 0.0f, 0.0f);
	}
	// dol
	if (key == 'z')
	{
		current_xRotation += 1;
		//glRotatef(1.0f, 1.0f, 0.0f, 0.0f);
	}

	if (key == 'q')
	{
		ambientLevel -= 0.1;
	}

	if (key == 'e')
	{
		ambientLevel += 0.1;
	}
}

void mouseMove(int x, int y)
{
	lastx = x;
	lasty = y;
}


void displayObjects(int frame_no)
{
	glRotatef(-mouseSpeed*lasty + 100 , 1.0f, 0.0f, 0.0f);
	glRotatef(mouseSpeed*lastx, 0.0, 1.0f, 0.0f);
	rysujOtoczenie(texture[2], texture[3], texture[4], texture[5], texture[6], texture[7]);

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, keySpeed*current_yRotation);
	glTranslatef(keySpeed*current_xRotation, 0.0f, 0.0f);
		// przesuwam plaszczke zeby byla mniej wiecej pod kursorem myszki
		//glTranslatef(-3, 3, 0);
	rysujTulow(texture[0], texture[1], frame_no);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(15, -15, -13);
	glRotatef(90, 0,1, 0);
	babelki(texture[8]);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(-15, -15, -13);
	glRotatef(90, 0, 1, 0);
	babelki(texture[8]);
	glPopMatrix();

}

void display()
{
	
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	if (frame_no<720) frame_no++; else frame_no = 0;
	glPushMatrix();
		displayObjects(0.5*frame_no);
	glPopMatrix();

    glFlush();
	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
    if( h > 0 && w > 0 ) {
      glViewport( 0, 0, w, h );
      glMatrixMode( GL_PROJECTION );
	  gluPerspective(100.0, (GLfloat)w / (GLfloat)h, 1.0, 60.0);

	  glTranslatef(0.0, 0.0, -10.0); //przesuniecie obserwatora
	  //glRotatef(90, 0, 1, 0);
	  glMatrixMode(GL_MODELVIEW);
    }
}


int main(int argc, char** argv)
{
   glutInit( &argc, argv );

   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
   
   glutInitWindowPosition( 0, 0 );
   glutInitWindowSize( 600, 600 );

   glutCreateWindow( "Plaszczka" );

   glutDisplayFunc( display );
   glutReshapeFunc( reshape );

   glutIdleFunc(display); 

   glutKeyboardFunc(keypressed);
   glutPassiveMotionFunc(mouseMove);

   init();

   glutMainLoop();

   return 0;
}
