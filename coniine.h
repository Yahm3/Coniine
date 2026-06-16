#ifndef CONIINE_H
#define CONIINE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define CONIINE_WIDTH 1000 //:TEST: Right now I am just using this for testing
#define CONIINE_HEIGHT 700
#define CONIINE_PI (float)(22/7)

#define CONIINE_SWAP(type, x, y) do { type temp = x; x = y; y = temp; } while(0)
#define CONIINE_ROUND(type, x) ((type)((x) >= 0 ? ((x) + 0.5) : ((x) - 0.5)))
#define CONIINE_MIN(a,b) ((a) < (b) ? (a) : (b))
#define CONIINE_MIN3(a,b,c) CONIINE_MIN(a,CONIINE_MIN(b,c))
#define CONIINE_MAX(a,b) ((a) > (b) ? (a) : (b))
#define CONIINE_MAX3(a,b,c) CONIINE_MAX(a,CONIINE_MAX(b,c))
#define CONIINE_IS_VALID_PIXEL(x, y) ((x) >= 0 && (x) < CONIINE_WIDTH && (y) >= 0 && (y) < CONIINE_HEIGHT)

#define RANDOM_COLOR    0xFFA88DC2

#define CONIINE_RED     0xFFFF0000
#define CONIINE_GREEN   0xFF00FF00
#define CONIINE_BLUE    0xFF0000FF
#define CONIINE_CYAN    0xFF00FFFF
#define CONIINE_YELLOW  0xFFFFFF00
#define CONIINE_MAGENTA 0xFFFF00FF

#define CONIINE_WHITE       0xFFFFFFFF
#define CONIINE_BLACK       0xFF000000
#define CONIINE_LIGHTGRAY   0xFFD3D3D3
#define CONIINE_GRAY        0xFF808080
#define CONIINE_DARKGRAY    0xFF404040

#define CONIINE_ORANGE      0xFFFFA500
#define CONIINE_GOLD        0xFFFFD700
#define CONIINE_CORAL       0xFFFF7F50
#define CONIINE_SALMON      0xFFFA8072
#define CONIINE_BROWN       0xFFA52A2A
#define CONIINE_MAROON      0xFF800000

#define CONIINE_LIME        0xFF32CD32
#define CONIINE_DARKGREEN   0xFF006400
#define CONIINE_OLIVE       0xFF808000
#define CONIINE_SKYBLUE     0xFF87CEEB
#define CONIINE_TEAL        0xFF008080
#define CONIINE_NAVY        0xFF000080

#define CONIINE_PINK        0xFFFFC0CB
#define CONIINE_HOTPINK     0xFFFF69B4
#define CONIINE_VIOLET      0xFF9B26B6
#define CONIINE_PURPLE      0xFF800080
#define CONIINE_INDIGO      0xFF4B0082

#define CONIINE_NEON_PINK   0xFFFF10F0
#define CONIINE_NEON_GREEN  0xFF39FF14
#define CONIINE_ELECTRIC_BLUE 0xFF7DF9FF
#define CONIINE_CYBER_YELLOW 0xFFFFD300
#define CONIINE_LASER_RED   0xFFFF003C

#define CONIINE_PASTEL_PINK 0xFFFFD1DC
#define CONIINE_MINT        0xFF98FF98
#define CONIINE_LAVENDER    0xFFE6E6FA
#define CONIINE_PEACH       0xFFFFE5B4
#define CONIINE_PERIWINKLE  0xFFCCCCFF

#define CONIINE_FOREST      0xFF228B22
#define CONIINE_WOOD        0xFF8B5A2B
#define CONIINE_SAND        0xFFF4A460
#define CONIINE_CLAY        0xFFB66A50
#define CONIINE_OCEAN       0xFF006994

#define CONIINE_SILVER      0xFFC0C0C0
#define CONIINE_BRONZE      0xFFCD7F32
#define CONIINE_COPPER      0xFFB87333

// Structs
typedef struct {//:TODO: Finish up here
  float r;
  float g;
  float b;
} Color;

typedef struct {
  float x, y;
} Vector2;

typedef enum {
  CONIINE_FILL, 
  CONIINE_LINE
} ConiineDrawMode;

static uint32_t CONIINE_PIXELS[CONIINE_WIDTH * CONIINE_HEIGHT];
float CONIINE_LERP(float x, float y, float z);
int CONIINE_EDGE_CROSS(Vector2 *a, Vector2 *b, Vector2 *p);
bool CONIINE_TOP_LEFT_EDGE(Vector2 *start, Vector2 *end);

void coniine_fill_rect(int x, int y, size_t w, size_t h, uint32_t color);
void coniine_drawLine(int xStart, int yStart, int xEnd, int yEnd, uint32_t color);
void coniine_drawRect( int x, int y, int width, int height, uint32_t color);
void coniine_fill_triangleV(Vector2 p1, Vector2 p2, Vector2 p3, uint32_t color);
void coniine_fill_triangleI(int px1, int py1, int px2, int py2, int px3, int py3, uint32_t color);
void coniine_fill_circle(ConiineDrawMode mode, int x, int y, int radius, uint32_t color);
void coniine_drawCircle(int xCenter, int yCenter, int x, int y, uint32_t color);

#ifdef CONIINE_IMPLEMENTATION
void coniine_drawCircle(int xCenter, int yCenter, int x, int y, uint32_t color) {
  int points[8][2] = {
    {xCenter + x, yCenter + y},
    {xCenter - x, yCenter + y},
    {xCenter + x, yCenter - y},
    {xCenter - x, yCenter - y},
    {xCenter + y, yCenter + x},
    {xCenter - y, yCenter + x},
    {xCenter + y, yCenter - x},
    {xCenter - y, yCenter - x}
  };
  for(int i = 0; i < 8; i++){
    int px = points[i][0];
    int py = points[i][1];
    if(CONIINE_IS_VALID_PIXEL(px, py)){
      CONIINE_PIXELS[(py * CONIINE_WIDTH) + px] = color;
    }
  }
}

void coniine_fill_circle(ConiineDrawMode mode, int xCenter, int yCenter, int radius, uint32_t color) {
  if(radius < 0){
    printf("Error: radius cannot be less or equal to zero");
    return;
  }
  if(mode == CONIINE_FILL){
    int x = 0, y = radius;
    int d = 3 - 2 * radius;

    while(y >= x){
      coniine_drawLine(xCenter - x, yCenter - y, xCenter + x, yCenter - y, color);
      coniine_drawLine(xCenter - x, yCenter + y, xCenter + x, yCenter + y, color);

      coniine_drawLine(xCenter - y, yCenter - x, xCenter + y, yCenter - x, color);
      coniine_drawLine(xCenter - y, yCenter + x, xCenter + y, yCenter + x, color);

      if(d > 0){
	y--;
	d = d + 4 * (x - y) + 10;
      } else {
	d = d + 4 * x + 6;
      }
      x++;
    }
  } else if(mode == CONIINE_LINE){
    int x = 0, y = radius;
    int d = 3 - 2 * radius;
    while(y >= x){
      coniine_drawCircle(xCenter, yCenter, x, y, color);
      if(d > 0){
	y--;
	d = d + 4 * (x - y) + 10;
      } else {
	d = d + 4 * x + 6;
      }
      x++;
    }
  }
}

void coniine_fill_triangleI(int px1,int py1,int px2, int py2, int px3, int py3, uint32_t color) {
  Vector2 p1 = {.x = px1, .y  = py1};
  Vector2 p2 = {.x = px2, .y  = py2};
  Vector2 p3 = {.x = px3, .y  = py3};
  coniine_fill_triangleV(p1, p2, p3, color);
}

bool CONIINE_TOP_LEFT_EDGE(Vector2 *start, Vector2 *end){
  Vector2 edge = {end->x - start->x, end->y - start->x};
  bool is_top_edge = edge.y == 0 && edge.x > 0;
  bool is_left_edge = edge.y < 0;
  return is_top_edge || is_left_edge;
}

int CONIINE_EDGE_CROSS(Vector2 *a, Vector2 *b, Vector2 *p){
  Vector2 ab = {b->x - a->x, b->y - a->y};
  Vector2 ap = {p->x - a->x, p->y - a->y};
  return ab.x * ap.y - ab.y * ap.x;
}
void coniine_fill_triangleV(Vector2 p1, Vector2 p2, Vector2 p3, uint32_t color){
  // Bound box with all candidate pixels
  int x_min = CONIINE_MIN3(p1.x, p2.x, p3.x);
  int y_min = CONIINE_MIN3(p1.y, p2.y, p3.y);
  int x_max = CONIINE_MAX3(p1.x, p2.x, p3.x);
  int y_max = CONIINE_MAX3(p1.y, p2.y, p3.y);

  int bias0 = CONIINE_TOP_LEFT_EDGE(&p2, &p3) ? 0 : -1;
  int bias1 = CONIINE_TOP_LEFT_EDGE(&p3, &p1) ? 0 : -1;
  int bias2 = CONIINE_TOP_LEFT_EDGE(&p1, &p2) ? 0 : -1;

  for(int y = y_min; y <= y_max; y++){
    for(int x = x_min; x <= x_max; x++){
      Vector2 p = {x,y};
      int w0 = CONIINE_EDGE_CROSS(&p2, &p3, &p) + bias0;
      int w1 = CONIINE_EDGE_CROSS(&p3, &p1, &p) + bias1;
      int w2 = CONIINE_EDGE_CROSS(&p1, &p2, &p) + bias2;
      if(w0 >= 0 && w1 >= 0 && w2 >= 0){// Are we inside or out
	CONIINE_PIXELS[y * CONIINE_WIDTH + x] = color;
      }
    }
  }
}

float CONIINE_LERP(float x, float y, float z) {
  return (1 - z) * x + z * y;
}

void coniine_fill_rect(int x, int y, size_t w, size_t h, uint32_t color){
  for(size_t row = 0; row < h; ++row){
    for(size_t col = 0; col < w; ++col){
      int px = x + col;
      int py = y + row;
      if(px >= 0 && px < CONIINE_WIDTH && py >= 0 && py < CONIINE_HEIGHT){
	CONIINE_PIXELS[py * CONIINE_WIDTH + px] = color;
      }
    }
  }
}

void coniine_drawLine(int xStart, int yStart, int xEnd, int yEnd, uint32_t color){
  int dx = xEnd - xStart;
  int dy = yEnd - yStart;

  if(dx == 0){
    if(yStart > yEnd){
      CONIINE_SWAP(int, yStart, yEnd);
    }
    for(int y = yStart; y < yEnd; y++){
      if(xStart >= 0 && xStart < CONIINE_WIDTH && y >= 0 && y < CONIINE_HEIGHT){
	CONIINE_PIXELS[y * CONIINE_WIDTH + xStart] = color;
      }
    }
    return;
  }

  double slope = (double)dy/dx;

  if(xStart > xEnd){
    CONIINE_SWAP(int, xStart, xEnd);
    CONIINE_SWAP(int, yStart, yEnd);
  }

  for(int x = xStart; x < xEnd; x++){
    int y = CONIINE_ROUND(int, yStart + (x - xStart) * (slope)); 
    if(x >= 0 && x < CONIINE_WIDTH && y >= 0 && y < CONIINE_HEIGHT){
      CONIINE_PIXELS[y * CONIINE_WIDTH + x] = color;
    }
  }
}

void coniine_drawRect(int x, int y, int width, int height, uint32_t color) {
  int right = x + width - 1;
  int bottom = y + height - 1;
  if(width <= 0 || height <= 0) return;

  for(int i = x; i <= right; i++){
    if(i >= 0 && i < CONIINE_WIDTH){
      if(y >= 0 && y < CONIINE_HEIGHT){
	CONIINE_PIXELS[y * CONIINE_WIDTH + i] = color;
      }
      if(bottom >= 0 && bottom < CONIINE_HEIGHT){
	CONIINE_PIXELS[bottom * CONIINE_WIDTH + i] = color;
      }
    }
  }
  for(int j = y; j <= bottom; j++){
    if(j >= 0 && j < CONIINE_HEIGHT){
      if(x >= 0 && x < CONIINE_WIDTH){
	CONIINE_PIXELS[j * CONIINE_WIDTH + x] = color;
      }
      if(right >= 0 && right < CONIINE_WIDTH){
	CONIINE_PIXELS[j * CONIINE_WIDTH + right] = color;
      }
    }
  }
}

#endif // CONIINE_IMPLEMENTATION
#endif // CONIINE_H

//---REFERENCES----
//:TODO: Draw line and shapes that have thickness
//:TODO: check this out -> https://en.wikipedia.org/wiki/Sierpi%C5%84ski_triangle
// https://www.tutorialspoint.com/computer_graphics/bresenhams_circle_generation_algorithm.htm
// what is a stride: https://medium.com/@oleg.shipitko/what-does-stride-mean-in-image-processing-bba158a72bcd
// Triangle rasterization: https://youtu.be/k5wtuKWmV48?si=qXgsP8sgcuOi-l56
// sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
// https://gabrielgambetta.com/computer-graphics-from-scratch/07-filled-triangles.html
// gabrielgambetta.com/computer-graphics-from-scratch/07-filled-triangles.html
// https://studylib.net/doc/27632019/1---line-drawing-algorithms?p=2
// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
// :CHECK: https://learn.microsoft.com/en-us/windows/win32/direct3d11/d3d10-graphics-programming-guide-rasterizer-stage-rules
