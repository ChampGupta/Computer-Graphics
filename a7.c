#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

int x, y, x1, y1, t1, t2, d1, d2, s;

void homogenousCoordinate(){
    
}

void renderDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    homogenousCoordinate();

    glFlush();
}

void initialize() {
    glClearColor(0.0, 0.0, 0.0, 1.0); 
    glColor3f(1.0, 1.0, 1.0);        
    glPointSize(4.0);                 
    gluOrtho2D(0.0, 640.0, 0.0, 480.0); 
}

int main(int argc, char** argv) {
    printf("Enter the starting point (x1, y1): ");
    scanf("%d %d", &startX, &startY);
    printf("Enter the ending point (x2, y2): ");
    scanf("%d %d", &endX, &endY);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Homogeneous Coordinates");

    initialize();
    glutDisplayFunc(renderDisplay);
    glutMainLoop();

    return 0;
}
