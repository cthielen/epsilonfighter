#ifndef H_BITMASK
#define H_BITMASK

#include "includes.h"

typedef struct {
  unsigned char* bm;
  int w, h;
  int bits_on; // number of on bits in entire mask (for calculating percent)
} bitmask;

bitmask* CreateBitmask(SDL_Surface *s);
int CalculateCollision(bitmask *b1, bitmask *b2, int o_x, int o_y);
int ExpandBitmask(bitmask *bm);
int FreeBitmask(bitmask *bm);

#endif /* H_BITMASK */
