//  main.cpp
//  SolarSystem
//
//  Created by Ganesh Koripalli on 10/25/17.
//  Copyright © 2017 Ganesh Koripalli. All rights reserved.

//Headers for Visual Studio
//#include <iostream>
//#include "GL/glew.h"
//#include "GL/glut.h"

//Headers for Xcode
#include "OpenGL/gl.h"
#include "OpenGL/glu.h"
#include <GLUT/glut.h>
#include <iostream>

#define sunRadius 0.4
#define earthRadius 0.06
#define moonRadius 0.016

GLfloat rotationSpeed = 0.2; //Rotation of the earth and moon
GLfloat daysInYear = 365;
GLfloat year = 0.0;
GLfloat day = 0.0;
GLfloat moonAroundEarth = 0.0;
GLfloat moonItself = 0.0;
GLfloat earthOrbitRadius = 1.0;
GLfloat moonOrbitRadius = 0.1;
GLfloat moonAroundEarthRate = 2 * rotationSpeed;
GLfloat moonRotationItselfRate = 5.0 * rotationSpeed;
GLfloat dayRate = 5.0 * rotationSpeed;
GLfloat yearRate = daysInYear / 360.0 * dayRate * rotationSpeed;

void Initialization(void) {
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(10.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
}

void drawSolarSystem(void) {
    
    glPushMatrix();
    gluLookAt(0.0, 0.0, -4.0, 0.0, 0.0, 1.0, 0.0, -3.0, 0.0);
    glColor3f(1.0, 0.8, 0.3);
    glutSolidSphere(sunRadius, 50, 50);
    glPushMatrix();
    
    glRotatef(year, 0.0, 1.0, 0.0); //rotation for earth
    glTranslatef(earthOrbitRadius, 0.0, 0.0); //translation for earth
    glRotatef(-year, 0.0, 1.0, 0.0); //It is a state machine
    glPushMatrix();
    glRotatef(day, 0.25, 1.0, 0.0);
    glColor3f(0.4, 0.6, 0.3);
    glutSolidSphere(earthRadius, 10, 10); //Drawing the earth
    
    glPopMatrix(); //pop the current matrix stack
    glRotatef(moonAroundEarth, 0.0, 1.0, 0.0); //rotation for moon
    glTranslatef(moonOrbitRadius, 0.0, 0.0); //translation for moon
    glRotatef(-moonAroundEarth, 0.0, 1.0, 0.0); //around earth rotation
    glRotatef(moonItself, 0.0, 1.0, 0.0); //moon rotation about itself
    
    glColor3f(0.3, 0.3, 0.5); //draw the moon
    glutSolidSphere(moonRadius, 8, 8);
    glPopMatrix(); //pop the current matrix
    glPopMatrix(); //pop the current matrix
    
    //GlPushMatrix() has been pressed 3 times prior
    
}
void displayFunc(void) {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawSolarSystem();
    glFlush();
    glutSwapBuffers();
    
}

void idleFunc(void) {
    
    day += dayRate; //increase the days
    year += yearRate; //increase the year
    moonItself += moonRotationItselfRate;
    moonAroundEarth += moonAroundEarthRate; //increase the times moon rotated itself
    displayFunc();
    
}

void reshapeFunc(int x, int y) {
    
    if (y == 0 || x == 0) {
        
        return;
        
    }
    
    glLoadIdentity();
    gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, x, y);
    displayFunc();
    
}

int main(int argc, char* argv[]) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Solar System");
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_BUFFER_BIT);
    Initialization();
    glutReshapeFunc(reshapeFunc);
    glutIdleFunc(idleFunc);
    glutDisplayFunc(displayFunc);
    glutMainLoop();
    return 0;
    
}


