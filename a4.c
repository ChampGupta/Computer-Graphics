#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdio.h>

typedef struct {
    int x, y;
} Point;

#define MAX_VERTICES 10

Point vertices[MAX_VERTICES] = {
    {10, 50}, {30, 120}, {50, 50}, {80, 200}, {100, 50}, 
    {150, 100}, {180, 40}, {200, 30}, {250, 20}, {120, 10}
};

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void scanLineFill() {
    int i, j, k;
    int n = MAX_VERTICES;

    int ymin = vertices[0].y, ymax = vertices[0].y;
    for (i = 1; i < n; i++) {
        if (vertices[i].y < ymin) ymin = vertices[i].y;
        if (vertices[i].y > ymax) ymax = vertices[i].y;
    }

    int x_intersections[MAX_VERTICES];

    for (int y = ymin; y <= ymax; y++) {
        int count = 0;

        for (i = 0; i < n; i++) {
            int x1 = vertices[i].x, y1 = vertices[i].y;
            int x2 = vertices[(i + 1) % n].x, y2 = vertices[(i + 1) % n].y;

            if ((y1 <= y && y2 > y) || (y2 <= y && y1 > y)) {
                int x_intersect = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
                x_intersections[count++] = x_intersect;
            }
        }

        for (j = 0; j < count - 1; j++) {
            for (k = 0; k < count - j - 1; k++) {
                if (x_intersections[k] > x_intersections[k + 1]) {
                    swap(&x_intersections[k], &x_intersections[k + 1]);
                }
            }
        }

        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        for (j = 0; j < count; j += 2) {
            if (j + 1 < count) {
                glVertex2i(x_intersections[j], y);
                glVertex2i(x_intersections[j + 1], y);
            }
        }
        glEnd();
        glFlush();
    }
}

void drawPolygon() {
    glColor3f(0.0, 1.0, 0.0);       
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < MAX_VERTICES; i++) {
        glVertex2i(vertices[i].x, vertices[i].y);
    }
    glEnd();
    glFlush();
}

void myInit(void){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void myDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);
    drawPolygon();
    scanLineFill();
    glFlush();
}

void main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Scan-Line Polygon Fill Algorithm");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
}