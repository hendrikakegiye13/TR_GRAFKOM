#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

#define FPS 120
#define TO_RADIANS 3.14/180.0

//  Anggota Kelompok 7
//  Hendrika .N Kegiye (672018500)
//  Juan Permana (672019064)
//  Ruth Melanesia Wanimbo (672018500)
//  Trivandi M Allow (672018107)

const int width = 1280;
const int height = 720;
int i;
float sudut;
double x_geser, y_geser, z_geser;

float pitch = 0.0, yaw = 0.0;
float camX = 0.0, camZ = 0.0, terbang = 25.0;

void display();
void reshape(int w, int h);
void timer(int);
void passive_motion(int, int);
void camera();
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);

struct Motion {
    bool Forward, Backward, Left, Right, Naik, Turun;
};
Motion motion = { false,false,false,false,false,false };

void init() {
    glClearColor(0.529, 0.807, 0.921, 0.0);
    glutSetCursor(GLUT_CURSOR_NONE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    glutWarpPointer(width / 2, height / 2);
}

void ground() {
    glBegin(GL_QUADS);
    glColor3f(0.19, 0.19, 0.19);
    glVertex3f(-1000.0, 0, -1000.0);

    glColor3f(0.38, 0.38, 0.38);
    glVertex3f(1000.0, 0, -1000.0);

    glColor3f(0.19, 0.19, 0.19);
    glVertex3f(1000.0, 0, 1000.0);

    glColor3f(0.38, 0.38, 0.38);
    glVertex3f(-1000.0, 0, 1000.0);
    glEnd();
}
void draw() {
    //halaman kuil
    glPushMatrix();
    glTranslatef(0, -250, 0);
    glutSolidCube(700.0);
    glPopMatrix();

    //tangga 1
    glPushMatrix();
    glTranslatef(0, 40, 330);
    glColor3f(0.32, 0.32, 0.32);
    glutSolidCube(100.0);
    glPopMatrix();
    //tangga 2
    glPushMatrix();
    glTranslatef(0, 30, 360);
    glColor3f(0.31, 0.31, 0.31);
    glutSolidCube(100.0);
    glPopMatrix();
    //tangga 3
    glPushMatrix();
    glTranslatef(0, 10, 390);
    glColor3f(0.30, 0.30, 0.30);
    glutSolidCube(100.0);
    glPopMatrix();
    //tangga 4
    glPushMatrix();
    glTranslatef(0, -10, 420);
    glColor3f(0.29, 0.29, 0.29);
    glutSolidCube(100.0);
    glPopMatrix();
    //tangga 5
    glPushMatrix();
    glTranslatef(0, -30, 450);
    glColor3f(0.28, 0.28, 0.28);
    glutSolidCube(100.0);
    glPopMatrix();

    //pojok tiang depan
    glPushMatrix();
    glTranslatef(-330, 160, 330);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 60.0f, 32, 32);
    glPopMatrix();
    //tengah tiang depan 1-2
    glPushMatrix();
    glTranslatef(-80, 160, 330);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 60.0f, 32, 32);
    glPopMatrix();
    //tengah tiang depan 1-2
    glPushMatrix();
    glTranslatef(-190, 160, 330);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 60.0f, 32, 32);
    glPopMatrix();
    //tengah tiang depan 1-3
    glPushMatrix();
    glTranslatef(80, 160, 330);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 60.0f, 32, 32);
    glPopMatrix();
    //tengah tiang depan 1-3
    glPushMatrix();
    glTranslatef(190, 160, 330);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 60.0f, 32, 32);
    glPopMatrix();
    //pojok tiang depan 1.4
    glPushMatrix();
    glTranslatef(330, 160, 330);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 60.0f, 32, 32);
    glPopMatrix();
    //pojok tiang kiri 2.1
    glPushMatrix();
    glTranslatef(-330, 160, -330);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 60.0f, 32, 32);
    glPopMatrix();
    //tengah tiang kiri 2-2
    glPushMatrix();
    glTranslatef(-330, 160, 200);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 60.0f, 32, 32);
    glPopMatrix();
    //tengah tiang kiri 2-3
    glPushMatrix();
    glTranslatef(-330, 160, 70);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 60.0f, 32, 32);
    glPopMatrix();
    //tengah tiang kiri 2-4
    glPushMatrix();
    glTranslatef(-330, 160, -60);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 60.0f, 32, 32);
    glPopMatrix();
    //tengah tiang kiri 2-5
    glPushMatrix();
    glTranslatef(-330, 160, -190);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 60.0f, 32, 32);
    glPopMatrix();
    //pojok kanan blkg 3.1
    glPushMatrix();
    glTranslatef(330, 160, -330);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 60.0f, 32, 32);
    glPopMatrix();
    //tengah tiang blkg 3.2
    glPushMatrix();
    glTranslatef(-200, 160, -330);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 60.0f, 32, 32);
    glPopMatrix();
    //tengah tiang blkg 3.3
    glPushMatrix();
    glTranslatef(-70, 160, -330);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 60.0f, 32, 32);
    glPopMatrix();
    //tengah tiang blkg 3.4
    glPushMatrix();
    glTranslatef(60, 160, -330);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 60.0f, 32, 32);
    glPopMatrix();
    //tengah tiang blkg 3.4
    glPushMatrix();
    glTranslatef(190, 160, -330);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 60.0f, 32, 32);
    glPopMatrix();
    //pojok tiang kanan 4.1
    glPushMatrix();
    glTranslatef(330, 160, 190);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 60.0f, 32, 32);
    glPopMatrix();
    //tengah tiang kanan 4.2
    glPushMatrix();
    glTranslatef(330, 160, 60);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 60.0f, 32, 32);
    glPopMatrix();
    //tengah tiang kanan 4.3
    glPushMatrix();
    glTranslatef(330, 160, -70);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 60.0f, 32, 32);
    glPopMatrix();
    //tengah tiang kanan 4.4
    glPushMatrix();
    glTranslatef(330, 160, -190);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 5.0f, 5.0f, 60.0f, 32, 32);
    glPopMatrix();
    //tengah datar tiang kiri 5-1
    glPushMatrix();
    glTranslatef(-330, 140, -330);
    glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 660.0f, 32, 32);
    glPopMatrix();
    //tengah datar tiang kiri 5-2
    glPushMatrix();
    glTranslatef(-330, 120, -330);
    glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 660.0f, 32, 32);
    glPopMatrix();
    //tengah datar tiang kanan 6-1
    glPushMatrix();
    glTranslatef(330, 140, -330);
    glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 660.0f, 32, 32);
    glPopMatrix();
    //tengah datar tiang kanan 6-2
    glPushMatrix();
    glTranslatef(330, 120, -330);
    glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 660.0f, 32, 32);
    glPopMatrix();
    //tengah datar tiang blakang 7-1
    glPushMatrix();
    glTranslatef(-330, 140, -330);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 660.0f, 32, 32);
    glPopMatrix();
    //tengah datar tiang blakang 7-2
    glPushMatrix();
    glTranslatef(-330, 120, -330);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 660.0f, 32, 32);
    glPopMatrix();
    //tengah datar tiang depan 8-1
    glPushMatrix();
    glTranslatef(80, 140, 330);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 250.0f, 32, 32);
    glPopMatrix();
    //tengah datar tiang depan 8-2
    glPushMatrix();
    glTranslatef(80, 120, 330);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 250.0f, 32, 32);
    glPopMatrix();
    //tengah datar tiang depan 8-3
    glPushMatrix();
    glTranslatef(-330, 140, 330);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 250.0f, 32, 32);
    glPopMatrix();
    //tengah datar tiang depan 8-3
    glPushMatrix();
    glTranslatef(-330, 120, 330);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glColor3f(0.18, 0.19, 0.21);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 250.0f, 32, 32);
    glPopMatrix();
    //tiang lantai 1 kiri 1
    glPushMatrix();
    glTranslatef(-160, 200, -20);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 110.0f, 32, 32);
    glPopMatrix();
    //tiang lantai 1 kiri 2
    glPushMatrix();
    glTranslatef(-160, 200, 60);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 110.0f, 32, 32);
    glPopMatrix();
    //tiang lantai 1 kanan 1
    glPushMatrix();
    glTranslatef(160, 200, -20);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 110.0f, 32, 32);
    glPopMatrix();
    //tiang lantai 1 kanan 2
    glPushMatrix();
    glTranslatef(160, 200, 60);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 110.0f, 32, 32);
    glPopMatrix();
    //tiang lantai 1 depan 1
    glPushMatrix();
    glTranslatef(-40, 200, 180);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 110.0f, 32, 32);
    glPopMatrix();
    //tiang lantai 1 depan 2
    glPushMatrix();
    glTranslatef(40, 200, 180);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 110.0f, 32, 32);
    glPopMatrix();
    //tiang lantai 1 belakang 1
    glPushMatrix();
    glTranslatef(-40, 200, -140);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 110.0f, 32, 32);
    glPopMatrix();
    //tiang lantai 1 belakang 2
    glPushMatrix();
    glTranslatef(40, 200, -140);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 110.0f, 32, 32);
    glPopMatrix();
    //tiang lantai 2 depan 1
    glPushMatrix();
    glTranslatef(30, 350, 150);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.92, 0.37, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 150.0f, 32, 32);
    glPopMatrix();
    //tiang lantai 2 depan 2
    glPushMatrix();
    glTranslatef(-30, 350, 150);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.92, 0.37, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 150.0f, 32, 32);
    glPopMatrix();
    //tiang lantai 2 kanan 1
    glPushMatrix();
    glTranslatef(120, 350, -10);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 150.0f, 32, 32);
    glPopMatrix();
    //tiang lantai 2 kanan 2
    glPushMatrix();
    glTranslatef(120, 350, 50);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 150.0f, 32, 32);
    glPopMatrix();
    //pagar pojok 1 lantai 2
    glPushMatrix();
    glTranslatef(160, 230, 180);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 30.0f, 32, 32);
    glPopMatrix();
    //pagar tengah 1 lt 2
    glPushMatrix();
    glTranslatef(0, 230, 180);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 30.0f, 32, 32);
    glPopMatrix();
    //pagar tengah 1-1 lt 2
    glPushMatrix();
    glTranslatef(80, 230, 180);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 30.0f, 32, 32);
    glPopMatrix();
    //pagar tengah 1-2 lt 2
    glPushMatrix();
    glTranslatef(-80, 230, 180);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 30.0f, 32, 32);
    glPopMatrix();
    //tengah datar 1-4 lt 2
    glPushMatrix();
    glTranslatef(-160, 230, 180);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 2.5f, 2.5f, 322.0f, 32, 32);
    glPopMatrix();
    //pagar pojok 2 lantai 2
    glPushMatrix();
    glTranslatef(-160, 230, 180);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 30.0f, 32, 32);
    glPopMatrix();
    //pagar tengah 2 lantai 2
    glPushMatrix();
    glTranslatef(-160, 230, 90);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 30.0f, 32, 32);
    glPopMatrix();
    //pagar tengah 2.1 lantai 2
    glPushMatrix();
    glTranslatef(-160, 230, -60);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 30.0f, 32, 32);
    glPopMatrix();
    //pagar tengah 2-2 lantai 2
    glPushMatrix();
    glTranslatef(-160, 230, 20);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 30.0f, 32, 32);
    glPopMatrix();
    //tengah datar 2-4 lantai 2
    glPushMatrix();
    glTranslatef(-160, 230, -140);
    glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 2.5f, 2.5f, 322.0f, 32, 32);
    glPopMatrix();
    //pagar pojok 3 lantai 2
    glPushMatrix();
    glTranslatef(-160, 230, -140);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 30.0f, 32, 32);
    glPopMatrix();
    //pagar tengah 3 lantai 2
    glPushMatrix();
    glTranslatef(0, 230, -140);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 30.0f, 32, 32);
    glPopMatrix();
    //pagar tengah 3-1 lantai 2
    glPushMatrix();
    glTranslatef(-80, 230, -140);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 30.0f, 32, 32);
    glPopMatrix();
    //pagar tengah 3-1 lantai 2
    glPushMatrix();
    glTranslatef(80, 230, -140);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 30.0f, 32, 32);
    glPopMatrix();
    //pagar pojok 3 lantai 2
    glPushMatrix();
    glTranslatef(160, 230, -140);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 30.0f, 32, 32);
    glPopMatrix();
    //tengah datar 3-3 lantai 2
    glPushMatrix();
    glTranslatef(-160, 230, -140);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 2.5f, 2.5f, 322.0f, 32, 32);
    glPopMatrix();
    //tengah datar 3-4 lantai 2
    glPushMatrix();
    glTranslatef(160, 230, -140);
    glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 2.5f, 2.5f, 322.0f, 32, 32);
    glPopMatrix();
    //pagar tengah 4 lantai 2
    glPushMatrix();
    glTranslatef(160, 230, 20);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 30.0f, 32, 32);
    glPopMatrix();
    //pagar tengah 4-1 lantai 2
    glPushMatrix();
    glTranslatef(160, 230, 100);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 30.0f, 32, 32);
    glPopMatrix();
    //pagar tengah 4-2 lantai 2
    glPushMatrix();
    glTranslatef(160, 230, 10);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1, 0.35, 0);
    gluCylinder(gluNewQuadric(), 3.0f, 3.0f, 30.0f, 32, 32);
    glPopMatrix();
    //dinding lantai 1 belakang
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1, 0.35, 0);
    glTranslatef(0, 150, -110);
    glRotatef(0, 0, 1, 0);
    glScalef(51, 20, 1);
    glutSolidCube(5);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    //dinding lantai 1 kiri
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.86, 0.3, 0);
    glTranslatef(-130, 150, 20);
    glRotatef(90, 0, 1, 0);
    glScalef(51, 20, 1);
    glutSolidCube(5);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    //dinding lantai 1 kanan
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.86, 0.3, 0);
    glTranslatef(130, 150, 20);
    glRotatef(90, 0, 1, 0);
    glScalef(51, 20, 1);
    glutSolidCube(5);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    //dinding lantai 1 depan
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1, 0.30, 0);
    glTranslatef(0, 150, 150);
    glRotatef(0, 0, 1, 0);
    glScalef(51, 20, 1);
    glutSolidCube(5);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();

    //pintu lt 1
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(5, 0.20, 0);
    glTranslatef(0, 140, 160);
    glRotatef(0, 0, 1, 0);
    glScalef(50, 40, 0);
    glutSolidCube(2);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    //line pintu
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.17, 0.12, 0.09);
    glTranslatef(0, 140, 161);
    glRotatef(0, 0, 1, 0);
    glScalef(2, 80, 0);
    glutSolidCube(1);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    
    //lantai 1 atas
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.82, 0.82, 0.82);
    glTranslatef(0, 200, 20);
    glRotatef(90, 1, 0, 0);
    glScalef(170, 170, 3);
    glutSolidCube(2);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    //dinding lantai 2 belakang
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1, 0.30, 0);
    glTranslatef(0, 270, -80);
    glRotatef(0, 0, 1, 0);
    glScalef(35, 30, 1);
    glutSolidCube(5);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    //dinding lantai 2 kiri
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.89, 0.3, 0);
    glTranslatef(-90, 270, 20);
    glRotatef(90, 0, 1, 0);
    glScalef(40, 30, 1);
    glutSolidCube(5);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    //dinding lantai 2 kanan
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.89, 0.3, 0);
    glTranslatef(90, 270, 20);
    glRotatef(90, 0, 1, 0);
    glScalef(40, 30, 1);
    glutSolidCube(5);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    //dinding lantai 2 depan
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1, 0.30, 0);
    glTranslatef(0, 270, 120);
    glRotatef(0, 0, 1, 0);
    glScalef(35, 30, 1);
    glutSolidCube(5);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    //lantai 2 atas
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.22, 0.47, 0.21);
    glTranslatef(0, 350, 20);
    glRotatef(90, 1, 0, 0);
    glScalef(130, 140, 3);
    glutSolidCube(2);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    //dinding lantai 3 belakang
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1, 0.30, 0);
    glTranslatef(0, 410, -50);
    glRotatef(0, 0, 1, 0);
    glScalef(25, 25, 1);
    glutSolidCube(5);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    //dinding lantai 3 depan
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1, 0.30, 0);
    glTranslatef(0, 410, 90);
    glRotatef(0, 0, 1, 0);
    glScalef(25, 25, 1);
    glutSolidCube(5);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    //dinding lantai 3 kiri
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.89, 0.3, 0);
    glTranslatef(-60, 410, 20);
    glRotatef(90, 0, 1, 0);
    glScalef(27, 25, 1);
    glutSolidCube(5);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    //dinding lantai 3 kanan
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.89, 0.3, 0);
    glTranslatef(60, 410, 20);
    glRotatef(90, 0, 1, 0);
    glScalef(27, 25, 1);
    glutSolidCube(5);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    //lantai 3 atas
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.22, 0.47, 0.21);
    glTranslatef(0, 470, 20);
    glRotatef(-85, 1, 0, 0);
    glScalef(100, 110, 3);
    glutSolidCone(2, 20, 4, 50);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    //dinding lantai 4 belakang
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1, 0.30, 0);
    glTranslatef(0, 510, -20);
    glRotatef(0, 0, 1, 0);
    glScalef(20, 15, 1);
    glutSolidCube(5);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    //dinding lantai 4 depan
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1, 0.30, 0);
    glTranslatef(0, 510, 60);
    glRotatef(0, 0, 1, 0);
    glScalef(20, 15, 1);
    glutSolidCube(5);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    //dinding lantai 4 kiri
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.89, 0.3, 0);
    glTranslatef(-50, 510, 20);
    glRotatef(90, 0, 1, 0);
    glScalef(15, 15, 1);
    glutSolidCube(5);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    //dinding lantai 4 kanan
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.89, 0.3, 0);
    glTranslatef(50, 510, 20);
    glRotatef(90, 0, 1, 0);
    glScalef(15, 15, 1);
    glutSolidCube(5);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    //lantai 4 atas
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.22, 0.47, 0.21);
    glTranslatef(0, 550, 20);
    glRotatef(-85, 1, 0, 0);
    glScalef(55, 45, 3);
    glutSolidCone(2, 20, 4,50);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    ground();
    cout << "X_GESER = " << x_geser << " Y_GESER =       " << y_geser << " Z_GESER =         " << z_geser << endl;
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    camera();
    draw();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 16.0 / 9.0, 2, 10000);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int) {
    glutPostRedisplay();
    glutWarpPointer(width / 2, height / 2);
    glutTimerFunc(1000 / FPS, timer, 0);
}

void passive_motion(int x, int y) {
    int dev_x, dev_y;
    dev_x = (width / 2) - x;
    dev_y = (height / 2) - y;
    yaw += (float)dev_x / 20.0;
    pitch += (float)dev_y / 20.0;
}

void camera() {
    if (motion.Forward) {
        camX += cos((yaw + 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90) * TO_RADIANS) * 2;
    }
    if (motion.Backward) {
        camX += cos((yaw + 90 + 180) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 + 180) * TO_RADIANS) * 2;
    }
    if (motion.Left) {
        camX += cos((yaw + 90 + 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 + 90) * TO_RADIANS) * 2;
    }
    if (motion.Right) {
        camX += cos((yaw + 90 - 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 - 90) * TO_RADIANS) * 2;
    }
    if (motion.Naik) {
        terbang -= 2.0;
    }
    if (motion.Turun) {
        terbang += 2.0;
    }

    if (pitch >= 70)
        pitch = 70;
    if (pitch <= -90)
        pitch = -90;


    glRotatef(-pitch, 1.0, 0.0, 0.0);
    glRotatef(-yaw, 0.0, 1.0, 0.0);

    glTranslatef(-camX, -terbang, -350 - camZ);
    if (terbang < 25)
        terbang = 24;
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'W':
    case 'w':
        motion.Forward = true;
        break;
    case 'A':
    case 'a':
        motion.Left = true;
        break;
    case 'S':
    case 's':
        motion.Backward = true;
        break;
    case 'D':
    case 'd':
        motion.Right = true;
        break;
    case 'E':
    case 'e':
        motion.Naik = true;
        break;
    case 'Q':
    case 'q':
        motion.Turun = true;
        break;
    case '6':
        x_geser += 10.0;
        break;
    case '4':
        x_geser -= 10.0;
        break;
    case '8':
        y_geser += 10.0;
        break;
    case '2':
        y_geser -= 10.0;
        break;
    case '9':
        z_geser -= 10.0;
        break;
    case '1':
        z_geser += 10.0;
        break;
    case '`': // KELUAR DARI PROGRAM
        exit(1);
    }
}

void keyboard_up(unsigned char key, int x, int y) {
    switch (key) {
    case 'W':
    case 'w':
        motion.Forward = false;
        break;
    case 'A':
    case 'a':
        motion.Left = false;
        break;
    case 'S':
    case 's':
        motion.Backward = false;
        break;
    case 'D':
    case 'd':
        motion.Right = false;
        break;
    case 'E':
    case 'e':
        motion.Naik = false;
        break;
    case 'Q':
    case 'q':
        motion.Turun = false;
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("TR GRAFKOM KELOMPOK 7 ");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(passive_motion);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);

    glutMainLoop();
    return 0;
}