/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

    float Cx = 0.0f, Cy = 5.0f, Cz = 10.0f;
    float Lx = 0.0f, Ly = 1.0f, Lz = 0.0f;

/* GLUT callback Handlers */

float view_rotx = 20.0f, view_roty = 30.0f;
int oldMouseX, oldMouseY;

void initGL(){
    glShadeModel(GL_FLAT);
    float ambient[] = {1.0f,1.0f,1.0f,1.0f};
    float diffuse[] = {1.0f,1.0f,1.0f,1.0f};
    float specular[] = {0.2f,1.0f,0.2f,1.0f};
    float position[] = {20.0f,30.0f,20.0f,0.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

    float mambient[] ={0.1745f, 0.01175f, 0.01175f, 0.55f};
    float mdiffuse[] ={0.61424f, 0.04136f, 0.04136f, 0.55f };
    float mspecular[] ={0.727811f, 0.626959f, 0.626959f, 0.55f };
    float mshine =76.8f;

    glMaterialfv(GL_FRONT,GL_AMBIENT,mambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mdiffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mspecular);
    glMaterialf (GL_FRONT,GL_SHININESS,mshine);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}

void Drone(float radius, float length){
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

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(Cx,Cy,Cz, // eye pos
	Lx,Ly,Lz, // look at
	0,1,0); // up
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glRotatef(90,1,0,0);
	Drone(1.2f, 0.5f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(2.0f,0.0f,2.0f);
	glRotatef(90,1,0,0);
	Drone(0.5f, 0.5f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.0f,0.0f,2.0f);
	glRotatef(90,1,0,0);
	Drone(0.5f, 0.5f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.0f,0.0f,-2.0f);
	glRotatef(90,1,0,0);
	Drone(0.5f, 0.5f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(2.0f,0.0f,-2.0f);
	glRotatef(90,1,0,0);
	Drone(0.5f, 0.5f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.8f,-0.2f,0.8f);
	glRotatef(45,0,1,0);
	Drone(0.1f, 1.2f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.8f,-0.2f,0.8f);
	glRotatef(-45,0,1,0);
	Drone(0.1f, 1.2f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.8f,-0.2f,-0.8f);
	glRotatef(-135,0,1,0);
	Drone(0.1f, 1.2f);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.8f,-0.2f,-0.8f);
	glRotatef(135,0,1,0);
	Drone(0.1f, 1.2f);
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void timer(int value){
	glutPostRedisplay();
	glutTimerFunc(15, timer, 0);
}

void reshape(GLsizei width, GLsizei height){
	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	glViewport(30, 6, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, aspect, 1.0f, 20.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouseControl(int button, int state, int x, int y){
	oldMouseX = x;
	oldMouseY = y;
}

void mouseMotion(int x, int y){
	int getX = x;
	int getY = y;
	float thetaY = 360.0f*(getX - oldMouseX)/640;
	float thetaX = 360.0f*(getY - oldMouseY)/480;
	oldMouseX = getX;
	oldMouseY = getY;
	view_rotx += thetaX;
	view_roty += thetaY;
}

void keyFunction(unsigned char key, int x, int y){
    // Agar fungsi ini bekerja, pastikan CapsLock menyala
    switch(key){
        case 87: // huruf W
            Cz += 1;
            Lz += 1;
            break;
        case 65: // huruf A
            Cx -= 1;
            Lx -= 1;
            break;
        case 83: // huruf S
            Cz -= 1;
            Lz -= 1;
            break;
        case 68: // huruf D
            Cx += 1;
            Lx += 1;
            break;
        case 73: // huruf I
            break;
        case 79: // huruf O
            break;
        case 86: // huruf V
            break;
    }
}

void keyControl(int k, int x, int y){
    switch(k){
        case GLUT_KEY_UP: // tombol panah atas
            Cy += 1;
            Ly += 1;
            break;
        case GLUT_KEY_DOWN: // tombol panah bawah
            Cy -= 1;
            Ly -= 1;
            break;
    }
}

/* Program entry point */

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("3d-control");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	initGL();
	glutSpecialFunc(keyControl);
    glutKeyboardFunc(keyFunction);
	glutMouseFunc(mouseControl);
	glutMotionFunc(mouseMotion);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
	return 0;
}
