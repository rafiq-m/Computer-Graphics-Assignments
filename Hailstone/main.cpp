#include <windows.h> // use as needed for your system
#include <gl/Gl.h>
#include <gl/glut.h>
#include <iostream>

using namespace std;
//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>

GLint screenwidth = 640;
GLint screenheight = 480;
// global current position
static GLint greatNumber = 0;
static GLint count = 0;
void myInit(void)
{
    glClearColor(1.0,1.0,1.0,0.0); // set white background color
    glColor3f(0.0f, 0.0f, 0.0f); // set the drawing color
    glPointSize(4.0); // a ‘dot’ is 4 by 4 pixels
    glLineWidth(2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}
class GLintPoint
{
public:
    GLint x, y;
};

GLintPoint CP;
//<<<<<<<<<<<<< moveto >>>>>>>>>>>>>>
void moveto(GLint x, GLint y)
{
    CP.x = x;
    CP.y = y; // update the CP
}
//<<<<<<<<<<<< lineTo >>>>>>>>>>>>>>>>>
void lineto(GLint x, GLint y)
{
    glBegin(GL_LINES); // draw the line
    glVertex2i(CP.x, CP.y );
    glVertex2i(x * screenwidth/count, y * screenheight/greatNumber);
    glEnd();
    glFlush();
    CP.x = x * screenwidth/count;
    CP.y = y * screenheight/greatNumber; // update the CP
}

void drawDot(GLint x, GLint y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}
GLint HailstoneNumbers(GLint N)
{
    static GLint c;
    if (N == 1 && c == 0)
    {
        // N is initially 1.
        lineto(c, N);
        return c;
    }
    else if (N == 1 && c != 0)
    {
        // N is reduced to 1.
        c++;
        lineto(c, N);
        return c;
    }
    else if (N % 2 == 0)
    {
        // If N is Even.
        c++;
        lineto(c, N);
        HailstoneNumbers(N / 2);
    }
    else if (N % 2 != 0)
    {
        // N is Odd.
        c++;
        lineto(c,N);
        HailstoneNumbers(3 * N + 1);
    }
}

GLint HailstoneNumberscalc(GLint N)
{
    cout << N << " ";
    if (greatNumber  < N ) greatNumber = N;
    if (N == 1 && count == 0)
    {
        return count;
    }
    else if (N == 1 && count != 0)
    {
        // N is reduced to 1.
        count++;
        return count;
    }
    else if (N % 2 == 0)
    {
        // If N is Even.
        count++;
        HailstoneNumberscalc(N / 2);
    }
    else if (N % 2 != 0)
    {
        // N is Odd.
        count++;
        HailstoneNumberscalc(3 * N + 1);
    }
}
//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    GLint n = 61;
    HailstoneNumberscalc(n);
    cout << ":" << greatNumber << " <= Greatest Number:" << count<< "<= Count" << endl;
    glClear(GL_COLOR_BUFFER_BIT);
    moveto(0, 0);
    HailstoneNumbers(n);
}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
    glutInitWindowSize(screenwidth,screenheight); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("Hailstone Sequence"); // open the screen window
    glutDisplayFunc(myDisplay); // register redraw function
    myInit();
    glutMainLoop(); // go into a perpetual loop
}
