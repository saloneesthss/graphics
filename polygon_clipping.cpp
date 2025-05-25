#include <graphics.h>
#include <stdio.h>

#define MAX_POINTS 20

// Clipping window boundaries
int x_min = 100, y_min = 100, x_max = 300, y_max = 300;

// Structure to represent a point
typedef struct {
    int x, y;
} Point;

// Check if a point is inside the boundary (depending on edge)
int inside(Point p, int edge) {
    switch (edge) {
        case 0: return p.x >= x_min; // LEFT
        case 1: return p.x <= x_max; // RIGHT
        case 2: return p.y >= y_min; // BOTTOM
        case 3: return p.y <= y_max; // TOP
    }
    return 0;
}

// Get intersection point of the line with the boundary edge
Point intersect(Point p1, Point p2, int edge) {
    Point i;
    float m;

    if (p1.x != p2.x)
        m = (float)(p2.y - p1.y) / (p2.x - p1.x);
    else
        m = 1e9;

    switch (edge) {
        case 0: // LEFT
            i.x = x_min;
            i.y = p1.y + (x_min - p1.x) * m;
            break;
        case 1: // RIGHT
            i.x = x_max;
            i.y = p1.y + (x_max - p1.x) * m;
            break;
        case 2: // BOTTOM
            i.y = y_min;
            if (m != 0)
                i.x = p1.x + (y_min - p1.y) / m;
            else
                i.x = p1.x;
            break;
        case 3: // TOP
            i.y = y_max;
            if (m != 0)
                i.x = p1.x + (y_max - p1.y) / m;
            else
                i.x = p1.x;
            break;
    }
    return i;
}

// Sutherland-Hodgman polygon clipping
int clipPolygon(Point in[], int in_len, Point out[], int edge) {
    Point temp[MAX_POINTS];
    int count = 0;

    for (int i = 0; i < in_len; i++) {
        Point curr = in[i];
        Point prev = in[(i - 1 + in_len) % in_len];

        int curr_in = inside(curr, edge);
        int prev_in = inside(prev, edge);

        if (prev_in && curr_in) {
            temp[count++] = curr;
        } else if (prev_in && !curr_in) {
            temp[count++] = intersect(prev, curr, edge);
        } else if (!prev_in && curr_in) {
            temp[count++] = intersect(prev, curr, edge);
            temp[count++] = curr;
        }
    }

    for (int i = 0; i < count; i++) {
        out[i] = temp[i];
    }

    return count;
}

// Draw polygon using array of points
void drawPolygon(Point poly[], int n, int color) {
    setcolor(color);
    for (int i = 0; i < n - 1; i++) {
        line(poly[i].x, poly[i].y, poly[i + 1].x, poly[i + 1].y);
    }
    line(poly[n - 1].x, poly[n - 1].y, poly[0].x, poly[0].y);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char *)"");

    int n;
    Point input[MAX_POINTS], output[MAX_POINTS];

    printf("Enter number of vertices (max %d): ", MAX_POINTS);
    scanf("%d", &n);

    printf("Enter vertices (x y):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &input[i].x, &input[i].y);
    }

    drawPolygon(input, n, WHITE);

    // Draw clipping window in WHITE
    setcolor(WHITE);
    rectangle(x_min, y_min, x_max, y_max);

    // Clipping
    int clipped_n = n;
    Point poly1[MAX_POINTS], poly2[MAX_POINTS];

    for (int i = 0; i < n; i++) {
        poly1[i] = input[i];
    }

    for (int edge = 0; edge < 4; edge++) {
        clipped_n = clipPolygon(poly1, clipped_n, poly2, edge);
        for (int i = 0; i < clipped_n; i++) {
            poly1[i] = poly2[i];
        }
    }

    if (clipped_n > 0) {
        drawPolygon(poly1, clipped_n, WHITE);
    }

    getch();
    closegraph();
    return 0;
}
