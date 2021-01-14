#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include <GL/glut.h>
#include <Windows.h>
#include "RGBA.h"

float xx = 0, yy=0;

RGBApixmap pix[6];
void myInit(void)
{
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_EQUAL,1.0); // accept fragment if fragment alpha = reference alpha i.e. 1.0
    //or glAlphaFunc(GL_NOTEQUAL,0.0);// accept fragment if fragment alpha not= reference alpha i.e. 1.0
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

int ortho_r = 320, ortho_t=240, ortho_b=-240, ortho_l = -320;
int view_x=0,view_y=0;
int view_size_x=640, view_size_y=480;
void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(view_x,view_y,view_size_x,view_size_y);
    gluOrtho2D(ortho_l,ortho_r,ortho_b,ortho_t);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
    glBegin(GL_POLYGON);
    glTexCoord2f(0,0);
    glVertex2f(-320,-240);
    glTexCoord2f(1,0);
    glVertex2f(320,-240);
    glTexCoord2f(1,1);
    glVertex2f(320,240);
    glTexCoord2f(0,1);
    glVertex2f(-320,240);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glFlush();

}

void myKeyboard(unsigned char key, int x, int y)
{
    std :: cout << key <<std :: endl;
    if(key=='+')
    {
        ortho_l=ortho_l+40;
        ortho_r= ortho_r-40;
        ortho_t=ortho_t-30;
        ortho_b= ortho_b+30;
    }
    if(key=='-')
    {
        ortho_l=ortho_l-40;
        ortho_r= ortho_r+40;
        ortho_t=ortho_t+30;
        ortho_b= ortho_b-30;
    }
    if(key=='a')
    {
        ortho_l= ortho_l-30;
        ortho_r= ortho_r-30;
    }
    if(key=='s')
    {
        ortho_t= ortho_t-40;
        ortho_b= ortho_b-40;
    }
    if(key=='d')
    {
        ortho_l= ortho_l+30;
        ortho_r= ortho_r+30;
        //ortho_l = ortho_l+30;

    }
    if(key=='w')
    {
        ortho_t= ortho_t+40;
        ortho_b= ortho_b+40;
    }
    glutPostRedisplay();

}
int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Demo");
    myInit();
    pix[1].readBMPFile("C:/Users/Rafiq/Desktop/Semester6UBIT/ComputerGraphics/OpenGL/ZoomIn/room.bmp",1);
    pix[1].setTexture(2);
    glutDisplayFunc(display);
    glutKeyboardFunc(myKeyboard);


    glutMainLoop();

    return EXIT_SUCCESS;
}
