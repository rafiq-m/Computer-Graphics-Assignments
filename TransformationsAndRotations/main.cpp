#include <windows.h> // use as needed for your system
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>

void myInit(void)
{
    glClearColor(1.0,1.0,1.0,0.0); // set white background color
    glColor3f(0.0f, 0.0f, 0.0f); // set the drawing color
    glPointSize(2.0); // a ‘dot’ is 4 by 4 pixels
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-150, 150 , -150 , 150);
}

void drawDot(float x, float y, float r,float g,float b)
{
    glBegin(GL_POINTS);
    glColor3f(r,g,b);
    glVertex2f(x,y);
    glEnd();
}

void drawBox(float r,float g,float b)
{
    glColor3f(r,g,b);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(30, 0);
    glVertex2f(30, 30);
    glVertex2f(0, 30);
    glEnd();
}
//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{

    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    drawBox(0,0,0);
    for(int i = -200 ; i < 200 ; i++)
    {
        drawDot(i,0,1,0,0);
        drawDot(0,i,1,0,0);
    }

    glTranslated(50, 0 , 0);        //Replaced by rotate in second scenario
    drawBox(0.2,0.2,0.2);
    for(int i = -200 ; i < 200 ; i++)
    {
        drawDot(i,0,0,1,0);
        drawDot(0,i,0,1,0);
    }
    glRotated(45,0,0,1);           //Replaced by translate in second scenario
    drawBox(0.2,0.2,0.2);
    for(int i = -200 ; i < 200 ; i++)
    {
        drawDot(i,0,0,0,1);
        drawDot(0,i,0,0,1);
    }
    glFlush(); // send all output to display
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
    return EXIT_SUCCESS;
}
