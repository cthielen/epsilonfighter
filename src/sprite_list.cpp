#include "camera.h"
#include "includes.h"
#include "sprite_list.h"

SpriteList *SpriteList::pInstance = 0;

SpriteList *SpriteList::Instance( void ) {

	if( pInstance == 0 ) {
		pInstance = new SpriteList;
	}

	return( pInstance );
}

SpriteList::SpriteList( void ) {

}

void SpriteList::Update( void ) {
	float dx, dy;
	Camera *camera = Camera::Instance();
	list<Sprite *>::iterator i, j, player, end( sprites.end() );

	camera->GetDelta( &dx, &dy );
	
	for( player = i = sprites.begin(); i != sprites.end(); ++i ) {
		// update sprite coordinates
		(*i)->Update( (*player)->GetX(), (*player)->GetY() );
		
		// check for collisions between sprites by going through all the
		// sprites and seeing if they overlap
		for( j = sprites.begin(); j != sprites.end(); ++j ) {
			// dont check for collision against the current sprite
			if( i != j ) {
				(*i)->CheckCollision( *(*j) );
			}
		}
	}
	
	// check the removal list. if any sprites "died" in their update, we couldnt
	// remove them in the above because it would throw off the iterator
	for( i = removeList.begin(); i != removeList.end(); ++i ) {
		// look for the sprite to be removed (*i) in the sprite list (*j)
		for( j = sprites.begin(); j != sprites.end(); ++j ) {
			if( (*i) == (*j) ) {
				if( (*j)->NeedsDelete() ) {
					delete *j;
					sprites.erase( j );
				}
				break;
			}
		}
	}
	
	// empty the removeList
	removeList.erase( removeList.begin(), removeList.end() );
}

void SpriteList::Draw( void ) {
	list<Sprite *>::iterator i;

	for( i = sprites.begin(); i != sprites.end(); ++i ) {
		(*i)->Draw();
	}
}

bool SpriteList::Add( Sprite *sprite ) {
	sprites.push_back( sprite );
		
	return( true );
}

bool SpriteList::Remove( Sprite *sprite ) {
	list<Sprite *>::iterator i;

	for( i = sprites.begin(); i != sprites.end(); ++i ) {
		if( *i == sprite ) {
			//sprites.erase( i );
			removeList.push_back( sprite );
			return( true );
		}
	}

	return( false );
}

// NEVER keep this iterator after your function ends. the moment the list
// changes, the iterator is invalid and using it could crash the game
list<Sprite *>::iterator SpriteList::Enumerate( void ) {
	list<Sprite *>::iterator i = sprites.begin();
	
	return( i );
}

list<Sprite *>::iterator SpriteList::EnumerationEnd( void ) {
	return sprites.end();
}

list<Sprite *>::iterator SpriteList::Enumerate( list<Sprite *>::iterator i ) {
	i++;
	
	return( i );
}

Sprite *SpriteList::Retrieve( list<Sprite *>::iterator i ) {
	return( *i );
}
