#include "ammo.h"
#include "camera.h"
#include "sprite_list.h"
#include "timer.h"
#include "trig.h"
#include "video.h"

Ammo::Ammo( Sprite *owner, float x, float y, float ang ) {
	Timer *timer = Timer::Instance();
	
	image = new Image( "data/laser1.png" );
	
	this->x = x + cos( ang ) * 15.;
	this->y = y - sin( ang ) * 15.;
	this->ang = ang;
	
	throttle = 1.;
	mass = 0.025;
	thrust = 0.05;
	
	this->owner = owner;
	
	creationStamp = timer->GetTicks();
}

void Ammo::Collision( float severity ) {
	SpriteList *spriteList = SpriteList::Instance();
	
	if( !deleteMe ) {
		spriteList->Remove( this );
		deleteMe = true;
	}
}

void Ammo::Update( float px, float py ) {
	Timer *timer = Timer::Instance();
	SpriteList *spriteList = SpriteList::Instance();
	
	Sprite::Update( px, py );
	
	thrust = 0.;
	
	if(( creationStamp + 2000 ) < timer->GetTicks()) {
		if( !deleteMe ) {
			spriteList->Remove( this );
			deleteMe = true;
		}
	}
}

void Ammo::Draw( void ) {
	Video *video = Video::Instance();
	Trig *trig = Trig::Instance();
	Camera *camera = Camera::Instance();
	
	if( !video->OutOfBounds( sx, sy ) )
		image->DrawCentered( sx, sy, trig->RadToDeg( camera->GetAngle() - 1.57 ) - trig->RadToDeg( ang ) );
}
