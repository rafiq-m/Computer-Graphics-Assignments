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
    gluOrtho2D(-30, 30, -30, 30);
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

void drawTriangle()
{
    glBegin(GL_LINE_STRIP);
    glVertex2f(2,4);
    glVertex2f(4, 6);
    glVertex2f(2, 6);
    glVertex2f(2, 4);
    glEnd();
}
void drawDot(float x, float y, float r,float g,float b)
{
    glBegin(GL_POINTS);
    glColor3f(r,g,b);
    glVertex2f(x,y);
    glEnd();
}
void drawLine()
{
    glBegin(GL_LINES);
    glVertex2f(-10 , (-10+4)/2 );
    glVertex2f(10 , (10+4)/2 );
    glEnd();
}

void drawTooth()
{
    glBegin(GL_LINE_STRIP);
    glVertex2f(0,0);
    glVertex2f(0.2,0.2);
    glVertex2f(0.6,0.2);
    glVertex2f(0.6,0.8);
    glVertex2f(0.2, 0.8);
    glVertex2f(0, 1);
    glEnd();
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    float angle = 360/30.0;
    for(int i = 0 ; i < 30 ; i++)
    {
        glPushMatrix();
        glRotated(angle*i, 0 , 0 ,1);
        glScaled(3.5,3.5,0);
        glTranslated(5, 0 , 0);
        drawTooth();
        glPopMatrix();
    }
    glutSwapBuffers();

    /*glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    for(float i = -20 ; i < 20 ; i+=0.02)
    {
        drawDot(i,0,0,0,0);
        drawDot(0,i,0,0,0);
    }
    drawTriangle();
    drawLine();
    glTranslated(0, 2,  0);
    glRotated(-63.5, 0 , 0 ,1);
    glScaled(-1, 1, 0);
    glRotated(63.5, 0 , 0 , 1);
    glTranslated(0, -2, 0 );
    drawTriangle();
    glutSwapBuffers(); // send all output to display*/
}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set display mode
    glutInitWindowSize(640,480); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("my first attempt"); // open the screen window
    glutDisplayFunc(myDisplay); // register redraw function
    myInit();
    glutMainLoop(); // go into a perpetual loop
    return EXIT_SUCCESS;
}
