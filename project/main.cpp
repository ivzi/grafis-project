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

float Cx = 0.0f, Cy = 0.0f, Cz = 0.0f;
float Lx = 0.0f, Ly = 0.5f, Lz = -20.0f;
float angle_depanBelakang = 0.0f;
float angle_depanBelakang2 = 0.0f;
float angle_samping = 0.0f;
float angle_samping2 = 0.0f;
float angle_vertikal = 0.0f;
float angle_vertikal2 = 0.0f;
bool ori = true, kamera = false, kamera1 = false, kamera2 = false, kamera3 = false, kamera4 = false, kamera5 = false;
bool power = false, isOff = false;
float posX = 0.0f, posY = 0.0f, posZ = 0.0f;

float toRadians(float angle){
    return angle * M_PI / 180;
}

class Vector{
    public:
    float x, y, z;
    void set_values (float startX, float startY, float startZ){
    x = startX;
    y = startY;
    z = startZ;
}
void vectorRotation(Vector refs, float angle){
    Vector temp = refs;
    float magnitude = sqrt(pow(temp.x, 2) + pow(temp.y, 2) + pow(temp.z, 2));
    temp.x = temp.x / magnitude;
    temp.y = temp.y / magnitude;
    temp.z = temp.z / magnitude;
    float dot_product = (x * temp.x)+(y * temp.y)+(z * temp.z);
    float cross_product_x = (y * temp.z) - (temp.z * z);
    float cross_product_y = -((x * temp.z) - (z * temp.x));
    float cross_product_z = (x * temp.y) - (y * temp.x);
    float last_factor_rodrigues = 1.0f - cos(toRadians(fmod(angle, 360.0f)));
    x = (x * cos(toRadians(fmod(angle, 360.0f)))) + (cross_product_x * sin(toRadians(fmod(angle, 360.0f)))) + (dot_product * last_factor_rodrigues * x);
    y = (y * cos(toRadians(fmod(angle, 360.0f)))) + (cross_product_y * sin(toRadians(fmod(angle, 360.0f)))) + (dot_product * last_factor_rodrigues * y);
    z = (z * cos(toRadians(fmod(angle, 360.0f)))) + (cross_product_z * sin(toRadians(fmod(angle, 360.0f)))) + (dot_product * last_factor_rodrigues * z);
    }
};
Vector depanBelakang, samping, vertikal;

void cameraRotation(Vector refer, double angle){
    float M = sqrt(pow(refer.x, 2) + pow(refer.y, 2) + pow(refer.z, 2));
    float Up_x1 = refer.x / M;
    float Up_y1 = refer.y / M;
    float Up_z1 = refer.z / M;
    float VLx = Lx - Cx;
    float VLy = Ly - Cy;
    float VLz = Lz - Cz;
    float dot_product = (VLx * Up_x1) + (VLy * Up_y1) + (VLz * Up_z1);
    float cross_product_x = (Up_y1 * VLz) - (VLy * Up_z1);
    float cross_product_y = -((Up_x1 * VLz) - (Up_z1 * VLx));
    float cross_product_z = (Up_x1 * VLy) - (Up_y1 * VLx);
    float last_factor_rodrigues = 1.0f - cos(toRadians(angle));
    float Lx1 = (VLx * cos(toRadians(angle))) + (cross_product_x * sin(toRadians
    (angle))) + (dot_product * last_factor_rodrigues * VLx);
    float Ly1 = (VLy * cos(toRadians(angle))) + (cross_product_y * sin(toRadians
    (angle))) + (dot_product * last_factor_rodrigues * VLy);
    float Lz1 = (VLz * cos(toRadians(angle))) + (cross_product_z * sin(toRadians
    (angle))) + (dot_product * last_factor_rodrigues * VLz);
    Lx = Lx1+Cx;
    Ly = Ly1+Cy;
    Lz = Lz1+Cz;
}

void keyFunction(unsigned char key, int x, int y){
    switch(key){
        case 13: // Enter
            power = true;
        break;
        case 82: // R
            isOff = true;
        break;
        case 81: // Q
            if (power == true)
                posY += 0.2f;
        break;
        case 69: // E
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
        case 90: // Z
        angle_depanBelakang += 15.0f;
        samping.vectorRotation(depanBelakang, angle_depanBelakang - angle_depanBelakang2);
        vertikal.vectorRotation(depanBelakang, angle_depanBelakang - angle_depanBelakang2);
        angle_depanBelakang2 = angle_depanBelakang;
        break;
        case 88: // X
            angle_depanBelakang -= 15.0f;
            samping.vectorRotation(depanBelakang, angle_depanBelakang - angle_depanBelakang2);
            vertikal.vectorRotation(depanBelakang, angle_depanBelakang - angle_depanBelakang2);
            angle_depanBelakang2 = angle_depanBelakang;
        break;
        case 74: // J
            angle_vertikal += 5.0f;
            samping.vectorRotation(vertikal, angle_vertikal - angle_vertikal2);
            depanBelakang.vectorRotation(vertikal, angle_vertikal - angle_vertikal2);
            cameraRotation(vertikal, angle_vertikal - angle_vertikal2);
            angle_vertikal2 = angle_vertikal;
        break;
        case 76: // L
            angle_vertikal -= 5.0f;
            samping.vectorRotation(vertikal, angle_vertikal - angle_vertikal2);
            depanBelakang.vectorRotation(vertikal, angle_vertikal - angle_vertikal2);
            cameraRotation(vertikal, angle_vertikal - angle_vertikal2);
            angle_vertikal2 = angle_vertikal;
        break;
        case 73: // I
            angle_samping -= 5.0f;
            depanBelakang.vectorRotation(samping, angle_samping - angle_samping2);
            cameraRotation(samping, angle_samping - angle_samping2);
            angle_samping2 = angle_samping;
        break;
        case 75: // K
            angle_samping += 5.0f;
            depanBelakang.vectorRotation(samping, angle_samping - angle_samping2);
            cameraRotation(samping, angle_samping - angle_samping2);
            angle_samping2 = angle_samping;
        break;
    }
}

void initGL(){
    depanBelakang.set_values(0.0f, 0.0f, -1.0f);
    samping.set_values(1.0f, 0.0f, 0.0f);
    vertikal.set_values(0.0f, 1.0f, 0.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
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

void Soccer_Field (void)
{
    float x, y, ang, radius = 0.1;

    static float RAD_DEG = 57.296;

    glBegin (GL_QUADS);
       glColor3f  (0.20, 0.60, 0.20);
       glVertex2f (-1.10, -0.90);
       glVertex2f (2.50, -0.90);
       glVertex2f (2.50, 1.8);
       glVertex2f (-1.10, 1.8);
       glColor3f  (1.0, 1.0, 1.0);
    glEnd ();

    glColor3f (0.0, 0.0, 0.0);

    glBegin (GL_LINES);
       glVertex2f (0.70, -0.90);
       glVertex2f (0.70, 1.8);
    glEnd ();
}

void falling()
{
    keyFunction('E',0,0);
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

    gluLookAt(Cx, Cy, Cz,
    Lx, Ly, Lz,
    vertikal.x, vertikal.y, vertikal.z);
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

	glPushMatrix();
    glTranslated(-0.8,-1.45,-3);
    glRotated(-90,1,0,0);
    Soccer_Field();
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
	if (height == 0) height = 1;
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
