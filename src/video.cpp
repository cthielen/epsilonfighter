#include "includes.h"
#include "log.h"
#include "video.h"
#include "zoom.h"

Video *Video::pInstance = 0;

Video::Video( void ) {
	screen = NULL;
}

Video *Video::Instance( void ) {

	if( pInstance == 0 ) {
		pInstance = new Video;
	}

	return( pInstance );
}

bool Video::SetWindow( int w, int h, int bpp ) {

	if( SDL_Init( SDL_INIT_VIDEO ) != 0 ) {
		log( logError, "Could not initialize SDL: %s\n", SDL_GetError() );
		return( failure );
	}

	atexit( SDL_Quit );

	window = SDL_SetVideoMode( w, h, bpp, 0 ); //SDL_FULLSCREEN );
	if( !window ) {
		log (logError, "Could not set video mode: %s\n", SDL_GetError() );
		return( failure );
	}

	screen = SDL_CreateRGBSurface( SDL_SWSURFACE, 320, 240, 16, window->format->Rmask, window->format->Gmask, window->format->Bmask, window->format->Amask );
	if( !screen ) {
		log (logError, "Could not create scratch surface: %s\n", SDL_GetError() );
		return( failure );
	}

	// initialize colors
	clrBlack = SDL_MapRGB( screen->format, 0, 0, 0 );
	
	return( true );
}

void Video::Update( void ) {
	scale2x( screen, window );
	
	SDL_Flip( window );
}

int Video::GetWidth( void ) {
	return( screen->w );
}

int Video::GetHeight( void ) {
	return( screen->h );
}

SDL_Surface *Video::GetScreen( void ) {
	return( screen );
}

void Video::Blank( void ) {
	DrawRect( 0, 0, screen->w, screen->h, Video::clrBlack );
}

void Video::DrawRect( int x, int y, int w, int h, Uint32 clr ) {
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_FillRect( screen, &rect, clr );
}

void Video::DrawPixel( int x, int y, Uint32 clr ) {
	Uint8 *p;
	int bpp = screen->format->BytesPerPixel;

	if( OutOfBounds( x, y ) ) return;

	if( SDL_MUSTLOCK( screen ) )
		while( SDL_LockSurface( screen ) != 0 )
			SDL_Delay( 1 );

	p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = clr;
        break;

    case 2:
        *(Uint16 *)p = clr;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (clr >> 16) & 0xff;
            p[1] = (clr >> 8) & 0xff;
            p[2] = clr & 0xff;
        } else {
            p[0] = clr & 0xff;
            p[1] = (clr >> 8) & 0xff;
            p[2] = (clr >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = clr;
        break;
    }

	if( SDL_MUSTLOCK( screen ) )
		SDL_UnlockSurface( screen );
}

Uint32 Video::RGBtoClr( int r, int g, int b ) {
	return( SDL_MapRGB( screen->format, r, g, b ) );
}

bool Video::OutOfBounds( int x, int y ) {
	if( x < 0 )
		return( true );
	if( x > (screen->w - 1) )
		return( true );
	if( y < 0 )
		return( true );
	if( y > (screen->h - 1) )
		return( true );

	return( false );
}
