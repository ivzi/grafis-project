#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include "math.h"
#include <iostream>
using namespace std;

bool power = false, isOff = false;
float posX = 0.0f, posY = 0.0f, posZ = 0.0f;

void keyFunction(unsigned char key, int x, int y){
    switch(key){
        case 73: // I
            power = true;
        break;
        case 79: // O
            isOff = true;
        break;
        case 75: // K
            if (power == true)
                posY += 0.2f;
        break;
        case 76: // L
            if (power == true && posY > 0)
                posY -= 0.2f;
        break;
        case 87: // W
            if (power == true)
                posZ -= 0.2f;
        break;
        case 83: // S
            if (power == true)
                posZ += 0.2f;
        break;
        case 65: // A
            if (power == true)
                posX -= 0.2f;
        break;
        case 68: // D
            if (power == true)
                posX += 0.2f;
        break;
    }
}

void initGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

float deg2Rad (float sudut) {
	return sudut * (22/7) / 180;
}

void Tube(float radius, float length){
    float BODY_RADIUS=radius;
    float BODY_LENGTH=length;
    int SLICES=50;
    int STACKS=50;
    GLUquadric *q = gluNewQuadric();
    gluCylinder(q, BODY_RADIUS, BODY_RADIUS, BODY_LENGTH, SLICES, STACKS);
    gluDisk(q, 0.0f, BODY_RADIUS, SLICES, STACKS); //lingkaran untuk tutup atas
    glTranslatef(0.0f, 0.0f, BODY_LENGTH);
    gluDisk(q, 0.0f, BODY_RADIUS, SLICES, STACKS); //lingkaran untuk tutup bawah
}

void balingBaling()
{
	glBegin(GL_TRIANGLES);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0.5);
	glVertex3f(1, 0, -0.5);
	glVertex3f(0, 0, 0);
	glVertex3f(-1, 0, 0.5);
	glVertex3f(-1, 0, -0.5);
	glEnd();
}

void falling()
{
    keyFunction('L',0,0);
    // STOP ENGINE
    if (posY < 0){
        power = false;
        isOff = false;
    }
}

GLfloat angle = 0.0f;
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(posX,posY,posZ);

    // MAIN BODY
	glPushMatrix();
	glTranslatef(0, -2, -12);
    glRotatef(90,1,0,0);
	glColor3f(1,0,0);
	Tube(1.2f, 0.5f);
	glPopMatrix();

	// FALLING EVENT
	if (isOff){
	    falling();
	}

	// ROTOR PLATE
	for (int a=0; a<4; a++) {
		glPushMatrix();
	}
	for (int x=-3; x<=3; x+=6) {
		for (int z=-10; z>=-14; z-=4) {
			glTranslatef(x, -2, z);
			glRotatef(90,1,0,0);
			Tube(0.7f, 0.5f);
			glPopMatrix();
		}
	}

	// SKELETON
	glPushMatrix();
	glTranslatef(2.5f,-2.25f,-14.0f);
	glRotatef(-45,0,1,0);
	glColor3f(1,1,0);
	Tube(0.1f, 2.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.5f,-2.25f,-14.0f);
	glRotatef(45,0,1,0);
	glColor3f(1,1,0);
	Tube(0.1f, 2.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.5f,-2.25f,-10.0f);
	glRotatef(135,0,1,0);
	glColor3f(1,1,0);
	Tube(0.1f, 2.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.5f,-2.25f,-10.0f);
	glRotatef(-135,0,1,0);
	glColor3f(1,1,0);
	Tube(0.1f, 2.0f);
	glPopMatrix();

	// ROTOR
	for (int i=0; i<4; i++) {
		glPushMatrix();
	}
	glColor3f(1,1,0);
	for (int x=-3; x<=3; x+=6) {
		for (int z=-10; z>=-14; z-=4) {
			glPopMatrix();
			glTranslatef(x, -1.9, z);
			if (power){
				glRotatef(angle, 0, 1, 0);
				angle += 5;
			} else {
				glRotatef(angle, 0, 1, 0);
                angle += 0;
			}
			balingBaling();
		}
	}

	glPopMatrix();
	glutSwapBuffers();
}

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(15, timer, 0);
}

void reshape(GLsizei width, GLsizei height)
{
	if (height == 0)
		height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("3d-animation");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	initGL();
	glutTimerFunc(0, timer, 0);
	glutKeyboardFunc(keyFunction);
	glutMainLoop();
	return 0;
}
