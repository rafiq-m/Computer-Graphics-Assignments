#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include<vector>
#include <Windows.h>
#include "RGBA.h"
#include <iostream>
#include <mmsystem.h>

using namespace std;

int lefted = 0;
int righted = 500;
int bottomed = 0 ;
int toped= 500;
int plane_shooted = 0;
GLfloat score = 0.5;
GLfloat plane_x = 0;
GLfloat plane_y = (toped-bottomed) / 2;
struct bullet
{
    GLfloat x = 0;
    GLfloat y = 0;
};
struct bullet example_bullet;
vector<struct bullet> bullets;
vector <struct bullet> ::iterator bullet_count;

struct blast
{
    GLfloat x = 0;
    GLfloat y = 0;
};
struct blast example_blast;
vector<struct blast> blasts;
vector <struct blast> ::iterator blast_count;

struct enemy
{
    GLfloat x = 0;
    GLfloat y = 0;
};
struct enemy example_enemy;
vector<struct enemy> enemies;
vector <struct enemy> ::iterator enemy_count;

RGBApixmap pix[6];

void drawBlast(int x, int y)
{
    example_blast.x = x;
    example_blast.y = y;
    blasts.push_back(example_blast);
}
void drawEnemy()
{
    example_enemy.x = righted;
    example_enemy.y = rand() % toped - pix[2].nRows + lefted + pix[2].nRows;
    enemies.push_back(example_enemy);
}

void drawBullet()
{
    int random = rand() % 2;
    if(random == 0)
    {
        example_bullet.x = plane_x;
        example_bullet.y = plane_y;
    }
    else
    {
        example_bullet.x = plane_x;
        example_bullet.y = plane_y+40;
    }
    bullets.push_back(example_bullet);
}

void display2(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    char c[] = "Game Over !";
    int point = 150;
    for(int i = 0 ; i < sizeof(c)/sizeof(c[0]) ; i++)
    {
        glRasterPos2f(point, 250);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
        point +=10 ;
    }
    glFlush();
   glutDisplayFunc(display2);
}

void myInit(void)
{
    glClearColor(0.3f,0.3f,0.4f,1.0f);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_EQUAL,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(lefted,righted,bottomed,toped);
    glViewport(lefted,bottomed,righted,toped);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPointSize(4);

}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2005);
    glBegin(GL_POLYGON);
    glTexCoord2f(0,0);
    glVertex2f(0,0);
    glTexCoord2f(1,0);
    glVertex2f(500,0);
    glTexCoord2f(1,1);
    glVertex2f(500,500);
    glTexCoord2f(0,1);
    glVertex2f(0, 500);
    glEnd();
    glDisable(GL_TEXTURE_2D);


   /* glBegin(GL_QUADS);          //For Printing Score
    glVertex2f(0,500);
    glVertex2f(50,500);
    glVertex2f(50,450);
    glVertex2f(0, 450);
    glEnd();*/


    //glRasterPos2f(20 , 480);
    //glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, plane_shooted);

    /*glBegin(GL_QUADS);
    glVertex2d(plane_x, plane_y);
    glVertex2d(plane_x + pix[0].nCols-35, plane_y);
    glVertex2d(plane_x + pix[0].nCols-35, plane_y + pix[0].nRows);
    glVertex2d(plane_x, plane_y + pix[0].nRows);
    glEnd();*/
    glRasterPos2d(plane_x, plane_y);
    pix[0].mDraw();         //my plane


    for(bullet_count = bullets.begin() ; bullet_count != bullets.end(); ++bullet_count)
    {
        glRasterPos2d(bullet_count->x, bullet_count->y);
        pix[1].mDraw();         //bullets
    }
    for(enemy_count = enemies.begin() ; enemy_count != enemies.end(); ++enemy_count)
    {
        /*glBegin(GL_QUADS);
        glVertex2d(enemy_count->x, enemy_count->y);
        glVertex2d(enemy_count->x + pix[2].nCols, enemy_count->y);
        glVertex2d(enemy_count->x + pix[2].nCols, enemy_count->y + pix[2].nRows);
        glVertex2d(enemy_count->x, enemy_count->y + pix[2].nRows);
        glEnd();*/





        glRasterPos2d(enemy_count->x, enemy_count->y);
        pix[2].mDraw();         //enemy plane
    }
    for(blast_count = blasts.begin() ; blast_count != blasts.end(); ++blast_count)
    {
        glRasterPos2d(blast_count->x, blast_count->y);
        pix[3].mDraw();         //blasts
    }
    glFlush();

    for(bullet_count = bullets.begin() ; bullet_count != bullets.end(); ++bullet_count)
    {
         for(enemy_count = enemies.begin() ; enemy_count != enemies.end(); ++enemy_count)
         {
            if((bullet_count->x + pix[1].nCols >= enemy_count->x) &&
                    (bullet_count->x <= enemy_count->x + pix[2].nCols) &&
                    (bullet_count->y + pix[1].nRows >= enemy_count->y) &&
                    (bullet_count->y <= enemy_count->y + pix[2].nRows))
            {
                PlaySound("C:/Users/Rafiq/Desktop/Semester6UBIT/ComputerGraphics/OpenGL/PlaneShooter/Sounds/Explosion.wav", NULL, SND_ASYNC|SND_FILENAME);
                drawBlast(enemy_count->x, enemy_count->y);
                plane_shooted++;
                score += 0.1;
                enemies.erase(enemy_count);
                break;
            }

            if((plane_x + pix[0].nCols-38 >= enemy_count->x) &&
                    (plane_x <= enemy_count->x + pix[2].nCols) &&
                    (plane_y + pix[0].nRows >= enemy_count->y) &&
                    (plane_y <= enemy_count->y + pix[2].nRows))
            {
                display2();
            }


            if(enemy_count->x < 0 )
            {
                display2();
            }
        }
    }

}





void blastTimer(int t)
{
    for(blast_count = blasts.begin() ; blast_count != blasts.end(); ++blast_count)
    {
        blast_count->y -= 4;
        blast_count->x += 0.5;
    }
    glutPostRedisplay();
    glutTimerFunc(50,blastTimer,t);
}

void myTimer(int t)
{
    for(bullet_count = bullets.begin() ; bullet_count != bullets.end(); ++bullet_count)
    {
        bullet_count->x += 5;
    }

    for(enemy_count = enemies.begin() ; enemy_count != enemies.end(); ++enemy_count)
    {
        enemy_count->x -=  score;
    }

    glutPostRedisplay();
    glutTimerFunc(10,myTimer,t);

}


void generateEnemies(int t)
{
    drawEnemy();
    //glutPostRedisplay();
    int time = rand() % 3000 + 2000;
    glutTimerFunc(time,generateEnemies,0);

}
void myKeyboard(unsigned char key, int x, int y)
{
    if(key=='w')
    {
        plane_y += 10;
        if(plane_y >= toped)
            plane_y = toped - 10;
    }
    if(key=='s')
    {
        plane_y -= 10;
        if(plane_y <= bottomed)
            plane_y = bottomed;
    }
    if(key=='d')
    {
        plane_x += 10;
        if(plane_x >= righted)
            plane_x = righted - 10;
    }
    if(key=='a')
    {
        plane_x -=10;
        if(plane_x <= lefted)
            plane_x = lefted;
    }
    if(key=='f')
    {

    }
    if(key==32)
    {
        drawBullet();
    }

    glutPostRedisplay();

}
int main(int argc, char **argv)
{

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1000, 640);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Rafiq-B17101061- Plane Shooter Game");
    myInit();

    pix[0].readBMPFile("C:/Users/Rafiq/Desktop/Semester6UBIT/ComputerGraphics/OpenGL/PlaneShooter/plane.bmp",1);
    pix[0].setChromaKey(255,255,255);
    pix[0].setTexture(2001);



    pix[1].readBMPFile("C:/Users/Rafiq/Desktop/Semester6UBIT/ComputerGraphics/OpenGL/PlaneShooter/bullet.bmp",1);
    pix[1].setChromaKey(255,255,255);
    pix[1].setTexture(2002);

    pix[2].readBMPFile("C:/Users/Rafiq/Desktop/Semester6UBIT/ComputerGraphics/OpenGL/PlaneShooter/enemy_plane.bmp",1);
    pix[2].setChromaKey(255,255,255);
    pix[2].setTexture(2002);

    pix[3].readBMPFile("C:/Users/Rafiq/Desktop/Semester6UBIT/ComputerGraphics/OpenGL/PlaneShooter/blast.bmp",1);
    pix[3].setChromaKey(255,255,255);
    pix[3].setTexture(2003);

    pix[5].readBMPFile("C:/Users/Rafiq/Desktop/Semester6UBIT/ComputerGraphics/OpenGL/PlaneShooter/background.bmp",1);
    pix[5].setChromaKey(255,255,255);
    pix[5].setTexture(2005);

    glutDisplayFunc(display);
    glutTimerFunc(500, blastTimer, 0);
    glutTimerFunc(2000, generateEnemies, 0);
    glutTimerFunc(10,myTimer,0);
    glutKeyboardFunc(myKeyboard);
    glutMainLoop();

    return EXIT_SUCCESS;
}


