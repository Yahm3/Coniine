#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define CONIINE_IMPLEMENTATION
#include "coniine.h"


void draw_to_ppm(uint32_t *pixels, size_t width, size_t height, const char *path);

int main(void) {
  Vector2 vertices[3] = {
    {.x = 100, .y = 20},
    {.x = 200, .y = 280},
    {.x = 30,  .y = 210}
  };

  Coniine_Canvas cc  = coniine_canvas_create(1000,700);
  const char *path = "output.ppm";
  for (size_t i = 0; i < cc.width * cc.height; ++i) {
    cc.pixels[i] = COLOR_BLACK;
  } 

  coniine_draw_text(&cc,"the quick brown fox jumps over the lazy dog",
      2, 2, CONIINE_DEFAULT_FONT, 3,COLOR_SKYBLUE);

  //:NOTE: The test 
  draw_to_ppm(cc.pixels, cc.width, cc.height, path);
  coniine_canvas_destroy(&cc);
  return 0;
}

void draw_to_ppm(uint32_t *pixels, size_t width, size_t height,const char *path) {
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
