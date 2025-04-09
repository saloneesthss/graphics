#include<graphics.h>
#include<conio.h>
#include<math.h>
int main()
{
    int gd=DETECT, gm;
    initgraph(&gd,&gm,(char*)"");
    float x,y;
    // float x=50,y=70;
    scanf("%f%f",&x,&y);
    int x_scan=floor(x);
    int y_scan=floor(y);
    putpixel(x_scan,y_scan,WHITE);
    getch();
    closegraph();
    return 0;
}