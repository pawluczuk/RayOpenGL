#include <windows.h>
#include <GL/gl.h>
#include "glut.h"
#include <math.h>
#include "stale.h"
#include <iostream>


/*scalex - scaling of sphere around x-axis
scaley - scaling of sphere around y-axis
r - radius of sphere
*/

const int sin_frequency = 50;
const int radius = 4;

inline GLfloat sinRadian(int alfa)
{
	return sin(2 * M_PI * alfa / 360);
}

inline GLfloat cosRadian(int alfa)
{
	return cos(2 * M_PI * alfa / 360);
}

void przeksztalc(GLfloat* tab, int frame_no)
{
	// falowanie "parabola"
	GLfloat moc_obrotu = sinRadian(2*frame_no);
	GLfloat delta = abs(tab[0]);
	tab[2] += 0.4*(delta*delta)*moc_obrotu; 
	
	// falowanie "sinusoida"
	tab[2] -= 0.2*delta*sin(sin_frequency*M_PI * frame_no / 360 + tab[1]);
	
}

void drawHalf(double radius, int szerokosc, int dlugosc, GLuint texture, int frame_no = 0)
{
	for (int i = 1; i <= szerokosc; i++)
	{
		double theta = M_PI_2 * ((double)(i - 1) / szerokosc);
		double theta_1 = M_PI_2 *((double)(i) / szerokosc);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_TRIANGLE_STRIP);
		
		for (int k = 0; k <= dlugosc; k++)
		{
			// texture coordinators
			double s1, s2, t;
			s1 = ((double)i) / szerokosc;
			s2 = ((double)i + 1) / szerokosc;
			t = ((double)k) / dlugosc;

			double fi = 2 * M_PI * (double)(k - 1) / dlugosc;
			GLfloat tab[3] = { radius*cos(theta)*cos(fi), radius*sin(fi)*cos(theta), radius*sin(theta) };
			przeksztalc(tab, frame_no);
			glTexCoord2d(s1, t);
			glNormal3f(tab[0], tab[1], tab[2]);
			glVertex3f(tab[0], tab[1], tab[2]);

			GLfloat tab2[3] = { radius*cos(theta_1)*cos(fi), radius*sin(fi)*cos(theta_1), radius*sin(theta_1) };
			przeksztalc(tab2, frame_no);
			glTexCoord2d(s2, t);
			glNormal3f(tab2[0], tab2[1], tab2[2]);
			glVertex3f(tab2[0], tab2[1], tab2[2]);

			// ogonek
			//if ( fi >= 4.5 && fi <= 5 && i == 1)
			//{
			//	GLfloat tab3[3] = { 0, -8, 0 };
			//	przeksztalc(tab3, frame_no);
			//	glTexCoord2d(s2, t);
			//	glNormal3f(tab3[0], tab3[1], tab3[2]);
			//	glVertex3f(tab3[0], tab3[1], tab3[2]);

			//	//glTexCoord2d(s1, t);
			//	//glNormal3f(tab[0], tab[1], tab[2]);
			//	//glVertex3f(tab[0], tab[1], tab[2]);
			//	glTexCoord2d(s2, t);
			//	glNormal3f(tab2[0], tab2[1], tab2[2]);
			//	glVertex3f(tab2[0], tab2[1], tab2[2]);

			//}
		}
		glEnd();
	}

}
void rysujTulow(GLuint textureGora, GLuint textureDol, int frame_no)
{
	
	// renderuj gore plaszczki
	glPushMatrix();
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_FRONT);
	glScalef(1, 0.3, 1);
	glRotatef(-90, 1, 0, 0);
	drawHalf(radius, 10,100, textureGora, frame_no);
	glPopMatrix();

	
	// renderuj dol plaszczki
	glPushMatrix();
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glScalef(1, 0.3, 1);
	glRotatef(-90, 1, 0, 0);
	drawHalf(radius, 10, 100, textureDol, frame_no);
	glPopMatrix();
	glDisable(GL_CULL_FACE);

}

void rysujOczy()
{
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslatef(0, 5, 0);
		glutSolidSphere(0.5, 5, 5);
	glPopMatrix();

}


