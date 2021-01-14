#include <windows.h> // use as needed for your system
#include <gl/Gl.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<cmath>
#include<iostream>
using namespace std;
//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void)
{
    glClearColor(1.0,1.0,1.0,0.0); // set white background color
    glColor3f(1.0f, 1.0f, 1.0f); // set the drawing color
    glPointSize(4.0); // a ‘dot’ is 4 by 4 pixels
}

//--------------- setWindow ---------------------
void setWindow(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(left, right, bottom, top);
}
//---------------- setViewport ------------------
void setViewport(GLint left, GLint right, GLint bottom, GLint top)
{
    glViewport(left, bottom,right-left, top - bottom);
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>

void myDisplay(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glBegin(GL_LINE_STRIP);
    for(GLfloat x = 0; x < 20; x += 0.05)  // draw the plot
    {
        glVertex2f(x, sin(x));
        std::cout << x << sin(x) << endl;
    }
    glEnd();
    glFlush();
}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
    glutInitWindowSize(640,480); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("my first attempt"); // open the screen window
    glutDisplayFunc(myDisplay); // register redraw function
    myInit();
    setWindow(0, 91, -5, 5); // set the window
    setViewport(0, 640, 0, 480); // set the viewport
    glutMainLoop(); // go into a perpetual loop
    return EXIT_SUCCESS;
}
