#ifndef H_SPRITE_LIST
#define H_SPRITE_LIST

#include "image.h"
#include "sprite.h"

class cSpriteList {
	public:
		static cSpriteList *Instance();

		void Update( void );
		void Draw( void );

		bool Add( cSprite *sprite );
		bool Remove( cSprite *sprite );

		// enumation - allows non-cSpriteList functions to parse the sprite list
		list<cSprite *>::iterator Enumerate( void );
		list<cSprite *>::iterator Enumerate( list<cSprite *>::iterator i );
		cSprite *Retrieve( list<cSprite *>::iterator i );
	
	protected:
		cSpriteList( void );
		cSpriteList( const cSpriteList & );
  		cSpriteList& operator= (const cSpriteList&);
	
	private:
		static cSpriteList *pInstance;
	
		list<cSprite *> sprites;
		list<cSprite *> removeList; // list of sprites to delete
};

#endif // H_SPRITE_LIST
