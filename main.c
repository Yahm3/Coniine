#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define CONIINE_IMPLEMENTATION
#include "coniine.h"


void draw_to_ppm(uint32_t *pixels, size_t width, size_t height,
    const char *path);

int main(void) {
  const char *path = "output.ppm";
  for (size_t i = 0; i < CONIINE_WIDTH * CONIINE_HEIGHT; ++i) {
    coniine_pixels[i] = RANDOM_COLOR;
  } 

  //:NOTE: The data
  coniine_fill_rect(coniine_pixels, (CONIINE_WIDTH / 2) + 110, (CONIINE_HEIGHT / 2) + 110, 200, 100, CONIINE_CYAN);
  coniine_drawLine(coniine_pixels, 10, 1000, 400, 400, CONIINE_GREEN);
  coniine_drawLine(coniine_pixels, 100, 100, 1000, 100, CONIINE_CYAN);// Horizontal line (dx =  0)
  coniine_drawRect(coniine_pixels, CONIINE_WIDTH / 2, CONIINE_HEIGHT / 2, 200, 100, CONIINE_RED);

  //:NOTE: The test 
  draw_to_ppm(coniine_pixels, CONIINE_WIDTH, CONIINE_HEIGHT, path);
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

