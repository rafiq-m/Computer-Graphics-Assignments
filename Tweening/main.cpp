#include <windows.h> // use as needed for your system
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<iostream>
#define pi 3.141592654

using namespace std;
//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>


float x_0 =0, y_0=0,x=0,y=0  ;
float theta = (pi)/180 * 80;     //Angle Input  ANGLE
float vi = 110; //meters per second  SPEED
float tof ;    //time of flight
float X[100],Y[100];
float max_x = 0, max_y  = 0;
int incr = 0;

void calcTrajectory(void)
{
    int i;
    tof = 2*vi*sin(theta)/9.81;
    float del_t = tof/100;
    float temp=0;
    for(i=0; i<100; i++)
    {
        x = vi*cos(theta)*temp;
        y = vi*sin(theta)*temp - ((9.81*temp*temp)/2);
        X[i]=x;
        Y[i]=y;
        temp += del_t;
    }

    for(int i =0 ; i < 100; i++)
    {
        if(max_x < X[i]) max_x = X[i];
        if(max_y < Y[i]) max_y = Y[i];
    }
    cout << max_x << " " << max_y << endl;
}
void myInit(void)
{

    glClearColor(1.0,1.0,1.0,0.0); // set white background color
    glColor3f(0.0f, 0.0f, 0.0f); // set the drawing color
    glPointSize(2.0); // a ‘dot’ is 4 by 4 pixels
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
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
void drawBox(float a, float b)
{
    glBegin(GL_LINE_STRIP);
    glVertex2f(a+0 ,b+0);
    glVertex2f(a+3, b+0);
    glVertex2f(a+3,b+ 3);
    glVertex2f(a+0,b+3);
    glVertex2f(a+0, b+0 );
    glEnd();
}
//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    for(int i = 0 ; i < incr ; i++)
    {
        glBegin(GL_LINE_STRIP);
        glVertex2f(X[i], Y[i]);
        glVertex2f(X[i+1], Y[i+1]);
        glEnd();
    }
    glPushMatrix();
    glTranslated(X[incr], Y[incr], 0);
    drawBox(0 , 0);
    glPopMatrix();
    glutSwapBuffers(); // send all output to display
}

void timer(int i)
{
    if(incr < 99)
    {
        incr++;
        cout << incr << endl;
        glutPostRedisplay();
        glutTimerFunc(50, timer, 0);
    }

}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
    calcTrajectory();
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
    glutInitWindowSize(640,480); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("my first attempt"); // open the screen window
    glutDisplayFunc(myDisplay); // register redraw function
    glutTimerFunc(100, timer, 0);
    myInit();
    glutMainLoop(); // go into a perpetual loop
    return EXIT_SUCCESS;
}
