#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <glm/glm.hpp>

using namespace glm;

const float PI = 3.14159265359;

float anglex = 0.0;
float angley = 0.0;
float anglez = 0.0;

int Z = 0,Y = 0,X = 0;

bool TRIANGLE = false;
bool QUADRADO = false;
bool PENTAGONO = false;


bool TRANSLACAO = false;
bool ROTACAO = false;
bool SCALA = false;
bool CISALHAMENTO = false;
bool REFLEXAO = false;

class Triangle{

    public:
        vec3 a, b, c;

        Triangle(vec3 a, vec3 b, vec3 c);
};


Triangle::Triangle(vec3 a, vec3 b, vec3 c){
   this->a = a;
   this->b = b;
   this->c = c;
}


class Pentagon{

    public:
        vec3 a, b, c, d, e;

        Pentagon(vec3 a, vec3 b, vec3 c, vec3 d, vec3 e);
};


Pentagon::Pentagon(vec3 a, vec3 b, vec3 c, vec3 d, vec3 e){
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    this->e = e;
}

class Square{

    public:
        vec3 a, b, c, d;

        Square(vec3 a, vec3 b, vec3 c, vec3 d);
};


Square::Square(vec3 a, vec3 b, vec3 c, vec3 d){
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}


class Cube{

    public:
        vec3 a[4], b[4], c[4], d[4], e[4], f[4];

        Cube(vec3 a[], vec3 b[], vec3 c[], vec3 d[], vec3 e[], vec3 f[]);
};


Cube::Cube(vec3 a[], vec3 b[], vec3 c[], vec3 d[], vec3 e[], vec3 f[]){

    for(int i =0; i< 4; i++){
        this->a[i] = a[i];
        this->b[i] = b[i];
        this->c[i] = c[i];
        this->d[i] = d[i];
        this->e[i] = e[i];
        this->f[i] = f[i];
    }
}


void rotatingObject(){
    mat4 R = mat4(1.0);

     if(X){
         /*Rotacao no eixo x*/
         R[1] = vec4(0.0, cos(-anglex*PI/180), -sin(-anglex*PI/180), 0.0);
         R[2] = vec4(0.0, sin(-anglex*PI/180), cos(-anglex*PI/180), 0.0);
     }

     if(Y){
         /*Rotacao no eixo y*/
         R[0] = vec4(cos(-angley*PI/180), 0.0, sin(-angley*PI/180), 0.0);
         R[2] = vec4(-sin(-angley*PI/180), 0.0, cos(-angley*PI/180), 0.0);
     }

     if(Z){
         /* Rotacao no eixo Z*/
         R[0] = vec4(cos(-anglez*PI/180), -sin(-anglez*PI/180), 0, 0);
         R[1] = vec4(sin(-anglez*PI/180), cos(-anglez*PI/180), 0, 0);
}

     glMultMatrixf((GLfloat*) &R);

}

void trasnlateObject(){
    mat4 R = mat4(1.0);

    if(X)
        R[0] = vec4(1, 0, 0, anglex);
    else if(Y)
        R[1] = vec4(0, 1, 0, angley);

     glMultTransposeMatrixf((GLfloat*) &R);

}

void scale(){
    mat4 R = mat4(1.0);

    if(X){
        R[0] = vec4(anglex, 0, 0, 0);
        R[1] = vec4(0, 1, 0, 0);
        R[2] = vec4(0, 0, 1, 0);
    }
    if(Y){
        R[0] = vec4(1, 0, 0, 0);
        R[1] = vec4(0, angley, 0, 0);
        R[2] = vec4(0, 0, 1, 0);

    }

    if(Z){
        R[0] = vec4(1, 0, 0, 0);
        R[1] = vec4(0, 1, 0, 0);
        R[2] = vec4(0, 0, anglez, 0);

    }

    glMultMatrixf((GLfloat*) &R);

}

void shearing(){
 mat4 R = mat4(1.0);

    if(X){
        R[0] = vec4(-1,0  , 0, 0);
        R[1] = vec4(tan(anglex*PI/180), -1, 0, 0);
    }

    if(Y){
        R[0] = vec4(-1,tan(angley*PI/180)  , 0, 0);
        R[1] = vec4(0, -1, 0, 0);
    }

    glMultMatrixf((GLfloat*) &R);
}

void mirror(){
mat4 R = mat4(1.0);


        R[0] = vec4(-1,0  , 0, 0);

        R[1] = vec4(0,-1  , 0, 0);

    glMultMatrixf((GLfloat*) &R);
}

void drawTriangleShadow(){

    glBegin(GL_TRIANGLES);
        glColor3f(0.0, 0.0, 0.0);

        glVertex2f(2.0, -1.0);
        glVertex2f(3.0, 1.0);
        glVertex2f(4.0, -1.0);

    glEnd();

}

void drawTriangle(void){
    glPushMatrix();

    Triangle *t = new Triangle(vec3(-1.0, -1.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(1.0, -1.0, 0.0));

 //glMultTransposeMatrixf((GLfoat*) &Rz);

  if(ROTACAO) rotatingObject();

  if(TRANSLACAO) trasnlateObject();

  if(SCALA) scale();

  if(CISALHAMENTO) shearing();

  if(REFLEXAO) mirror();


   glBegin(GL_TRIANGLES);

        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(t->a.x, t->a.y);
        glVertex2f(t->b.x, t->b.y);
        glVertex2f(t->c.x, t->c.y);

    glEnd();
    glPopMatrix();


}


void drawPentagonShadow(){

    glBegin(GL_POLYGON);
        glColor3f(2, 0.0, 0.0);

        glVertex2f(0, 4.0);
        glVertex2f(-2.5, 0.0);
        glVertex2f(-1.5, -6.0);
        glVertex2f(1.5, -6);
        glVertex2f(2.5, 0.0);

    glEnd();

}

void drawPentagon(void){
    glPushMatrix();

    Pentagon *p = new Pentagon(vec3(0.0, 2.0, 0.0), vec3(-2.5, 0.0, 0.0), vec3(-1.5, -3.0, 0.0), vec3(1.5, -3.0, 0.0), vec3(2.5, 0.0, 0.0));

  if(ROTACAO) rotatingObject();

  if(TRANSLACAO) trasnlateObject();

  if(SCALA) scale();

  if(CISALHAMENTO) shearing();

  if(REFLEXAO) mirror();


    glBegin(GL_POLYGON);

        glColor3f(0.0, 0.0, 0.0);
        glVertex2f(p->a.x, p->a.y);
        glVertex2f(p->b.x, p->b.y);
        glVertex2f(p->c.x, p->c.y);
        glVertex2f(p->d.x, p->d.y);
        glVertex2f(p->e.x, p->e.y);

    glEnd();
    glPopMatrix();
}


void drawSquareShadow(){

    glBegin(GL_QUADS);

        glColor3f(0.0, 0.0, 1.0);

        glVertex2f(7.0, 1.0);
        glVertex2f(3.0, 1.0);
        glVertex2f(3.0, -1.0);
        glVertex2f(7.0, -1.0);

    glEnd();

}
void drawSquare(void){
  glPushMatrix();

  Square *s = new Square(vec3(2.0, 2.0, 0.0), vec3(-2.0, 2.0, 0.0), vec3(-2.0, -2.0, 0.0), vec3(2.0, -2.0, 0.0));

  if(ROTACAO) rotatingObject();

  if(TRANSLACAO) trasnlateObject();

  if(SCALA) scale();

  if(CISALHAMENTO) shearing();

  if(REFLEXAO) mirror();


    glBegin(GL_QUADS);
        glColor3f(0.0, 0.0, 0.0);
        glVertex2f(s->a.x, s->a.y);
        glVertex2f(s->b.x, s->b.y);
        glVertex2f(s->c.x, s->c.y);
        glVertex2f(s->d.x, s->d.y);

    glEnd();
    glPopMatrix();
}


void drawCube(void){
    glPushMatrix();

    glRotatef(230,1,1,1);

    glBegin(GL_QUADS);

    glColor3f(1, 2, 0);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
     glColor3f(0, 0, 0);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
     glColor3f(0, 0, 1);

    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
     glColor3f(0, 1, 0);

    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

     glColor3f(1, 1, 0);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

     glColor3f(1, 0, 1);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);


    glEnd();
    glPopMatrix();

}
void display(){

    glClear(GL_COLOR_BUFFER_BIT);

    if(TRIANGLE){
        drawTriangleShadow();
        drawTriangle();
    }

    if(PENTAGONO){
        drawPentagonShadow();
        drawPentagon();
    }

    if(QUADRADO){
        drawSquareShadow();
        drawSquare();
    }

    //drawCube();

    glFlush();
}

void init(){

    glClearColor(1.0, 1.0, 1.0, 1.0);

}

void reshape(int w, int h){


    glViewport(0, 0, (GLsizei)w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
  /*  if (h == 0) h = 1;
    if(w <= h)
    gluOrtho2D(00.f,250.0f, 0.0f,250.0f*h/w);
    else
    gluOrtho2D(0.0f,250.0f*h/w, 0.0f, 250.0f);
*/
    glOrtho(-10.0, 10.0, -10.0, 10.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*
void mouse(int button, int state, int x, int y){
    switch(button){

        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN)
                angle += 5;
            glutPostRedisplay();
        break;

        case GLUT_RIGHT_BUTTON:
            if(state == GLUT_DOWN)
                angle -= 5;
            glutPostRedisplay();
        break;

        default:
        break;
    }
}
*/
void keyboard(unsigned char key, int x, int y){

    switch(key){
        case 'X':
        case 'x':
                X = 1;
                Y = 0;
                Z = 0;
        break;

        case 'Y':
        case 'y':
                X = 0;
                Y = 1;
                Z = 0;
        break;

        case 'Z':
        case 'z':
                X = 0;
                Y = 0;
                Z = 1;
        break;

        case 't':
        case 'T':
            TRANSLACAO = true;
            ROTACAO = false;
            SCALA = false;
            CISALHAMENTO = false;
            REFLEXAO = false;
        break;

        case 'r':
        case 'R':
            TRANSLACAO = false;
            ROTACAO = true;
            SCALA = false;
            CISALHAMENTO = false;
            REFLEXAO = false;
        break;

        case 's':
        case 'S':
            TRANSLACAO = false;
            ROTACAO = false;
            SCALA = true;
            CISALHAMENTO = false;
            REFLEXAO = false;

        break;

        case 'c':
        case 'C':
            TRANSLACAO = false;
            ROTACAO = false;
            SCALA = false;
            CISALHAMENTO = true;
            REFLEXAO = false;

        break;

        case 'm':
        case 'M':
            TRANSLACAO = false;
            ROTACAO = false;
            SCALA = false;
            CISALHAMENTO = false;
            REFLEXAO = true;

        break;

    }




  //glutPostRedisplay();

}

void specialKey(int key, int x, int y){

    switch(key){
        case GLUT_KEY_LEFT:
            anglex += 1;

        break;

        case GLUT_KEY_RIGHT:
            anglex -= 1.0;

        break;

        case GLUT_KEY_DOWN:
            angley -= 1.0;

        break;

        case GLUT_KEY_UP:
            angley += 1.0;

        break;

        case GLUT_KEY_HOME:
            anglez += 1;
        break;

        case GLUT_KEY_F8:
            QUADRADO = true;
            TRIANGLE = false;
            PENTAGONO = false;
            anglex = 0.0;
            angley = 0.0;
            anglez = 0.0;

        break;


        case GLUT_KEY_F9:
            QUADRADO = false;
            TRIANGLE = true;
            PENTAGONO = false;
            anglex = 0.0;
            angley = 0.0;
            anglez = 0.0;

        break;


        case GLUT_KEY_F10:
            QUADRADO = false;
            TRIANGLE = false;
            PENTAGONO = true;
            anglex = 0.0;
            angley = 0.0;
            anglez = 0.0;

        break;



    }

   glutPostRedisplay();

}




int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(720, 680);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Puzzle");
    glutPositionWindow(100, 100);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
//    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);


    glutMainLoop();


    return 0;

}

