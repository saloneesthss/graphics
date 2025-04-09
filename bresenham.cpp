#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>
int main()
{
    float dy, dx, x, y, x1, x2, y1, y2, p;
    int gd, gm;
    detectgraph(&gd, &gm);
    initgraph(&gd, &gm, (char *)"C:\\Turboc3\\BGI");
    printf("\n Enter 1st co-ordinate:");
    scanf("%f%f", &x1, &y1);
    printf("\n Enter 2nd co-ordinate:");
    scanf("%f%f", &x2, &y2);
    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    if (x1 < x2)
    {
        x = x1;
        y = y1;
    }
    if (x1 > x2)
    {
        x = x2;
        y = y2;
    }
    p = (2 * dy) - dx;
    while (x <= x1 || x <= x2)
    {
        if (p < 0)
        {
            x = x + 1;
            y = y;
            p = p + (2 * dy);
        }
        else
        {
            x = x + 1;
            y = y + 1;
            p = p + (2 * dy) - (2 * dx);
        }
        putpixel((int)x, (int)y, WHITE);
    }
    getch();
    closegraph();
}