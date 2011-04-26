#ifndef H_FX_SHIELD
#define H_FX_SHIELD

#include "bitmask.h"
#include "includes.h"

class fxShield {
	public:
		fxShield();

		void Renew( Uint32 length );
		void Update();
		void Draw( int x, int y, SDL_Surface *s, bitmask *bm, SDL_Surface *to );
		bool IsActive();

	private:
		Uint32 length, start;
		unsigned char alpha;
		bool active;
};

#endif /* H_FX_SHIELD */
