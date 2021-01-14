#include <windows.h> // use as needed for your system
#include <gl/Gl.h>
#include <gl/glut.h>
#include <fstream>
#include <string>
#include<iostream>
#include <typeinfo>
#include <cmath>

using namespace std;
//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void)
{
    glClearColor(0.0,0.0,0.0,0.0); // set white background color
    glColor3f(1.0f, 1.0f, 1.0f); // set the drawing color
    glPointSize(4.0); // a ‘dot’ is 4 by 4 pixels
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 900, -200 , 700);
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void drawDot(GLint x, GLint y)
{
    // draw dot at integer point (x, y)
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

int max_x = INT_MIN, min_x = INT_MAX, max_y = INT_MIN, min_y = INT_MAX;

void calcMaxMin()
{
    GLint numpolys, numLines, x,y;
    fstream indstream;
    indstream.open("C:\\Users\\Rafiq\\Desktop\\Semester6UBIT\\ComputerGraphics\\OpenGL\\dinoDrawing\\dino.dat",std::fstream::in);
    if(indstream.fail())
    {
        cout << "Can't open the file" << endl;
        return;
    }
    indstream >> numpolys; // read the number of polylines
    for(int j = 0; j < numpolys; j++) // read each polyline
    {
        indstream >> numLines;
        for (int i = 0; i < numLines; i++)
        {
            indstream >> x >> y;
            if(x > max_x) max_x = x;
            if(x < min_x) min_x = x;
            if(y > max_y) max_y = y;
            if(y < min_y) min_y = y;
        }
        std::cout << min_x << " " << max_x << " " << min_y << " " << max_y  << endl;
    }
    indstream.close();

}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_STRIP);
    fstream instream;
    instream.open("C:\\Users\\Rafiq\\Desktop\\Semester6UBIT\\ComputerGraphics\\OpenGL\\dinoDrawing\\dino.dat",std::fstream::in);
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

    calcMaxMin();



    float mid_x = (min_x + max_x) / 2.0;
    float mid_y = (min_y + max_y) / 2.0;
    float r = sqrt(pow((max_x - mid_x),2) + pow((max_y-mid_y),2));
    glBegin(GL_LINE_LOOP);
    for(int ii = 0; ii < 40; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(40);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + (max_x-min_x)/2, y + (max_y-min_y) / 2);//output vertex

    }
    glEnd();

    /*glBegin(GL_LINES);
    glVertex2d(min_x, min_x);
    glVertex2d(max_x, min_y);
    glVertex2d(max_x, min_y);
    glVertex2d(max_x, max_y);
    glVertex2d(max_x, max_y);
    glVertex2d(min_x, max_y);
    glVertex2d(min_x, max_y);
    glVertex2d(min_x, min_y);
    glEnd();*/

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
    glutMainLoop(); // go into a perpetual loop
}

