#include <GLUT/glut.h>
#include <stdio.h>
#include <math.h>

float startX,startY,endX,endY,transX,transY,angle,scaleX,scaleY;
#define pi 3.14159265358979323846

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0f, 0.0f);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-800,800,-450,450);
}


void myDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(-800,0); glVertex2i(800,0);
    glVertex2i(0,-450); glVertex2i(0,450);
    glEnd();

    glLineWidth(1.0);
    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_LINES);
    glVertex2i(startX,startY); glVertex2i(endX,endY);
    glEnd();
   
   
    float P1[2][1] = {{startX},{startY}};
    float P2[2][1] = {{endX},{endY}};
    
    
    float S[2][2] = {{scaleX,0},{0,scaleY}};
    float P1s[2][1] = {{S[0][0]*P1[0][0]+S[0][1]*P1[1][0]},{S[1][0]*P1[0][0]+S[1][1]*P1[1][0]}};
    float P2s[2][1] = {{S[0][0]*P2[0][0]+S[0][1]*P2[1][0]},{S[1][0]*P2[0][0]+S[1][1]*P2[1][0]}};
   
    glColor3f(1.0, 0.0, 0.0);

    glLineWidth(3.0);
    glBegin(GL_LINES);
   
    glVertex2i(P1s[0][0],P1s[1][0]); glVertex2i(P2s[0][0],P2s[1][0]);
   
    glEnd();
    
    
    float T[2][1] = {{transX},{transY}};
   
    float P1t[2][1] = {{P1s[0][0]+T[0][0]},{P1s[1][0]+T[1][0]}};
    float P2t[2][1] = {{P2s[0][0]+T[0][0]},{P2s[1][0]+T[1][0]}};
   
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
   
    glVertex2i(P1t[0][0],P1t[1][0]); glVertex2i(P2t[0][0],P2t[1][0]);
   
    glEnd();    
   
    float a_rad = angle * (pi / 180.0);

    float A[2][2] = {{cos(a_rad),-sin(a_rad)},{sin(a_rad),cos(a_rad)}};
   
    float P1a[2][1] = {
        {(A[0][0]*P1t[0][0]) + (A[0][1]*P1t[1][0])},
        {(A[1][0]*P1t[0][0]) + (A[1][1]*P1t[1][0])}
    };
    float P2a[2][1] = {
        {(A[0][0]*P2t[0][0]) + (A[0][1]*P2t[1][0])},
        {(A[1][0]*P2t[0][0]) + (A[1][1]*P2t[1][0])}
    };
   
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
   
    glVertex2i(P1a[0][0],P1a[1][0]); glVertex2i(P2a[0][0],P2a[1][0]);
   
    glEnd();
   
    glFlush();
}

void main(int argc, char **argv) {
    printf("Enter start point (x1 y1): ");
    scanf("%f %f", &startX, &startY);
    printf("Enter end point (x2 y2): ");
    scanf("%f %f", &endX, &endY);
    printf("Enter translation (tx ty): ");
    scanf("%f %f", &transX, &transY);
    printf("Enter rotation angle (degrees): ");
    scanf("%f", &angle);
    printf("Enter scaling factors (sx sy): ");
    scanf("%f %f", &scaleX, &scaleY);
    if(transX>150 || transY<50 || transY>150 || transX<50 || angle<10 || angle>80 || scaleX<0.2 || scaleY<0.2 || scaleX> 3.0 || scaleY>3.0) {
        printf("Enter the values in given range!!!");
        return;
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1600,900);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("Line Transformation");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
}