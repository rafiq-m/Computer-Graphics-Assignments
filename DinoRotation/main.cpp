#include <windows.h> // use as needed for your system
#include<GL/gl.h>
#include<GL/glu.h>
#include <fstream>
#include<GL/glut.h>
#include <iostream>

using namespace std;
//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>

void drawDot(GLint x, GLint y)
{
    // draw dot at integer point (x, y)
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void myInit(void)
{
    glClearColor(1.0,1.0,1.0,0.0); // set white background color
    glColor3f(0.0f, 0.0f, 0.0f); // set the drawing color
    glPointSize(2.0); // a ‘dot’ is 4 by 4 pixels
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-640*4, 640.0*4, -480*4, 480.0*4);
    glMatrixMode(GL_MODELVIEW);
}
//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>


void drawDino()
{
    glBegin(GL_LINE_STRIP);
    fstream instream;
    instream.open("C:\\Users\\Rafiq\\Desktop\\Semester6UBIT\\ComputerGraphics\\OpenGL\\DinoRotation\\dino.dat",std::fstream::in);
    if(instream.fail())
    {
        cout << "Can't open the file" << endl;
        return;
    }
    GLint numpolys, numLines, x,y;
    instream >> numpolys; // read the number of polylines
    for(int j = 0; j < numpolys; j++) // read each polyline
    {
        instream >> numLines;
        glBegin(GL_LINE_STRIP); // draw the next polyline
        for (int i = 0; i < numLines; i++)
        {
            instream >> x >> y; // read the next x, y pair
            glVertex2i(x,  y);
        }
        glEnd();
    }
    instream.close();
}

void drawDot(float x, float y, float r,float g,float b)
{
    glBegin(GL_POINTS);
    glColor3f(r,g,b);
    glVertex2f(x,y);
    glEnd();
}
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    double angle = 360/12;
    for(int i =1; i <= 12 ; i++)
    {
        glPushMatrix();
        glRotated(-angle * i,0,0,1);
        glTranslated(0, 900, 0 );
        glRotated(angle * i , 0 , 0 ,1);
        drawDino();
        glPopMatrix();
    }
    glutSwapBuffers();
}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set display mode
    glutInitWindowSize(640,480); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("Dino Rotatation"); // open the screen window
    glutDisplayFunc(myDisplay); // register redraw function
    myInit();
    glutMainLoop(); // go into a perpetual loop
    return EXIT_SUCCESS;
}
