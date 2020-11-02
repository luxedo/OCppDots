#include <GL/glut.h>

#include "OCDots.h"
#include <iostream>

void loop(int);
void draw(void);
void init(void);

std::vector<Dot> dots = {
        Dot(150, 230, 0, 0),
        Dot(130, 50, 0, 0),
        Dot(160, 140, 0, 0),
        Dot(140, 60, 0, 0),
        Dot(140, 160, 0, 0),
};
std::vector<Vector> polygon = {
        Vector(150, 0),
        Vector(0, 300),
        Vector(300, 300),
        Vector(150, 0)};
OCDots ds{};

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Points");
    glutDisplayFunc(draw);
    glutTimerFunc(1000 / 60, loop, 0);
    init();
    glutMainLoop();

    return 0;
}

void update() {
    dots = ds.movePoints(dots, polygon);
}

void loop(int) {
    update();
    // draw();
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, loop, 0);
}

void draw(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    for (unsigned int i = 1; i < polygon.size(); i++) {
        glVertex2f(polygon[i].x, polygon[i].y);
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0.0, 0.0, 0.0);
    for (unsigned int i = 0; i < dots.size(); i++) {
        glVertex2f(dots[i].p.x, dots[i].p.y);
    }
    glEnd();
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(0.0, 1.0, 0.0);
    glPointSize(10.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 300.0, 0.0, 300.0);
}
