#include <windows.h>
#include <GL/gl.h>
#include "glut.h"
#include <math.h>
#include "stale.h"

void swiatloOtoczenia()
{
	GLfloat LightAmbient[] = { 1, 1, 1, 1.0f };
	GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightPosition2[] = { 2.5f, 2.5f, -2.5f, 1.0f };
	GLfloat LightPosition3[] = { -2.5f, -2.5f, 2.5f, 1.0f };
	glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT2, GL_POSITION, LightPosition2);	// Position The Light

	glLightfv(GL_LIGHT3, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT3, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT3, GL_POSITION, LightPosition3);	// Position The Light
	
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
}

void rysujOtoczenie(GLuint textureBack, GLuint textureDown, GLuint textureFront, GLuint textureLeft, GLuint textureRight, GLuint textureUp)
{

	//swiatloOtoczenia();
	glPushMatrix();
	int k = 20;
	glScalef(k, k, k);
	glColor4f(1, 1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, textureBack);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();
	// Back Face
	//glBegin(GL_LINES);
	glBindTexture(GL_TEXTURE_2D, textureFront);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	// Top Face
	//glBegin(GL_LINES);
	glBindTexture(GL_TEXTURE_2D, textureUp);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();
	// Bottom Face
	//glBegin(GL_LINES);
	glBindTexture(GL_TEXTURE_2D, textureDown);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();
	// Right face
	//glBegin(GL_LINES);
	glBindTexture(GL_TEXTURE_2D, textureRight);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();
	// Left Face
	//glBegin(GL_LINES);
	glBindTexture(GL_TEXTURE_2D, textureLeft);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();
	glPopMatrix();
}