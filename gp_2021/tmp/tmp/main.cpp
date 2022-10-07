
// GLUTのwarningが出ないようする
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

float rotation1 = 0.0;
float rotation2 = 0.0;

void reshape(int width, int height){
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width/height, 0.1, 100.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,2.0,13.0, 0.0,0.0,0.0, 0.0,1.0,0.0);
    
}

void setup(){
    float lightPosition[4] = {5.25, 2.0, 0.25, 1.0};
    float ambient[4] = {0.3, 0.5, 0.0, 1.0};
    float diffuse[4] = {1.0, 1.0, 0.0, 1.0};
    float specular[4] = {1.0, 1.0, 1.0, 1.0};
    float shininess[1] = {20.0};
    
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

void display(){
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    int x = 1;
    int y = 1;
    int z = 5;
    
    glPushMatrix();
    glRotatef(rotation1, 0.0,1.0,0.0);
    
    //glutWireCube(1.0);
    
    
    glPushMatrix();
    glTranslatef(-(float)(x-1)/2.0,-(float)(y-1)/2.0, -(float)(z-1)/2.0);
    
    for(int k=0; k<z; k++){

        for(int j=0; j<y; j++){
            glutSolidCube(3.0);
            for(int i=0; i<x; i++){
                glPushMatrix();
                glTranslatef(i, j, z);
                glRotatef(rotation1,rotation2,rotation1,rotation2);
                glutWireCube(0.5);
                glPopMatrix();
            }
        }
    }
    
    glPopMatrix();
    
    glPopMatrix();
    
    glutSwapBuffers();
}


void idle(){
    //rotation = rotation + 1;
    rotation1++;
    rotation2 = rotation2 + 10;
    glutPostRedisplay();
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow("forCubes");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    
    setup();
    
    glutMainLoop();
    
    return 0;
}
