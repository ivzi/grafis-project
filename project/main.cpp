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
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

    float Cx = 0.0f, Cy = 10.0f, Cz = 15.0f;
    float Lx = 0.0f, Ly = 4.0f, Lz = 0.0f;

/* GLUT callback Handlers */

void objek(){
    glBegin(GL_POLYGON);
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(2.0f,0.0f,0.0f);
        glVertex3f(0.0f,4.0f,0.0f);
        glVertex3f(-2.0f,0.0f,0.0f);
    glEnd();
}

void tempat(){
    glBegin(GL_POLYGON);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(4.0f,0.0f,4.0f);
        glVertex3f(-4.0f,0.0f,4.0f);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-4.0f,0.0f,-4.0f);
        glVertex3f(4.0f,0.0f,-4.0f);
    glEnd();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
	glLoadIdentity();
	gluLookAt(Cx,Cy,Cz,
                Lx,Ly,Lz,
                0,1,0);
    tempat();
    objek();
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

void keyFunction(unsigned char key, int x, int y){
    // Agar fungsi ini bekerja, pastikan CapsLock menyala
    switch(key){
        case 87: // huruf W
            Cz += 2;
            Lz += 2;
            break;
        case 65: // huruf A
            Cx -= 2;
            Lx -= 2;
            break;
        case 83: // huruf S
            Cz -= 2;
            Lz -= 2;
            break;
        case 68: // huruf D
            Cx += 2;
            Lx += 2;
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
            Cy += 2;
            Ly += 2;
            break;
        case GLUT_KEY_DOWN: // tombol panah bawah
            Cy -= 2;
            Ly -= 2;
            break;
    }
}

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Project Grafis");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(keyControl);
    glutKeyboardFunc(keyFunction);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
	return 0;
}
