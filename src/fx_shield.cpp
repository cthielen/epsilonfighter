#include "fx_shield.h"
#include "timer.h"
#include "video.h"

fxShield::fxShield() {
	active = false;
}

void fxShield::Renew( Uint32 length ) {
	Timer *timer = Timer::Instance();
	
	this->length = length;
	start = timer->GetTicks();
	active = true;
}

bool fxShield::IsActive() {
	return( active );
}

void fxShield::Update() {
	Timer *timer = Timer::Instance();
	Uint32 current_time = timer->GetTicks();
	Uint32 time_left = ( start + length ) - current_time;

	if( !active )
		return;

	if( ( signed ) time_left <= 0 )
	{
		active = false;
		return;
	}

	else
	{
		Uint32 half_life = ( length / 2 ) + start;
		alpha = ( ( current_time - start ) * 135 ) / ( length / 2 );
		if( current_time >= half_life )
		{
			if( ( 135 - ( alpha - 135 ) ) < 0 )
				alpha = 0;
			else
				alpha = 135 - ( alpha - 135 );
		}
	}
}

void fxShield::Draw( int x, int y, SDL_Surface *s, bitmask *bm, SDL_Surface *to ) {
	int a, b;
	int pitch_adjust;
	Video *video = Video::Instance();

	if( !active )
		return;

	if( s->format->BitsPerPixel == 32 )
		pitch_adjust = s->pitch / sizeof( Uint32 );
	else if( s->format->BitsPerPixel == 16 )
		pitch_adjust = s->pitch / sizeof( Uint16 );

	if( SDL_MUSTLOCK( to ) )
		while( SDL_LockSurface( to ) == -1 ) SDL_Delay(1);

	if( SDL_MUSTLOCK( s ) )
		while( SDL_LockSurface( s ) == -1 ) SDL_Delay(1);

	/* draw a tv effect on surface 's', only where the bitmask applies */
	for( b = 0; b < s->h; b++ ) {
		for( a = 0; a < s->w; a++ ) {
			/* make sure the mask is on in this area */
			if( bm->bm[a + ( b * bm->w )] ) {
				if (!video->OutOfBounds( a + x, b + y )) {
					unsigned char d = ( rand() % 100 ) + 100;
					unsigned char c;
					int r1, g1, b1, nr, ng, nb;
					Uint32 pixel, npixel;

					/* the random color will be c, c, d (r, g, b) */
					if( ( d - 100 ) < 0 )
						c = 0;
					else
						c = d - 100;

					/* extract current pixel */
					if( s->format->BitsPerPixel == 16 )
						pixel = ( ( Uint16 * ) s->pixels )[a + ( b * pitch_adjust )];
					else if( s->format->BitsPerPixel == 32 )
						pixel = ( ( Uint32 * ) s->pixels )[a + ( b * pitch_adjust )];
					else
						assert( " bpp not covered!" );

					/* extract r,g,b values from pixel */
					r1 = pixel & s->format->Rmask;
					g1 = pixel & s->format->Gmask;
					b1 = pixel & s->format->Bmask;
					r1 >>= s->format->Rshift;
					g1 >>= s->format->Gshift;
					b1 >>= s->format->Bshift;
					r1 <<= s->format->Rloss;
					g1 <<= s->format->Gloss;
					b1 <<= s->format->Bloss;

					/* blend the extracted value w/ the random value (c,c,d in r,g,b) */
					nr = ( c * ( ( float ) alpha / 255.0f ) )
					   + ( r1 * ( ( 255.0f - ( float ) alpha ) / 255.0f ) );
					ng = ( c * ( ( float ) alpha / 255.0f ) )
					   + ( g1 * ( ( 255.0f - ( float ) alpha ) / 255.0f ) );
					nb = ( d * ( ( float ) alpha / 255.0f ) )
					   + ( b1 * ( ( 255.0f - ( float ) alpha ) / 255.0f ) );

					npixel = SDL_MapRGB( to->format, nr, ng, nb );

					/* write back blended pixel */
					if( to->format->BitsPerPixel == 16 )
						( ( Uint16 * ) to->pixels )[a + x + ( ( b + y ) * ( to->pitch / sizeof( Uint16 ) ) )] = npixel;
					else if( s->format->BitsPerPixel == 32 )
						( ( Uint32 * ) to->pixels )[a + x + ( ( b + y ) * ( to->pitch / sizeof( Uint32 ) ) )] = npixel;
				}
			}
		}
	}

	SDL_UnlockSurface( s );
	SDL_UnlockSurface( to );
}
