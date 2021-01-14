#include <windows.h> // use as needed for your system
#include <gl/Gl.h>
#include <gl/glut.h>
#include <cmath>
#include<iostream>
//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void)
{
    glClearColor(0.75,0.75,0.75,1.0); // set white background color
    glColor3f(1.0f, 1.0f, 1.0f); // set the drawing color
    glPointSize(2.0); // a ‘dot’ is 4 by 4 pixels
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glPointSize(4);
    gluOrtho2D(-2000, 2000, -2000 ,2000);
}
class GLpoint
{
public:
    GLdouble x,y;
};
double mymean = 1;
long prev = 17101061;
//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
/*GLpoint random(GLdouble N)
{
    GLpoint point;
    GLdouble randomNumber = (GLdouble)rand() / N;
    GLdouble randomNumber2 = (GLdouble)rand() / N;
    if(log(randomNumber) != 0)
    {
        GLdouble x = sqrt(-2 * log(randomNumber)) * cos(2 * M_PI * randomNumber2);
        GLdouble y = sqrt(-2 * log(randomNumber)) * sin(2 * M_PI * randomNumber2);

        point.x = x;
        point.y = y;
        return point;
    }
    else
    {
        point.x = 0;
        point.y = 0;
        return point;
    }
}
*/
void drawDot(double x, double y)
{
    int i = rand() % 2;
    if (i == 0)
        glColor3f(1.0, 0.0 , 0.0);
    else
        glColor3f(1.0,1.0,0.2);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}
//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
double rand_gen() {
   // return a uniformly distributed random value
   return ( (double)(rand()) + 1. )/( (double)(RAND_MAX) + 1. );
}
double normalRandom(double means) {
   // return a normally distributed random value
   double rand_1=rand_gen();
   double rand_2=rand_gen();
   double stdDev = 30;
   double mean = means;
   return cos(2*3.14*rand_2)*sqrt(-2.*log(rand_1)) * stdDev * mean;
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);


    for(int i = 0; i < 10000; i++)
    {
        drawDot(normalRandom(mymean), normalRandom(mymean));
    }
    glFlush();
}
void myTimer(int t)
{
    mymean += 1;
    glutPostRedisplay();
    glutTimerFunc(100, myTimer, 0);
}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
    glutInitWindowSize(640,480); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("my first attempt"); // open the screen window
    glutTimerFunc(500, myTimer, 0);
    glutDisplayFunc(myDisplay); // register redraw function
    myInit();
    glutMainLoop(); // go into a perpetual loop
}
