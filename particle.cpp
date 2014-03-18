#include <windows.h>
#include <GL/gl.h>
#include "glut.h"
#include <math.h>
#include "stale.h"
#define	MAX_PARTICLES	30		// ilosc babelkow
float	slowdown = 3.0f;				// Slow Down Particles

GLuint	loop;

typedef struct						// struktura babelka
{	// x,y,z - aktualna pozycja; xi,yi,zi - zmiany
	float	x;						
	float	y;						
	float	z;						
	float	xi;						
	float	yi;						
	float	zi;						
}
particles;

particles particle[MAX_PARTICLES];	// tablica babelkow

void babelki(GLuint texture)
{
	glEnable(GL_BLEND);									
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);					
	glEnable(GL_TEXTURE_2D);						
	glBindTexture(GL_TEXTURE_2D, texture);			

	// tworze babelki
	for (loop = 0; loop < MAX_PARTICLES; loop++)
	{
		particle[loop].xi = float((rand() % 50) - 26.0f)*10.0f;
		particle[loop].yi = float((rand() % 50) - 25.0f)*10.0f;
		particle[loop].zi = float((rand() % 50) - 25.0f)*10.0f;
	}

	// petla ruszajaca babelkami
	for (loop = 0; loop<MAX_PARTICLES; loop++)	
	{
		// aktualna pozycja
			float x = particle[loop].x;						
			float y = particle[loop].y;						
			float z = particle[loop].z;					

		// rysujemy nasz babelek
			glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2d(1, 1); glVertex3f(x + 0.5f, y + 0.5f, z); // Top Right
			glTexCoord2d(0, 1); glVertex3f(x - 0.5f, y + 0.5f, z); // Top Left
			glTexCoord2d(1, 0); glVertex3f(x + 0.5f, y - 0.5f, z); // Bottom Right
			glTexCoord2d(0, 0); glVertex3f(x - 0.5f, y - 0.5f, z); // Bottom Left
			glEnd();

		// zmieniamy mu pozycje na nastepne rysowanie
			particle[loop].x += particle[loop].xi / (slowdown * 1000);
			particle[loop].y += particle[loop].yi / (slowdown * 1000);
			particle[loop].z += particle[loop].zi / (slowdown * 1000);
	}

	glDisable(GL_BLEND);
}