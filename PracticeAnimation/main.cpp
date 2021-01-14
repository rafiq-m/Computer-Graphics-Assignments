#include <windows.h> // use as needed for your system
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include <cmath>
#include<vector>
#include<iostream>
using namespace std;
//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
#define PI 3.141592653589
# define deg2rad(deg) (deg * PI / 180.0)

int lengthed = 1;
float angle = 10;
void myInit(void)
{
    glClearColor(0.0,0.0,0.0,1.0); // set white background color
}
struct box
{
    float x_pos;
    float y_pos;
    float box_theta;
    int state = 1;
};

vector<struct box> boxes;
vector <struct box> ::iterator ib;
struct box box1;

void drawBullet()
{
    glBegin(GL_QUADS);

    glVertex2f(-1.0,-1.0-19);
    glVertex2f(1.0,-1.0-19);
    glVertex2f(1.0,1.0-19);
    glVertex2f(-1.0,1.0-19);

    glEnd();
}
//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);



    for(ib = boxes.begin(); ib != boxes.end(); ++ib)
    {
    glPushMatrix();
    glTranslatef(ib->x_pos,ib->y_pos,0);
    drawBullet();
    glPopMatrix();
    }

    glutSwapBuffers();
}

void myfunc(int)
{
    for(ib = boxes.begin(); ib != boxes.end(); ++ib)
    {
        switch(ib->state)
        {
        case 1:
            if(ib->x_pos < 18)
            {
                ib->x_pos += cos(deg2rad(ib->box_theta));
                ib->y_pos += sin(deg2rad(ib->box_theta));
            }
            else
            {
                ib->state = -1;
            }
            break;
        case -1:
            if(ib->x_pos > -18)
            {
                ib->y_pos += sin(deg2rad(ib->box_theta));
                ib->x_pos += -cos(deg2rad(ib->box_theta));
            }
            else
            {
                ib->state = 1;
            }
            break;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(1000/60, myfunc, 0);
}
void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-20.0,20.0,-20.0,20.0);
    glMatrixMode(GL_MODELVIEW);
}

void  drawBox()
{
   box1.x_pos = 0;
   box1.y_pos = 0;
   if(angle > 90 && angle < 180)
   {
       box1.box_theta = 180  - angle;
       box1.state = -1;
   }
   else
   {
   box1.box_theta = angle;
   box1.state = 1;
   }
   boxes.push_back(box1);
}

void handleKeypress(unsigned char key, int x, int y)
{
     if(key==32)
    {
        drawBox();
    }
    else if(key == 'p') //Changing Angle
    {
        cout << angle << " ";
        if(angle < 180)
            angle += 10;
        else
            angle = 10;
    }

}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set display mode

    glutInitWindowSize(500,500); // set window size
    glutInitWindowPosition(200, 100); // set window position on screen
    glutCreateWindow("my first attempt"); // open the screen window

    glutDisplayFunc(myDisplay); // register redraw function
    glutReshapeFunc(reshape);
    glutTimerFunc(1000, myfunc,0);

    glutKeyboardFunc(handleKeypress);

    myInit();

    glutMainLoop(); // go into a perpetual loop

    return EXIT_SUCCESS;
}

















/*
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <stdlib.h>

GLuint theTorus;

static void torus(int numc, int numt)
{
   int i, j, k;
   double s, t, x, y, z, twopi;

   twopi = 2 * (double)M_PI;
   for (i = 0; i < numc; i++) {
      glBegin(GL_QUAD_STRIP);
      for (j = 0; j <= numt; j++) {
         for (k = 1; k >= 0; k--) {
            s = (i + k) % numc + 0.5;
            t = j % numt;

            x = (1+.1*cos(s*twopi/numc))*cos(t*twopi/numt);
            y = (1+.1*cos(s*twopi/numc))*sin(t*twopi/numt);
            z = .1 * sin(s * twopi / numc);
            glVertex3f(x, y, z);
         }
      }
      glEnd();
   }
}
static void init(void)
{
   theTorus = glGenLists (1);
   glNewList(theTorus, GL_COMPILE);
   torus(8, 25);
   glEndList();

   glShadeModel(GL_FLAT);
   glClearColor(0.0, 0.0, 0.0, 0.0);
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);
   glCallList(theTorus);
   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(30, (GLfloat) w/(GLfloat) h, 1.0, 100.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
}

//Rotate about x-axis when "x" typed; rotate about y-axiswhen "y" typed; "i" returns torus to original view
void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
   case 'x':
   case 'X':
      glRotatef(30.,1.0,0.0,0.0);
      glutPostRedisplay();
      break;
   case 'y':
   case 'Y':
      glRotatef(30.,0.0,1.0,0.0);
      glutPostRedisplay();
      break;
   case 'i':
   case 'I':
      glLoadIdentity();
      gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
      glutPostRedisplay();
      break;
   case 27:
      exit(0);
      break;
   }
}

int main(int argc, char **argv)
{
   glutInitWindowSize(200, 200);
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutCreateWindow(argv[0]);
   init();
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}
*/
