#include "ammo.h"
#include "camera.h"
#include "sprite_list.h"
#include "timer.h"
#include "trig.h"
#include "video.h"

cAmmo::cAmmo( cSprite *owner, float x, float y, float ang ) {
	cTimer *timer = cTimer::Instance();
	
	image = new cImage( "data/laser1.png" );
	
	this->x = x + cos( ang ) * 15.;
	this->y = y - sin( ang ) * 15.;
	this->ang = ang;
	
	throttle = 1.;
	mass = 0.025;
	thrust = 0.05;
	
	this->owner = owner;
	
	creationStamp = timer->GetTicks();
}

void cAmmo::Collision( float severity ) {
	cSpriteList *spriteList = cSpriteList::Instance();
	
	if( !deleteMe ) {
		spriteList->Remove( this );
		deleteMe = true;
	}
}

void cAmmo::Update( float px, float py ) {
	cTimer *timer = cTimer::Instance();
	cSpriteList *spriteList = cSpriteList::Instance();
	
	cSprite::Update( px, py );
	
	thrust = 0.;
	
	if(( creationStamp + 2000 ) < timer->GetTicks()) {
		if( !deleteMe ) {
			spriteList->Remove( this );
			deleteMe = true;
		}
	}
}

void cAmmo::Draw( void ) {
	cVideo *video = cVideo::Instance();
	cTrig *trig = cTrig::Instance();
	cCamera *camera = cCamera::Instance();
	
	if( !video->OutOfBounds( sx, sy ) )
		image->DrawCentered( sx, sy, trig->RadToDeg( camera->GetAngle() - 1.57 ) - trig->RadToDeg( ang ) );
}
