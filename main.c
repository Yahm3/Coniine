#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define CONIINE_IMPLEMENTATION
#include "coniine.h"


void coniine_drawRect(uint32_t *pixels, int x, int y, int width, int height);
void coniine_drawLine(int var1, int var2, int var3, int var4);
void draw_to_ppm(uint32_t *pixels, size_t width, size_t height,
    const char *path);

int main(void) {
  const char *path = "output.ppm";
  for (size_t i = 0; i < CONIINE_WIDTH * CONIINE_HEIGHT; ++i) {
    coniine_pixels[i] = RANDOM_COLOR;
  } 

  coniine_fill_rect(coniine_pixels, CONIINE_WIDTH / 2, CONIINE_HEIGHT / 2, 200, 100, CONIINE_CYAN);
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

void coniine_drawLine(int var1, int var2, int var3, int var4){
  /* NOB_TODO("Implement drawLine"); */
}

void coniine_drawRect(uint32_t *pixels, int x, int y, int width, int height) {
  if (width >= 0 && height >= 0) {
    if (height != 0 && width != 0) {
      coniine_drawLine(x, y, x + width - 1, y);
      coniine_drawLine(x + width, y, x + width, y + height - 1);
      coniine_drawLine(x + width, y + height, x + 1, y + height);
      coniine_drawLine(x, y + height, x, y + 1);
    } else {
      coniine_drawLine(x, y, x + width, y + height);
    }

  }
}
