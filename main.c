#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define CONIINE_IMPLEMENTATION
#include "coniine.h"


void draw_to_ppm(uint32_t *pixels, size_t width, size_t height,
    const char *path);

Vector2 vertices[3] = {
  {.x = 100, .y = 20},
  {.x = 200, .y = 280},
  {.x = 30,  .y = 210}
};

Vector2 vertices1[3] = {
  {.x = 100, .y = 300},
  {.x = 200, .y = 580},
  {.x = 30,  .y = 610}
};

int main(void) {
  const char *path = "output.ppm";
  for (size_t i = 0; i < CONIINE_WIDTH * CONIINE_HEIGHT; ++i) {
    CONIINE_PIXELS[i] = RANDOM_COLOR;
  } 

  //:NOTE: The data
  coniine_fill_triangleV(vertices[0], vertices[1], vertices[2], CONIINE_BLACK);
  coniine_fill_triangleI(vertices1[0].x,vertices1[0].y, vertices1[1].x,
                  vertices1[1].y, vertices1[2].x, vertices1[2].y, CONIINE_BLUE);
  coniine_fill_rect((CONIINE_WIDTH / 2) + 110, (CONIINE_HEIGHT / 2) + 110, 200, 100, CONIINE_CYAN);
  coniine_drawLine(10, 1000, 400, 400, CONIINE_GREEN);
  coniine_drawLine(100, 100, 1000, 100, CONIINE_CYAN);// Horizontal line (dx =  0)
  coniine_drawRect(CONIINE_WIDTH / 2, CONIINE_HEIGHT / 2, 200, 100, CONIINE_RED);
  coniine_fill_circle(CONIINE_FILL, 120*4, 120*3, 50, CONIINE_SILVER);
  coniine_fill_circle(CONIINE_LINE, 220*4, 220*2, 50, CONIINE_SALMON);
  
  //:NOTE: The test 
  draw_to_ppm(CONIINE_PIXELS, CONIINE_WIDTH, CONIINE_HEIGHT, path);
  return 0;
}

void draw_to_ppm(uint32_t *pixels, size_t width, size_t height,
    const char *path) {
  FILE *fp = fopen(path, "wb");
  if (fp == NULL) {
    fprintf(stderr, "Failed to open file for writing at %s\n", path);
    return;
  }

  fprintf(fp, "P6\n%zu %zu\n255\n", width, height);

  for (size_t i = 0; i < width * height; ++i) {
    uint32_t pixel = pixels[i];

    uint8_t bytes[3] = {
      (pixel >> 16) & 0xFF,
      (pixel >> 8) & 0xFF, 
      (pixel >> 0) & 0xFF  
    };

    fwrite(bytes, sizeof(bytes), 1, fp);
  }
  fclose(fp);
}

