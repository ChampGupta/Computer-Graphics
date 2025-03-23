#include <GLUT/glut.h>
#include <stdio.h>

int xc = -200, yc = -200, r = 100;

void plotPoints(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);
    glEnd();
}

void drawCircle() {
    int x = 0, y = r;
    int d = 1 - r;
    plotPoints(x, y);
    
    while (x < y) {
        x++;
        if (d < 0)
            d += 2 * x + 1;
        else {
            y--;
            d += 2 * (x - y) + 1;
        }
        plotPoints(x, y);
    }
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCircle();
}

void init() {
    glClearColor(0, 0, 0, 1);
    glColor3f(1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -500, 500);
}

int main(int argc, char* argv) {
    printf("Enter center coordinates (xc, yc): ");
    scanf("%d %d", &xc, &yc);
    printf("Enter radius: ");
    scanf("%d", &r);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mid-Point Circle Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
