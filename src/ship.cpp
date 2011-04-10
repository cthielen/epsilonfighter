#include "camera.h"
#include "includes.h"
#include "ship.h"
#include "sprite_list.h"
#include "trig.h"
#include "video.h"

cShip::cShip() {
	useAI = true;
	isPlayer = false;
	weapon.SetType( WLASER );
	
	image = new cImage( "data/player.png" );
	
	mass = 100.;

	shieldStrength = 10.;
	hullStrength = 10.;
}

cShip::cShip( float x, float y ) {
	useAI = true;
	isPlayer = false;
	
	this->x = x;
	this->y = y;
	weapon.SetType( WLASER );
	
	image = new cImage( "data/player.png" );
	
	mass = 100.;

	shieldStrength = 10.;
	hullStrength = 10.;
}

void cShip::UseAI( bool useAI ) {
	this->useAI = useAI;
}

void cShip::IsPlayer( bool isPlayer ) {
	cVideo *video = cVideo::Instance();
	
	this->isPlayer = isPlayer;
	
	sx = (video->GetWidth() / 2);
	sy = (video->GetHeight() / 2);
}

bool cShip::GetIsPlayer( void ) {
	return( isPlayer );
}

void cShip::Turn( float ang ) {
	cTrig *trig = cTrig::Instance();

	this->ang += trig->DegToRad( (double)ang );

	if( isPlayer ) {
		cCamera *camera = cCamera::Instance();

		camera->SetAngle( this->ang );
	}
}

void cShip::ThrottleUp( void ) {
	throttle += .1;
	
	if( throttle > 1. )
		throttle = 1.;
}

void cShip::ThrottleDown( void ) {
	throttle -= .1;
	
	if( throttle < 0. )
		throttle = 0.;
}

void cShip::Fire( void ) {
	weapon.Fire( this );
}

void cShip::Update( float px, float py ) {
	cSprite::Update( px, py );
	
	flare.Update();
}

void cShip::Draw( void ) {
	cVideo *video = cVideo::Instance();

	if( isPlayer)
		image->DrawCentered( video->GetWidth() / 2, video->GetHeight() / 2 );
	else
		cSprite::Draw();
	if( isPlayer )
		flare.Draw( sx - (image->GetWidth() / 2), sy - (image->GetHeight() / 2), GetImage( 0 ), GetBitmask( 0 ), video->GetScreen() );
	else
		flare.Draw( sx - (image->GetWidth() / 2), sy - (image->GetHeight() / 2), GetImage(), GetBitmask(), video->GetScreen() );
}

void cShip::Collision( float severity ) {
	flare.Renew( 750 );
	
	if( shieldStrength > 0. ) {
		shieldStrength -= severity;
		if( shieldStrength < 0. )
			hullStrength += shieldStrength; // the negative part of the shield goes to the hull
	} else
		hullStrength -= severity;
	
	// we're dead
	if( hullStrength < 0. ) {
		cSpriteList *spriteList = cSpriteList::Instance();
		
		if( !deleteMe ) {
			spriteList->Remove( this );
			deleteMe = true;
		}
	}
}
