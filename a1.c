#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>

int startX, startY, endX, endY;

void drawPoint(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawBresenhamsLine(int x0, int y0, int x1, int y1) {
    int deltaX = abs(x1 - x0);
    int deltaY = abs(y1 - y0);
    int stepX = (x1 > x0) ? 1 : -1;
    int stepY = (y1 > y0) ? 1 : -1;

    int error = deltaX - deltaY;

    while (1) {
        drawPoint(x0, y0);
        if (x0 == x1 && y0 == y1) break;

        int error2 = 2 * error;

        if (error2 > -deltaY) {
            error -= deltaY;
            x0 += stepX;
        }

        if (error2 < deltaX) {
            error += deltaX;
            y0 += stepY;
        }
    }
}

void renderDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawBresenhamsLine(startX, startY, endX, endY);

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
    glutCreateWindow("Bresenham's Line Drawing");

    initialize();
    glutDisplayFunc(renderDisplay);
    glutMainLoop();

    return 0;
}