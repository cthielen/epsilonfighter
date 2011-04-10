#include "bitmask.h"
#include "includes.h"

/* written by chris thielen, written for napkin37 codebase */

/* gives the minesweeper number (how many of the 8 bits around it are on) */
static inline int IronMaiden(bitmask *bm, int x, int y);

bitmask *CreateBitmask(SDL_Surface *s) {
	int w, h;
	Uint8* p;
	int bpp;
	Uint32 pixel;
	unsigned char * c;
	int i, j;
	bitmask *bm;
  
	bm = (bitmask *)malloc(sizeof(bitmask));
  
	assert(bm);
	assert(s);
  
	bm->bits_on = 0;
	bm->w = s->w;
	bm->h = s->h;
	bm->bm = (unsigned char *)malloc(sizeof(unsigned char) * bm->w * bm->h);
  
	assert(bm->bm);
  
	if(SDL_MUSTLOCK(s))
		while(SDL_LockSurface(s) != -1) SDL_Delay(1);
  
	c = bm->bm;
  
	w = s->w;
	h = s->h;
  
	/* clear any current information set there */
	memset( c, 0, sizeof( char ) * w * h );
  
	bpp = s->format->BytesPerPixel;
  
	for( j = 0; j < h; j++ ) {
		for( i = 0; i < w; i++ ) {
			/* Here p is the address to the pixel we want to retrieve */
			p = ( Uint8 * ) s->pixels + j * s->pitch + i * bpp;
	  
			/* extract pixel */
			if( s->format->BitsPerPixel == 16 )
				pixel = *( Uint16 * ) p;
			else if( s->format->BitsPerPixel == 32 )
				pixel = *( Uint32 * ) p;
	  else
		  assert( "bpp not handled!");
	  
	  if(pixel != s->format->colorkey) {
				/* dont set a pixel that they cant see */
				/* check for alpha */
	    pixel &= s->format->Amask;
	    pixel >>= s->format->Ashift;
	    pixel <<= s->format->Aloss;
	
		  if( pixel > 15 ) {
	    	*c = 1;
	 		bm->bits_on++;
		  }
	  }
	  
	  c++;
	}
    }
  
	SDL_UnlockSurface(s);
  
	return(bm);
}

// returns serverity of collision
int CalculateCollision(bitmask* b1, bitmask* b2, int o_x, int o_y) {
	int collide = 0, i, j, k, l;
	int start_x, start_y, w, h, start2_x, start2_y;
  
	if( !b1 ) return 0;
	if( !b2 ) return 0;
	if( !b1->bm ) return 0;
	if( !b2->bm ) return 0;
  
	if( o_x >= 0 ) {
		start_x = o_x;
		if( ( o_x + b2->w ) > b1->w )
			w = b1->w;
		else
			w = b2->w;
		start2_x = 0;
	} else {
		start_x = 0;
		if( ( o_x + b2->w ) > b1->w )
			w = b1->w;
		else
			w = b2->w + o_x;
		start2_x = ( o_x * -1 );
	}
	
  if( o_y >= 0 ) {
      start_y = o_y;
      if( ( o_y + b2->h ) > b1->h )
	h = b1->h;
      else
	h = b2->h;
      start2_y = 0;
    } else {
      start_y = 0;
      if( ( o_y + b2->h ) > b1->h )
		h = b1->h;
      else
		h = b2->h + o_y;
      start2_y = ( o_y * -1 );
    }
  
	for( j = start_y, l = start2_y; j < h; j++, l++ ) {
		for( i = start_x, k = start2_x; i < w; i++, k++ ) {
			if( b1->bm[( j * b1->w ) + i] & b2->bm[( l * b2->w ) + k] )
				collide++;
		}
	}
  
	return(collide);
}

int FreeBitmask(bitmask* bm) {
  if(!bm)
    return -1;
  if(!bm->bm)
    return -1;
  free(bm->bm);
  free(bm);
  
  return(0);
}

/* make bitmask beefy! */
int ExpandBitmask(bitmask* bm) {
  int i, j;
  int iterations = 6;
  
  assert(bm);
  
  while(iterations--) {
    /* simple additive filter */
    for( j = 0; j < bm->h; j++ ) {
      for( i = 0; i < bm->w; i++ ) {
	if( bm->bm[( j * bm->w ) + i] ) {
	  if( IronMaiden( bm, i, j ) )
	    bm->bm[( j * bm->w ) + i] = 1;
	}
      }
    }
  }
  
  return(0);
}

/* gives the minesweeper number (how many of the 8 bits around it are on) */
static inline int IronMaiden(bitmask *bm, int x, int y) {
  int num = 0;
  
  assert( bm );
  
  /* check left */
  if( x > 0 )
    {
      if( bm->bm[( y * bm->w ) + x - 1] )
	num++;
    }
  /* check right */
  if( x < ( bm->w - 1 ) )
    {
      if( bm->bm[( y * bm->w ) + x + 1] )
	num++;
    }
  /* check top */
  if( y > 0 )
    {
      if( bm->bm[( ( y - 1 ) * bm->w ) + x] )
	num++;
    }
  /* check bottom */
  if( y < ( bm->h - 1 ) )
    {
      if( bm->bm[( ( y + 1 ) * bm->w ) + x] )
	num++;
    }
  
  return(num);
}
