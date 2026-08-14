#ifndef CONIINE_DEF
#ifdef __cplusplus
#define CONIINE_DEF extern "C"
#else
#define CONIINE_DEF extern
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CONIINE_H
#define CONIINE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define CONIINE_PI (float)(22/7)
#define CONIINE_DEFAULT_THICKNESS 5

#define CONIINE_SWAP(type, x, y) do { type temp = x; x = y; y = temp; } while(0)
#define CONIINE_ROUND(type, x) ((type)((x) >= 0 ? ((x) + 0.5) : ((x) - 0.5)))
#define CONIINE_MIN(a,b) ((a) < (b) ? (a) : (b))
#define CONIINE_MIN3(a,b,c) CONIINE_MIN(a,CONIINE_MIN(b,c))
#define CONIINE_MAX(a,b) ((a) > (b) ? (a) : (b))
#define CONIINE_MAX3(a,b,c) CONIINE_MAX(a,CONIINE_MAX(b,c))

#define CONIINE_IS_VALID_PIXEL(canvas, x, y) ((x) >=\
    0 && (size_t)(x) < (canvas)->width && (y) >=\
    0 && (size_t)(y) < (canvas)->height)

#define CONIINE_ABS(x) ((x) < 0 ? -(x) : (x))

#define COLOR_RED           0xFFFF0000
#define COLOR_GREEN         0xFF00FF00
#define COLOR_BLUE          0xFF0000FF
#define COLOR_CYAN          0xFF00FFFF
#define COLOR_YELLOW        0xFFFFFF00
#define COLOR_MAGENTA       0xFFFF00FF

#define COLOR_WHITE         0xFFFFFFFF
#define COLOR_BLACK         0xFF000000
#define COLOR_LIGHTGRAY     0xFFD3D3D3
#define COLOR_GRAY          0xFF808080
#define COLOR_DARKGRAY      0xFF404040

#define COLOR_ORANGE        0xFFFFA500
#define COLOR_GOLD          0xFFFFD700
#define COLOR_CORAL         0xFFFF7F50
#define COLOR_SALMON        0xFFFA8072
#define COLOR_BROWN         0xFFA52A2A
#define COLOR_MAROON        0xFF800000

#define COLOR_LIME          0xFF32CD32
#define COLOR_DARKGREEN     0xFF006400
#define COLOR_OLIVE         0xFF808000
#define COLOR_SKYBLUE       0xFF87CEEB
#define COLOR_TEAL          0xFF008080
#define COLOR_NAVY          0xFF000080

#define COLOR_PINK          0xFFFFC0CB
#define COLOR_HOTPINK       0xFFFF69B4
#define COLOR_VIOLET        0xFF9B26B6
#define COLOR_PURPLE        0xFF800080
#define COLOR_INDIGO        0xFF4B0082

#define COLOR_NEON_PINK     0xFFFF10F0
#define COLOR_NEON_GREEN    0xFF39FF14
#define COLOR_ELECTRIC_BLUE 0xFF7DF9FF
#define COLOR_CYBER_YELLOW  0xFFFFD300
#define COLOR_LASER_RED     0xFFFF003C

#define COLOR_PASTEL_PINK   0xFFFFD1DC
#define COLOR_MINT          0xFF98FF98
#define COLOR_LAVENDER      0xFFE6E6FA
#define COLOR_PEACH         0xFFFFE5B4
#define COLOR_PERIWINKLE    0xFFCCCCFF

#define COLOR_FOREST        0xFF228B22
#define COLOR_WOOD          0xFF8B5A2B
#define COLOR_SAND          0xFFF4A460
#define COLOR_CLAY          0xFFB66A50
#define COLOR_OCEAN         0xFF006994

#define COLOR_SILVER        0xFFC0C0C0
#define COLOR_BRONZE        0xFFCD7F32
#define COLOR_COPPER        0xFFB87333

  typedef struct {
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

  typedef struct {
    size_t width;
    size_t height;
    const char  *glyph;
  } Coniine_Font;

  typedef struct {
    size_t width;
    size_t height;
    uint32_t *pixels;
  } Coniine_Canvas;

  Coniine_Canvas coniine_canvas_create(size_t width, size_t height);
  void coniine_canvas_destroy(Coniine_Canvas *canvas);

  float CONIINE_LERP(float x, float y, float z);
  int   CONIINE_EDGE_CROSS(Vector2 *a, Vector2 *b, Vector2 *p);
  bool  CONIINE_TOP_LEFT_EDGE(Vector2 *start, Vector2 *end);

  void coniine_fill_rect(Coniine_Canvas *cc, int x, int y, size_t w, size_t h, uint32_t color);
  void coniine_drawLineP(Coniine_Canvas *cc, int xStart, int yStart, int xEnd, int yEnd, uint32_t color);
  void coniine_drawLine(Coniine_Canvas *cc, int xStart, int yStart, int xEnd, int yEnd,size_t thickness, uint32_t color);
  void coniine_drawRect(Coniine_Canvas *cc,int x, int y, size_t width, size_t height, uint32_t color);
  void coniine_fill_triangleV(Coniine_Canvas *cc, Vector2 p1, Vector2 p2, Vector2 p3, uint32_t color);
  void coniine_fill_triangleI(Coniine_Canvas *cc, int px1, int py1, int px2, int py2, int px3, int py3, uint32_t color);
  void coniine_fill_circle(Coniine_Canvas *cc, ConiineDrawMode mode, int x, int y, int radius, uint32_t color);
  void coniine_drawCircle(Coniine_Canvas *cc, int xCenter, int yCenter, int x, int y, uint32_t color);
  void coniine_sierpinski_triangle(Coniine_Canvas *cc, Vector2 p1, Vector2 p2, Vector2 p3,int depth, uint32_t color);
  void coniine_draw_text(Coniine_Canvas *cc, const char *text, int x, int y, Coniine_Font font, size_t fontSize, uint32_t color);

#define CONIINE_DEFAULT_FONT_WIDTH 6
#define CONIINE_DEFAULT_FONT_HEIGHT 6

  static char DEFAULT_FONT_GLYPH[128][CONIINE_DEFAULT_FONT_HEIGHT][CONIINE_DEFAULT_FONT_WIDTH] = {
    ['a'] = {
      {0, 0, 0, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 0, 1, 0},
      {0, 1, 1, 1, 0},
      {1, 0, 0, 1, 0},
      {0, 1, 1, 1, 0},
    },
    ['b'] = {
      {1, 0, 0, 0, 0},
      {1, 1, 1, 0, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {1, 1, 1, 0, 0},
    },
    ['c'] = {
      {0, 0, 0, 0, 0},
      {0, 1, 1, 0, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 0, 0},
      {1, 0, 0, 1, 0},
      {0, 1, 1, 0, 0},
    },
    ['d'] = {
      {0, 0, 0, 1, 0},
      {0, 1, 1, 1, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {0, 1, 1, 1, 0},
    },
    ['e'] = {
      {0, 0, 0, 0, 0},
      {0, 1, 1, 0, 0},
      {1, 0, 0, 1, 0},
      {1, 1, 1, 1, 0},
      {1, 0, 0, 0, 0},
      {0, 1, 1, 1, 0},
    },
    ['f'] = {
      {0, 0, 1, 1, 0},
      {0, 1, 0, 0, 0},
      {1, 1, 1, 1, 0},
      {0, 1, 0, 0, 0},
      {0, 1, 0, 0, 0},
      {0, 1, 0, 0, 0},
    },
    ['g'] = {
      {0, 1, 1, 1, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {0, 1, 1, 1, 0},
      {0, 0, 0, 1, 0},
      {0, 1, 1, 0, 0},
    },
    ['h'] = {
      {1, 0, 0, 0, 0},
      {1, 1, 1, 0, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
    },
    ['i'] = {
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
    },
    ['j'] = {
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {1, 0, 1, 0, 0},
      {0, 1, 1, 0, 0},
    },
    ['k'] = {
      {1, 0, 0, 0, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 1, 0, 0},
      {1, 1, 0, 0, 0},
      {1, 0, 1, 0, 0},
      {1, 0, 0, 1, 0},
    },
    ['l'] = {
      {0, 1, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 1, 1, 1, 0},
    },
    ['m'] = {
      {0, 0, 0, 0, 0},
      {0, 1, 0, 1, 1},
      {1, 0, 1, 0, 1},
      {1, 0, 1, 0, 1},
      {1, 0, 1, 0, 1},
      {1, 0, 1, 0, 1},
    },
    ['n'] = {
      {0, 0, 0, 0, 0},
      {0, 1, 1, 1, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
    },
    ['o'] = {
      {0, 0, 0, 0, 0},
      {0, 1, 1, 0, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {0, 1, 1, 0, 0},
    },
    ['p'] = {
      {1, 1, 1, 0, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {1, 1, 1, 0, 0},
      {1, 0, 0, 0, 0},
      {1, 0, 0, 0, 0},
    },
    ['q'] = {
      {0, 1, 1, 1, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {0, 1, 1, 1, 0},
      {0, 0, 0, 1, 0},
      {0, 0, 0, 1, 0},
    },
    ['r'] = {
      {0, 0, 0, 0, 0},
      {1, 0, 1, 1, 0},
      {1, 1, 0, 0, 1},
      {1, 0, 0, 0, 0},
      {1, 0, 0, 0, 0},
      {1, 0, 0, 0, 0},
    },
    ['s'] = {
      {0, 0, 0, 0, 0},
      {0, 1, 1, 1, 0},
      {1, 0, 0, 0, 0},
      {1, 1, 1, 1, 0},
      {0, 0, 0, 1, 0},
      {1, 1, 1, 0, 0},
    },
    ['t'] = {
      {0, 1, 0, 0, 0},
      {0, 1, 0, 0, 0},
      {1, 1, 1, 1, 0},
      {0, 1, 0, 0, 0},
      {0, 1, 0, 1, 0},
      {0, 1, 1, 0, 0},
    },
    ['u'] = {
      {0, 0, 0, 0, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {0, 1, 1, 1, 0},
    },
    ['v'] = {
      {0, 0, 0, 0, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {0, 1, 1, 0, 0},
    },
    ['w'] = {
      {0, 0, 0, 0, 0},
      {1, 0, 0, 0, 1},
      {1, 0, 1, 0, 1},
      {1, 0, 1, 0, 1},
      {1, 0, 1, 0, 1},
      {0, 1, 1, 1, 1},
    },
    ['x'] = {
      {0, 0, 0, 0, 0},
      {1, 0, 1, 0, 0},
      {1, 0, 1, 0, 0},
      {0, 1, 0, 0, 0},
      {1, 0, 1, 0, 0},
      {1, 0, 1, 0, 0},
    },
    ['y'] = {
      {0, 0, 0, 0, 0},
      {1, 0, 1, 0, 0},
      {1, 0, 1, 0, 0},
      {1, 0, 1, 0, 0},
      {0, 1, 0, 0, 0},
      {0, 1, 0, 0, 0},
    },
    ['z'] = {
      {0, 0, 0, 0, 0},
      {1, 1, 1, 1, 0},
      {0, 0, 0, 1, 0},
      {0, 1, 1, 0, 0},
      {1, 0, 0, 0, 0},
      {1, 1, 1, 1, 0},
    },

    ['A'] = {0},
    ['B'] = {0},
    ['C'] = {0},
    ['D'] = {0},
    ['E'] = {0},
    ['F'] = {0},
    ['G'] = {0},
    ['H'] = {0},
    ['I'] = {0},
    ['J'] = {0},
    ['K'] = {0},
    ['L'] = {0},
    ['M'] = {0},
    ['N'] = {0},
    ['O'] = {0},
    ['P'] = {0},
    ['Q'] = {0},
    ['R'] = {0},
    ['S'] = {0},
    ['T'] = {0},
    ['U'] = {0},
    ['V'] = {0},
    ['W'] = {0},
    ['X'] = {0},
    ['Y'] = {0},
    ['Z'] = {0},

    ['0'] = {
      {0, 1, 1, 0, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {0, 1, 1, 0, 0},
    },
    ['1'] = {
      {0, 0, 1, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 1, 1, 1, 0},
    },
    ['2'] = {
      {0, 1, 1, 0, 0},
      {1, 0, 0, 1, 0},
      {0, 0, 0, 1, 0},
      {0, 1, 1, 0, 0},
      {1, 0, 0, 0, 0},
      {1, 1, 1, 1, 0},
    },
    ['3'] = {
      {0, 1, 1, 0, 0},
      {1, 0, 0, 1, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {0, 1, 1, 0, 0},
    },
    ['4'] = {
      {0, 0, 1, 1, 0},
      {0, 1, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {1, 1, 1, 1, 1},
      {0, 0, 0, 1, 0},
      {0, 0, 0, 1, 0},
    },
    ['5'] = {
      {1, 1, 1, 0, 0},
      {1, 0, 0, 0, 0},
      {1, 1, 1, 0, 0},
      {0, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {0, 1, 1, 0, 0},
    },
    ['6'] = {
      {0, 1, 1, 0, 0},
      {1, 0, 0, 0, 0},
      {1, 1, 1, 0, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {0, 1, 1, 0, 0},
    },
    ['7'] = {
      {1, 1, 1, 1, 0},
      {0, 0, 0, 1, 0},
      {0, 0, 1, 0, 0},
      {0, 1, 0, 0, 0},
      {0, 1, 0, 0, 0},
      {0, 1, 0, 0, 0},
    },
    ['8'] = {
      {0, 1, 1, 0, 0},
      {1, 0, 0, 1, 0},
      {0, 1, 1, 0, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {0, 1, 1, 0, 0},

    },
    ['9'] = {
      {0, 1, 1, 0, 0},
      {1, 0, 0, 1, 0},
      {1, 0, 0, 1, 0},
      {0, 1, 1, 1, 0},
      {0, 0, 0, 1, 0},
      {0, 1, 1, 0, 0},
    },

    [','] = {
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 1, 0},
      {0, 0, 1, 0, 0},
    },

    ['.'] = {
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
    },
    ['-'] = {
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {1, 1, 1, 1, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
    },
  };

  static Coniine_Font CONIINE_DEFAULT_FONT = {
    .width  = CONIINE_DEFAULT_FONT_WIDTH,
    .height = CONIINE_DEFAULT_FONT_HEIGHT,
    .glyph = &DEFAULT_FONT_GLYPH[0][0][0]
  };

#ifdef __cplusplus
}
#endif

#ifdef CONIINE_IMPLEMENTATION
CONIINE_DEF Coniine_Canvas coniine_canvas_create(size_t width, size_t height) {
  Coniine_Canvas canvas;
  canvas.width = width;
  canvas.height = height;
  canvas.pixels = (uint32_t *)malloc(width * height * sizeof(uint32_t));

  if (canvas.pixels != NULL) {
    memset(canvas.pixels, 0, width * height * sizeof(uint32_t));
  }

  return canvas;
}

CONIINE_DEF void coniine_canvas_destroy(Coniine_Canvas *cc) {
  if (cc && cc->pixels) {
    free(cc->pixels);
    cc->pixels = NULL;
  }
}

CONIINE_DEF void coniine_drawCircle(Coniine_Canvas *cc, int xCenter, int yCenter, int x, int y, uint32_t color) {
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
    if(CONIINE_IS_VALID_PIXEL(cc, px, py)){
      cc->pixels[py * cc->width + px] = color;
    }
  }
}

CONIINE_DEF void coniine_fill_circle(Coniine_Canvas *cc, ConiineDrawMode mode,
    int xCenter, int yCenter, int radius, uint32_t color) {
  if(radius < 0){
    printf("Error: radius cannot be less or equal to zero");
    return;
  }
  if(mode == CONIINE_FILL){
    int x = 0, y = radius;
    int d = 3 - 2 * radius;

    while(y >= x){
      coniine_drawLine(cc,xCenter - x, yCenter - y, xCenter + x,
	  yCenter - y, CONIINE_DEFAULT_THICKNESS, color);
      coniine_drawLine(cc,xCenter - x, yCenter + y, xCenter + x,
	  yCenter + y, CONIINE_DEFAULT_THICKNESS, color);

      coniine_drawLine(cc,xCenter - y, yCenter - x, xCenter + y,
	  yCenter - x, CONIINE_DEFAULT_THICKNESS, color);

      coniine_drawLine(cc,xCenter - y, yCenter + x, xCenter + y,
	  yCenter + x, CONIINE_DEFAULT_THICKNESS, color);

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
      coniine_drawCircle(cc, xCenter, yCenter, x, y, color);
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

CONIINE_DEF void coniine_fill_triangleI(Coniine_Canvas *cc, int px1, int py1,
    int px2, int py2, int px3, int py3, uint32_t color) {
  Vector2 p1 = {.x = px1, .y  = py1};
  Vector2 p2 = {.x = px2, .y  = py2};
  Vector2 p3 = {.x = px3, .y  = py3};
  coniine_fill_triangleV(cc, p1, p2, p3, color);
}

CONIINE_DEF bool CONIINE_TOP_LEFT_EDGE(Vector2 *start, Vector2 *end){
  Vector2 edge = {end->x - start->x, end->y - start->x};
  bool is_top_edge = edge.y == 0 && edge.x > 0;
  bool is_left_edge = edge.y < 0;
  return is_top_edge || is_left_edge;
}

CONIINE_DEF int CONIINE_EDGE_CROSS(Vector2 *a, Vector2 *b, Vector2 *p){
  Vector2 ab = {b->x - a->x, b->y - a->y};
  Vector2 ap = {p->x - a->x, p->y - a->y};
  return ab.x * ap.y - ab.y * ap.x;
}

CONIINE_DEF void coniine_fill_triangleV(Coniine_Canvas *cc, Vector2 p1, Vector2 p2, Vector2 p3, uint32_t color){
  // Bound box with all candidate pixels
  int x_min = CONIINE_MIN3(p1.x, p2.x, p3.x);
  int y_min = CONIINE_MIN3(p1.y, p2.y, p3.y);
  int x_max = CONIINE_MAX3(p1.x, p2.x, p3.x);
  int y_max = CONIINE_MAX3(p1.y, p2.y, p3.y);

  x_min = CONIINE_MAX(0, x_min);
  y_min = CONIINE_MAX(0, y_min);
  x_max = CONIINE_MIN(x_max, (int)cc->width - 1);
  y_max = CONIINE_MIN(y_max, (int)cc->height - 1);

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
	cc->pixels[y * cc->width + x] = color;
      }
    }
  }
}

CONIINE_DEF float CONIINE_LERP(float x, float y, float z) {
  return (1 - z) * x + z * y;
}

CONIINE_DEF void coniine_fill_rect(Coniine_Canvas *cc, int x, int y, size_t w, size_t h, uint32_t color){
  if(!cc || !cc->pixels) return;
  for(size_t row = 0; row < h; ++row){
    for(size_t col = 0; col < w; ++col){
      int px = x + col;
      int py = y + row;
      if(CONIINE_IS_VALID_PIXEL(cc,px,py)){
	cc->pixels[py * cc->width + px] = color;
      }
    }
  }
}

CONIINE_DEF void coniine_drawLineP(Coniine_Canvas *cc, int xStart, int yStart ,int xEnd, int yEnd, uint32_t color){
  int dx = xEnd - xStart;
  int dy = yEnd - yStart;

  if(dx == 0){ if(yStart > yEnd){
    CONIINE_SWAP(int, yStart, yEnd);
  }
  for(int y = yStart; y < yEnd; y++){
    if(xStart >= 0 && xStart < cc->width && y >= 0 && y < cc->height){
      cc->pixels[y * cc->width + xStart] = color;
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
    if(x >= 0 && x < cc->width && y >= 0 && y < cc->height){
      cc->pixels[y * cc->width + x] = color;
    }
  }
}

CONIINE_DEF void coniine_drawLine(Coniine_Canvas *cc, int xStart, int yStart,int xEnd,
    int yEnd, size_t thickness, uint32_t color) {
  if (thickness <= 1.0f) {
    coniine_drawLineP(cc, xStart, yStart, xEnd, yEnd, color);
    return;
  }

  float radius = thickness / 2.0f;
  float radiusSq = radius * radius;

  int minX = (xStart < xEnd ? xStart : xEnd) - (int)radius - 1;
  int maxX = (xStart > xEnd ? xStart : xEnd) + (int)radius + 1;
  int minY = (yStart < yEnd ? yStart : yEnd) - (int)radius - 1;
  int maxY = (yStart > yEnd ? yStart : yEnd) + (int)radius + 1;

  if (minX < 0) minX = 0;
  if (minY < 0) minY = 0;
  if (maxX >= cc->width) maxX = cc->width - 1;
  if (maxY >= cc->height) maxY = cc->height - 1;

  float dx = (float)(xEnd - xStart);
  float dy = (float)(yEnd - yStart);
  float lenSq = dx * dx + dy * dy;

  for (int y = minY; y <= maxY; y++) {
    for (int x = minX; x <= maxX; x++) {

      float px = (float)(x - xStart);
      float py = (float)(y - yStart);

      float t = 0.0f;
      if (lenSq > 0.0f) {
	t = (px * dx + py * dy) / lenSq;

	if (t < 0.0f) t = 0.0f;
	else if (t > 1.0f) t = 1.0f;
      }

      float closestX = xStart + t * dx;
      float closestY = yStart + t * dy;

      float distX = x - closestX;
      float distY = y - closestY;
      float distSq = (distX * distX) + (distY * distY);

      if (distSq <= radiusSq) {
	cc->pixels[y * cc->width + x] = color;
      }
    }
  }
}

CONIINE_DEF void coniine_drawRect(Coniine_Canvas *cc, int x, int y,
    size_t width, size_t height, uint32_t color) {
  int right = x + width - 1;
  int bottom = y + height - 1;
  if(width <= 0 || height <= 0) return;

  for(int i = x; i <= right; i++){
    if(i >= 0 && i < cc->width){
      if(y >= 0 && y < cc->height){
	cc->pixels[y * cc->width + i] = color;
      }
      if(bottom >= 0 && bottom < cc->height){
	cc->pixels[bottom * cc->width + i] = color;
      }
    }
  }
  for(int j = y; j <= bottom; j++){
    if(j >= 0 && j < cc->height){
      if(x >= 0 && x < cc->width){
	cc->pixels[j * cc->width + x] = color;
      }
      if(right >= 0 && right < cc->width){
	cc->pixels[j * cc->width + right] = color;
      }
    }
  }
}

//:NOTE: The visibility of the Sierpinski triangle depends on given depth relative to the width and height
CONIINE_DEF void coniine_sierpinski_triangle(Coniine_Canvas *cc, Vector2 p1, Vector2 p2,
    Vector2 p3, int depth, uint32_t color){
  if(depth < 0){
    printf("Error: depth cannot be less than 0");
    return;
  }

  if(depth == 0){
    coniine_fill_triangleV(cc, p1, p2, p3, color);
    return;
  }

  //:NOTE: Find the midpoint of the two lines
  Vector2 m12 = {CONIINE_LERP(p1.x,p2.x,0.5f), CONIINE_LERP(p1.y,p2.y,0.5f)};
  Vector2 m23 = {CONIINE_LERP(p2.x,p3.x,0.5f), CONIINE_LERP(p2.y,p3.y,0.5f)};
  Vector2 m31 = {CONIINE_LERP(p3.x,p1.x,0.5f), CONIINE_LERP(p3.y,p1.y,0.5f)};

  coniine_sierpinski_triangle(cc, p1, m12, m31, depth - 1, color);
  coniine_sierpinski_triangle(cc, m12, p2, m23, depth - 1, color);
  coniine_sierpinski_triangle(cc, m31, m23, p3, depth - 1, color);
}

CONIINE_DEF void coniine_draw_text(Coniine_Canvas *cc, const char *text, int tx, int ty,
    Coniine_Font font, size_t fontSize, uint32_t color) {
  size_t text_length = strlen(text);
  for(size_t i = 0; i < text_length; i++){
    int x = tx + i*font.width*fontSize;
    int y = ty;
    const char *glyph = &font.glyph[text[i]*sizeof(char)*font.width*font.height];
    for(int dy = 0; (size_t)dy < font.height; dy++){
      for(int dx = 0; (size_t)dx < font.width; dx++){
	int px = x + dx*fontSize;
	int py = y + dy*fontSize;
	if(CONIINE_IS_VALID_PIXEL(cc, px, py)){
	  if(glyph[dy*font.width + dx]){
	    coniine_fill_rect(cc, px, py, fontSize, fontSize, color);
	  }
	}
      }
    }
  }
}

#endif // CONIINE_IMPLEMENTATION
#endif // CONIINE_H

//---REFERENCES----
// https://en.wikipedia.org/wiki/Sierpi%C5%84ski_triangle
// https://www.tutorialspoint.com/computer_graphics/bresenhams_circle_generation_algorithm.htm
// what is a stride: https://medium.com/@oleg.shipitko/what-does-stride-mean-in-image-processing-bba158a72bcd
// Triangle rasterization: https://youtu.be/k5wtuKWmV48?si=qXgsP8sgcuOi-l56
// sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
// https://gabrielgambetta.com/computer-graphics-from-scratch/07-filled-triangles.html
// gabrielgambetta.com/computer-graphics-from-scratch/07-filled-triangles.html
// https://studylib.net/doc/27632019/1---line-drawing-algorithms?p=2
// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
// :CHECK: https://learn.microsoft.com/en-us/windows/win32/direct3d11/d3d10-graphics-programming-guide-rasterizer-stage-rules
