//
//  main.cpp
//  helloGL
//
//  Created by TomoHirata on 2021/04/27.
//  My first OpenGL Code.

#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

void display(){
    glClearColor(0.0, 0.0, 0.0, 0.0);   //set background color
    glClear(GL_COLOR_BUFFER_BIT);       //setup background
    
    //1st Rectangle
    glBegin(GL_POLYGON);
        glColor3f(0.0, 0.5, 1.0);
        glVertex2f(0.5, 0.5);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(0.5, -0.5);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(-0.5, -0.5);
        glColor3f(0.0, 1.0, 1.0);
        glVertex2f(-0.5, 0.5);
    glEnd();
    
    //2nd Rectangle
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(1.0, 1.0);
        glVertex2f(1.0, 0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(0.5, 1.0);
    glEnd();
    
    //3nd Rectangle
    glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(-1.0, 1.0);
        glVertex2f(-1.0, 0.5);
        glVertex2f(-0.5, 0.5);
        glVertex2f(-0.5, 1.0);
    glEnd();
    
    //4nd Rectangle
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(-1.0, -1.0);
        glVertex2f(-1.0, -0.5);
        glVertex2f(-0.5, -0.5);
        glVertex2f(-0.5, -1.0);
    glEnd();
    
    //5nd Recangle
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(1.0, -1.0);
        glVertex2f(1.0, -0.5);
        glVertex2f(0.5, -0.5);
        glVertex2f(0.5, -1.0);
    glEnd();

    
    glFlush();
}

int main(int argc, char ** argv) {
    glutInit(&argc, argv);              //Initialize glut
    glutInitDisplayMode(GLUT_SINGLE);   //single buffer
    glutInitWindowSize(500, 500);       //set window width and height
    glutCreateWindow("Hello OpenGL");
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
