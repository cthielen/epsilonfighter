#ifndef H_SPRITE_LIST
#define H_SPRITE_LIST

#include "image.h"
#include "sprite.h"

class SpriteList {
	public:
		static SpriteList *Instance();

		void Update( void );
		void Draw( void );

		bool Add( Sprite *sprite );
		bool Remove( Sprite *sprite );

		// enumation - allows non-SpriteList functions to parse the sprite list
		list<Sprite *>::iterator Enumerate( void );
		list<Sprite *>::iterator Enumerate( list<Sprite *>::iterator i );
		list<Sprite *>::iterator EnumerationEnd( void );
		Sprite *Retrieve( list<Sprite *>::iterator i );
	
	protected:
		SpriteList( void );
		SpriteList( const SpriteList & );
  		SpriteList& operator= (const SpriteList&);
	
	private:
		static SpriteList *pInstance;
	
		list<Sprite *> sprites;
		list<Sprite *> removeList; // list of sprites to delete
};

#endif // H_SPRITE_LIST
