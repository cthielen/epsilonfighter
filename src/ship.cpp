#include "camera.h"
#include "includes.h"
#include "ship.h"
#include "sprite_list.h"
#include "trig.h"
#include "video.h"

Ship::Ship() {
	useAI = true;
	isPlayer = false;
	weapon.SetType( WLASER );
	
	image = new Image( "data/player.png" );
	
	mass = 100.;

	shieldStrength = 10.;
	hullStrength = 10.;
}

Ship::Ship( float x, float y ) {
	useAI = true;
	isPlayer = false;
	
	this->x = x;
	this->y = y;
	weapon.SetType( WLASER );
	
	image = new Image( "data/player.png" );
	
	mass = 100.;

	shieldStrength = 10.;
	hullStrength = 10.;
}

void Ship::UseAI( bool useAI ) {
	this->useAI = useAI;
}

void Ship::IsPlayer( bool isPlayer ) {
	Video *video = Video::Instance();
	
	this->isPlayer = isPlayer;
	
	sx = (video->GetWidth() / 2);
	sy = (video->GetHeight() / 2);
}

bool Ship::GetIsPlayer( void ) {
	return( isPlayer );
}

void Ship::Turn( float ang ) {
	Trig *trig = Trig::Instance();

	this->ang += trig->DegToRad( (double)ang );

	if( isPlayer ) {
		Camera *camera = Camera::Instance();

		camera->SetAngle( this->ang );
	}
}

void Ship::ThrottleUp( void ) {
	throttle += .1;
	
	if( throttle > 1. )
		throttle = 1.;
}

void Ship::ThrottleDown( void ) {
	throttle -= .1;
	
	if( throttle < 0. )
		throttle = 0.;
}

void Ship::Fire( void ) {
	weapon.Fire( this );
}

void Ship::Update( float px, float py ) {
	Sprite::Update( px, py );
	
	flare.Update();
}

void Ship::Draw( void ) {
	Video *video = Video::Instance();

	if( isPlayer)
		image->DrawCentered( video->GetWidth() / 2, video->GetHeight() / 2 );
	else
		Sprite::Draw();
	if( isPlayer )
		flare.Draw( sx - (image->GetWidth() / 2), sy - (image->GetHeight() / 2), GetImage( 0 ), GetBitmask( 0 ), video->GetScreen() );
	else
		flare.Draw( sx - (image->GetWidth() / 2), sy - (image->GetHeight() / 2), GetImage(), GetBitmask(), video->GetScreen() );
}

void Ship::Collision( float severity ) {
	flare.Renew( 750 );
	
	if( shieldStrength > 0. ) {
		shieldStrength -= severity;
		if( shieldStrength < 0. )
			hullStrength += shieldStrength; // the negative part of the shield goes to the hull
	} else
		hullStrength -= severity;
	
	// we're dead
	if( hullStrength < 0. ) {
		SpriteList *spriteList = SpriteList::Instance();
		
		if( !deleteMe ) {
			spriteList->Remove( this );
			deleteMe = true;
		}
	}
}
