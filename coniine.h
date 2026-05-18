#ifndef CONIINE_H
#define CONIINE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define CONIINE_WIDTH 1000 //:NOTE: Right now I am just using this for testing
#define CONIINE_HEIGHT 700

static uint32_t coniine_pixels[CONIINE_WIDTH * CONIINE_HEIGHT];

#define RANDOM_COLOR  	0xFFA88DC2
#define CONIINE_RED   	0xFFFF0000
#define CONIINE_GREEN   0xFF00FF00
#define CONIINE_BLUE    0xFF0000FF
#define CONIINE_CYAN    0xFF00FFFF
#define CONIINE_BLACK   0xFFFFFFFF

void coniine_fill_rect(uint32_t *pixels, int x, int y, size_t w, size_t h, uint32_t color);

#ifdef CONIINE_IMPLEMENTATION

void coniine_fill_rect(uint32_t *pixels, int x, int y, size_t w, size_t h, uint32_t color){
  for(size_t row = 0; row < h; ++row){
    for(size_t col = 0; col < w; ++col){
      int px = x + col;
      int py = y + row;
      if(px >= 0 && px < CONIINE_WIDTH && py < CONIINE_HEIGHT){
	pixels[py * CONIINE_WIDTH + px] = color;
      }
    }
  }
}

#endif

#endif // CONIINE_H




