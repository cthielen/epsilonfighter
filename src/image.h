#ifndef H_IMAGE
#define H_IMAGE

#include "bitmask.h"
#include "includes.h"

#define NUM_ROTS 36

class cImage {
	public:
		cImage( );
		cImage( char *filename );
		~cImage( );

		bool Load( char *filename );
		bool Draw( int x, int y );
		bool Draw( int x, int y, int ang );
		bool DrawCentered( int x, int y );
		bool DrawCentered( int x, int y, int ang );
		void DrawPartialCentered( int x, int y, int sx, int sy, int sw, int sh );

		int GetWidth( void );
		int GetHeight( void );

		bitmask *GetBitmask( int ang );
		SDL_Surface *GetImage( int ang );

	private:
		SDL_Surface *image;
		// temporary cache of rotates and their bitmasks
		SDL_Surface *cache[NUM_ROTS];
		bitmask *bcache[NUM_ROTS];
		// record of last access of a cache
		Uint32 cache_access[NUM_ROTS];

		void DrawPartial( SDL_Surface *s, int x, int y, int sx, int sy, int sw, int sh );
};

#endif // H_IMAGE
