#ifndef H_AMMO
#define H_AMMO

#include "sprite.h"

class cAmmo : public cSprite {
	public:
		cAmmo( cSprite *owner, float x, float y, float ang );
		
		void Collision( float severity );
		void Update( float px, float py );
		void Draw( void );

	private:
		Uint32 creationStamp;
};

#endif // H_AMMO
