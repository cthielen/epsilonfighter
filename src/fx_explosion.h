#ifndef H_EXPLOSION
#define H_EXPLOSION

#include "animation.h"
#include "sprite.h"

class fxExplosion : public Sprite {
	public:
		fxExplosion( void );
	
		void Collision( void );
		void Update( float px, float py );
		void Draw( void );
	
	private:
		cAnimation explosion;
};

#endif // H_EXPLOSION
