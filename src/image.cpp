#include "bitmask.h"
#include "image.h"
#include "includes.h"
#include "log.h"
#include "rotate.h"
#include "timer.h"
#include "video.h"

cImage::cImage( ) {
	image = NULL;
	memset( cache, 0, sizeof(SDL_Surface *) * NUM_ROTS );
	memset( bcache, 0, sizeof(bitmask *) * NUM_ROTS );
	memset( cache_access, 0, sizeof(Uint32) * NUM_ROTS );
}

cImage::cImage( char *filename ) {
	image = NULL;
	memset( cache, 0, sizeof(SDL_Surface *) * NUM_ROTS );
	memset( bcache, 0, sizeof(bitmask *) * NUM_ROTS );
	memset( cache_access, 0, sizeof(Uint32) * NUM_ROTS );

	Load( filename );
}

bool cImage::Load( char *filename ) {
	SDL_Surface *temp;

	temp = IMG_Load( filename );
	if( !temp ) {
		log( logWarning, "Could not load image '%s'\n", filename );
		return( false );
	}

	image = SDL_DisplayFormatAlpha( temp );

	SDL_FreeSurface( temp );

	return( true );
}

bool cImage::Draw( int x, int y ) {
	return( Draw( x, y, 0 ) );
}

bool cImage::DrawCentered( int x, int y ) {
	return( DrawCentered( x, y, 0 ) );
}

bool cImage::Draw( int x, int y, int ang ) {
	int i; // cache index
	cTimer *timer = cTimer::Instance();

	while( ang < 0 )
		ang += 360;
	
	// normalize angle
	ang %= 360;
	
	i = ang / 10;
	
	cache_access[i] = timer->GetTicks();
	if( !cache[i] )
		cache[i] = rotate( image, i * 10 );
	if( !bcache[i] )
		bcache[i] = CreateBitmask( cache[i] );

	DrawPartial( cache[i], x, y, 0, 0, image->w, image->h );
	
	return( true );
}

cImage::~cImage( ) {
	int i;
	
	if( image )
		SDL_FreeSurface( image );
	
	for( i = 0; i < NUM_ROTS; i++ ) {
		if( cache[i] )
			SDL_FreeSurface( cache[i] );
	}
}

bool cImage::DrawCentered( int x, int y, int ang ) {
	return( Draw( x - (image->w / 2), y - (image->h / 2), ang ) );
}

int cImage::GetWidth( void ) {
	if( image )
		return( image->w );
	
	return( 0 );
}

int cImage::GetHeight( void ) {
	if( image )
		return( image->h );
	
	return( 0 );
}

bitmask *cImage::GetBitmask( int ang ) {
	int i;
	cTimer *timer = cTimer::Instance();
	
	while( ang < 0 )
		ang += 360;
	
	// normalize angle
	ang %= 360;
	
	i = ang / 10;
	
	// ensure the bitmask index exists
	if( !bcache[i] ) {
		// ensure the bitmap index exists
		if( !cache[i] ) {
			cache[i] = rotate( image, i * 10 );
			cache_access[i] = timer->GetTicks();
		}
		
		bcache[i] = CreateBitmask( cache[i] );
	}
	
	return( bcache[i] );
}

SDL_Surface *cImage::GetImage( int ang ) {
	int i;
	cTimer *timer = cTimer::Instance();
	
	while( ang < 0 )
		ang += 360;
	
	// normalize angle
	ang %= 360;
	
	i = ang / 10;
	
	// ensure the bitmap index exists
	if( !cache[i] ) {
		cache[i] = rotate( image, i * 10 );
		cache_access[i] = timer->GetTicks();
	}
	
	return( cache[i] );
}

void cImage::DrawPartialCentered( int x, int y, int sx, int sy, int sw, int sh ) {
  DrawPartial( image, x - (image->w / 2), y - (image->h / 2), sx, sy, sw, sh );
}

void cImage::DrawPartial( SDL_Surface *s, int x, int y, int sx, int sy, int sw, int sh ) {
  SDL_Rect src, dest;
  cVideo *video = cVideo::Instance();

  src.x = sx;
  src.y = sy;
  src.w = sw;
  src.h = sh;
  dest.x = x;
  dest.y = y;
  dest.w = src.w;
  dest.h = src.h;

  SDL_BlitSurface( s, &src, video->GetScreen(), &dest );
}
