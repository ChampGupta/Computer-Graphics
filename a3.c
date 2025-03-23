#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdio.h>
#include <math.h>

void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void plotPoints(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void midPointEllipse(int rx, int ry, int xc, int yc)
{
    int ask;
    printf("Enter 1 for custom input and 0 for default input: ");
    scanf("%d", &ask);
    if (ask == 1)
    {
        printf("Enter the value of rx, ry, xc, yc: ");
        scanf("%d %d %d %d", &rx, &ry, &xc, &yc);
    }
    else
    {
        printf("Default values are: rx = 400, ry = 200, xc = 100, yc = 100\n");
    }
    int x = 0, y = ry;

    // Region-1
    int p = pow(ry, 2) - pow(rx, 2) * ry + pow(rx, 2) * 0.25;
    int dx = 2 * pow(ry, 2) * x;
    int dy = 2 * pow(rx, 2) * y;
    do
    {
        plotPoints(xc + x, yc + y);
        plotPoints(xc + x, yc - y);
        plotPoints(xc - x, yc + y);
        plotPoints(xc - x, yc - y);
        if (p < 0)
        {
            x++;
            dx = dx + 2 * pow(ry, 2);
            p = p + dx + pow(ry, 2);
        }
        else
        {
            x++;
            y--;
            dx = dx + 2 * pow(ry, 2);
            dy = dy - 2 * pow(rx, 2);
            p = p + dx - dy + pow(ry, 2);
        }
    } while (dx < dy);

    //Region-2
    p=pow(ry,2)*pow(x+0.5,2)+pow(rx,2)*pow(y-1,2)-pow(rx,2)*pow(ry,2);

    do{
        plotPoints(xc + x, yc + y);
        plotPoints(xc + x, yc - y);
        plotPoints(xc - x, yc + y);
        plotPoints(xc - x, yc - y);
        if(p>0){
            y--;
            dy=dy-2*pow(rx,2);
            p=p-dy+pow(rx,2);
        }
        else{
            x++;
            y--;
            dy=dy-2*pow(rx,2);
            dx=dx+2*pow(ry,2);
            p=p+dx-dy+pow(rx,2);
        }
    }while(y!=0);
    glFlush();
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    midPointEllipse(400, 200, 100, 100);
}

void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Mid-point ellipse drawing algorithm");
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
}