#ifndef CONIINE_H
#define CONIINE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CONIINE_WIDTH 1000 //:TEST: Right now I am just using this for testing
#define CONIINE_HEIGHT 700

#define CONIINE_SWAP(type, x, y) do { type temp = x; x = y; y = temp; } while(0)
#define CONIINE_ROUND(type, x) ((type)((x) >= 0 ? ((x) + 0.5) : ((x) - 0.5)))
#define CONIINE_MIN(a,b) ((a) < (b) ? (a) : (b))
#define CONIINE_MIN3(a,b,c) CONIINE_MIN(a,CONIINE_MIN(b,c))
#define CONIINE_MAX(a,b) ((a) > (b) ? (a) : (b))
#define CONIINE_MAX3(a,b,c) CONIINE_MAX(a,CONIINE_MAX(b,c))

//:NOTE: COLORS
#define RANDOM_COLOR  	0xFFA88DC2
#define CONIINE_RED   	0xFFFF0000
#define CONIINE_GREEN   0xFF00FF00
#define CONIINE_BLUE    0xFF0000FF
#define CONIINE_CYAN    0xFF00FFFF
#define CONIINE_WHITE   0xFFFFFFFF
#define CONIINE_BLACK   0xFF000000

typedef struct {
  float x, y;
} Vector2;

static uint32_t CONIINE_PIXELS[CONIINE_WIDTH * CONIINE_HEIGHT];
float CONIINE_LERP(float x, float y, float z);
int CONIINE_EDGE_CROSS(Vector2 *a, Vector2 *b, Vector2 *p);
bool CONIINE_TOP_LEFT_EDGE(Vector2 *start, Vector2 *end);

void coniine_fill_rect(int x, int y, size_t w, size_t h, uint32_t color);
void coniine_drawLine(int xStart, int yStart, int xEnd, int yEnd, uint32_t color);
void coniine_drawRect( int x, int y, int width, int height, uint32_t color);
void coniine_fill_triangleV(Vector2 p1, Vector2 p2, Vector2 p3, uint32_t color);
void coniine_fill_triangleI(int px1,int py1,int px2, int py2, int px3, int py3, uint32_t color);


#ifdef CONIINE_IMPLEMENTATION
void coniine_fill_triangleI(int px1,int py1,int px2, int py2, int px3, int py3, uint32_t color){
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
	CONIINE_PIXELS[x * CONIINE_WIDTH + y] = color;
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
      if(right >= 0 && right < CONIINE_HEIGHT){
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
// Triangle rasterization: https://youtu.be/k5wtuKWmV48?si=qXgsP8sgcuOi-l56
// sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
// https://gabrielgambetta.com/computer-graphics-from-scratch/07-filled-triangles.html
// gabrielgambetta.com/computer-graphics-from-scratch/07-filled-triangles.html
// https://studylib.net/doc/27632019/1---line-drawing-algorithms?p=2
// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
// :CHECK: https://learn.microsoft.com/en-us/windows/win32/direct3d11/d3d10-graphics-programming-guide-rasterizer-stage-rules
