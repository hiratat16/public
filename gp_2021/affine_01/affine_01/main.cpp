#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

int rotation = 0; // rotation angele for animation

//original function setting up light ang material
void setup(){
 //LIGHTING
 float lightPosition[4] = {5.25, 2.0, 0.25, 1.0};
 glEnable(GL_DEPTH_TEST);
 glEnable(GL_LIGHTING);
 glEnable(GL_LIGHT0);
 glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

 //MATERIAL
 float ambient[4] = {0.3, 0.5, 0.0, 1.0};
 float diffuse[4] = {1.0, 1.0, 0.3, 1.0};
 float specular[4] = {1.0, 1.0, 1.0, 1.0};
 float shininess[1] = {20.0f};
 glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
 glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
 glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
 glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}
void reshape(int width, int height){
 glViewport(0, 0, width, height);

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluPerspective(45.0, (double)width/height, 0.1, 100.0);

 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 gluLookAt(0.0, 3.0, 13.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 );
}

void idle(void){
    rotation++;
    if(rotation >= 360) rotation = 0;
    glutPostRedisplay();
}

void display(void){
 glEnable(GL_DEPTH_TEST);
 glClearColor(0.0, 0.0, 0.0, 1.0);
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 //1st teapot
 glutSolidCube(1);

 //2nd teapot
 glPushMatrix();
 glRotatef(rotation, 1.0, 0, 0); // x軸を中心に回転
 glTranslatef(3,0,0);
 glutSolidCube(1);
 glPopMatrix();
 //3rd teapot
 // glRotatef(rotation, 0, 1.0, 0); // x軸を中心に回転
 glPushMatrix();
 glRotatef(135.0, 0.0,1.0,0.0);
 glTranslatef(3,0,0);
 glutSolidCube(1);
 glPopMatrix();
 glutSwapBuffers(); //double buffer
}

int main(int argc, char * argv[]) {
 glutInit(&argc, argv);
 glutInitWindowSize(600, 600);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
 glutCreateWindow("affine transformation");
 glutDisplayFunc(display);
 glutReshapeFunc(reshape);
 glutIdleFunc(idle);
    
 setup();
    
 glutMainLoop();
 return 0;
}
