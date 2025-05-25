#include <graphics.h>
#include <stdio.h>
#include <conio.h>

int main() {
    int gd = DETECT, gm;
    int n, xs[100], ys[100], i, tx, ty;
    int x1, y1, x2, y2; // for line drawing

    printf("Enter number of sides of the polygon: ");
    scanf("%d", &n);

    printf("Enter x and y coordinates for each vertex:\n");
    for (i = 0; i < n; i++) {
        printf("x%d: ", i + 1);
        scanf("%d", &xs[i]);
        printf("y%d: ", i + 1);
        scanf("%d", &ys[i]);
    }

    printf("Enter translation distances (tx ty): ");
    scanf("%d %d", &tx, &ty);

    initgraph(&gd, &gm, (char *)""); // Initialize graphics mode

    // Draw the original polygon
    setcolor(WHITE);
    for (i = 0; i < n; i++) {
        x1 = xs[i];
        y1 = ys[i];
        x2 = xs[(i + 1) % n];
        y2 = ys[(i + 1) % n];
        line(x1, y1, x2, y2);
    }

    // Translate the polygon
    setcolor(YELLOW); // Set color for translated polygon
    for (i = 0; i < n; i++) {
        x1 = xs[i] + tx;
        y1 = ys[i] + ty;
        x2 = xs[(i + 1) % n] + tx;
        y2 = ys[(i + 1) % n] + ty;
        line(x1, y1, x2, y2);
    }

    getch(); // Wait for a key press
    closegraph(); // Close graphics mode
    return 0;
}