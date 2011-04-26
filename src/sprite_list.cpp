#include "camera.h"
#include "includes.h"
#include "sprite_list.h"

cSpriteList *cSpriteList::pInstance = 0;

cSpriteList *cSpriteList::Instance( void ) {

	if( pInstance == 0 ) {
		pInstance = new cSpriteList;
	}

	return( pInstance );
}

cSpriteList::cSpriteList( void ) {

}

void cSpriteList::Update( void ) {
	float dx, dy;
	cCamera *camera = cCamera::Instance();
	list<cSprite *>::iterator i, j, player, end( sprites.end() );

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
				//if( (*j)->NeedsDelete() )
					//delete *j;
				sprites.erase( j );
				break;
			}
		}
	}
	
	removeList.erase( removeList.begin(), removeList.end() );
}

void cSpriteList::Draw( void ) {
	list<cSprite *>::iterator i;

	for( i = sprites.begin(); i != sprites.end(); ++i ) {
		(*i)->Draw();
	}
}

bool cSpriteList::Add( cSprite *sprite ) {

	sprites.push_back( sprite );
		
	return( true );
}

bool cSpriteList::Remove( cSprite *sprite ) {
	list<cSprite *>::iterator i;

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
list<cSprite *>::iterator cSpriteList::Enumerate( void ) {
	list<cSprite *>::iterator i = sprites.begin();
	
	return( i );
}

list<cSprite *>::iterator cSpriteList::Enumerate( list<cSprite *>::iterator i ) {
	i++;
	
	if( i == sprites.end() )
		return( (list<cSprite *>::iterator)NULL );
	
	return( i );
}

cSprite *cSpriteList::Retrieve( list<cSprite *>::iterator i ) {
	return( *i );
}
