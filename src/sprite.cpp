#include "bitmask.h"
#include "camera.h"
#include "includes.h"
#include "level.h"
#include "sprite.h"
#include "timer.h"
#include "trig.h"
#include "vector.h"
#include "video.h"

cSprite::cSprite( void ) {
	cVideo *video = cVideo::Instance();
	
	x = 0.;
	y = 0.;
	mass = 1.;

	ang = 0.;
	throttle = 0.;
	thrust = 2.;
	
	radarBlip = video->RGBtoClr( 255, 255, 255 );
	
	deleteMe = false;
	
	owner = NULL;
}

cSprite::cSprite( float x, float y ) {
	cVideo *video = cVideo::Instance();
	
	this->x = x;
	this->y = y;
	mass = 1.;

	ang = 0.;
	throttle = 0.;
	thrust = 2.;
	
	radarBlip = video->RGBtoClr( 255, 255, 255 );
	
	deleteMe = false;
	
	owner = NULL;
}

void cSprite::Update( float px, float py ) {
	cTimer *timer = cTimer::Instance();
	cTrig *trig = cTrig::Instance();
	cCamera *camera = cCamera::Instance();
	float a;
	int sx, sy;
	vector2D accel;
	
	/* -= the arcade way to do it =-
	a = (throttle * thrust) / mass;
	
	x += cos( ang ) * a * timer->GetMultiplier();
	y -= sin( ang ) * a * timer->GetMultiplier();
	*/
	
	a = (throttle * thrust) / mass;
	accel.Set( cos( ang ) * a, -sin( ang ) * a );

	velocity = velocity + (accel * timer->GetMultiplier());
	
	x += velocity.GetX();
	y += velocity.GetY();
	
	trig->RotatePoint( x, y, px, py, &rx, &ry, camera->GetAngle() );
	camera->WorldtoScreen( rx, ry, &sx, &sy );

	this->sx = sx;
	this->sy = sy;
}

void cSprite::Draw( void ) {
	cVideo *video = cVideo::Instance();
	cTrig *trig = cTrig::Instance();
	cCamera *camera = cCamera::Instance();
	
	if( !video->OutOfBounds( sx, sy ) )
		image->DrawCentered( sx, sy, trig->RadToDeg( ang ) - trig->RadToDeg( (1.57 - camera->GetAngle() ) ) );
}

bool cSprite::SetImage( cImage *image ) {
	this->image = image;

	return( true );
}

float cSprite::GetX( void ) {
	return( x );
}

float cSprite::GetY( void ) {
	return( y );
}

void cSprite::SetAngle( float ang ) {
	this->ang = ang;
}

// check for collision between 'this' sprite and sprite
void cSprite::CheckCollision( cSprite &sprite ) {
	int c;
	
	c = CalculateCollision( GetBitmask(), sprite.GetBitmask(), (int)(sprite.GetX() - x), (int)(sprite.GetY() - y) );
	
	if( c ) {
		if(( &sprite != owner ) && (sprite.owner != this)) { // we can't collide with our owner
			// a collision has occured
			// modify the velocities
			float avx, avy, bvx, bvy;
			// the kinetic energies of the collision
			float ke_him = .5 * sprite.GetMass() * (sprite.velocity.GetMagnitude() * sprite.velocity.GetMagnitude());
			float ke_us = .5 * mass * (velocity.GetMagnitude() * velocity.GetMagnitude());
			
			avx = sprite.velocity.GetX();
			avy = sprite.velocity.GetY();
		
			bvx = velocity.GetX();
			bvy = velocity.GetY();

			// calculate new velocities
			avx = (velocity.GetX() * (( 2. * mass ) / ( sprite.GetMass() + mass ) )) - (sprite.velocity.GetX() * (( mass - sprite.GetMass() )/( sprite.GetMass() + mass )));
			avy = (velocity.GetY() * (( 2. * mass ) / ( sprite.GetMass() + mass ) )) - (sprite.velocity.GetY() * (( mass - sprite.GetMass() )/( sprite.GetMass() + mass )));
		
			bvx = (sprite.velocity.GetX() * (( 2. * sprite.GetMass() ) / ( sprite.GetMass() + mass ) )) - (velocity.GetX() * (( sprite.GetMass() - mass )/( sprite.GetMass() + mass )));
			bvy = (sprite.velocity.GetY() * (( 2. * sprite.GetMass() ) / ( sprite.GetMass() + mass ) )) - (velocity.GetY() * (( sprite.GetMass() - mass )/( sprite.GetMass() + mass )));

			velocity.Set( bvx, bvy );
			sprite.velocity.Set( avx, avy );
		
			// until debugged
			ke_him = 1.;
			ke_us = 1.;
		
			// call the sprite-child's specific collision code
			Collision( ke_him );
			// and the other's collision code
			sprite.Collision( ke_us );
		}
	}
}

bitmask *cSprite::GetBitmask( float angOverride ) {
	cTrig *trig = cTrig::Instance();
	
	return( image->GetBitmask( trig->RadToDeg( angOverride ) ) );
}

void cSprite::SetMass( float mass ) {
	this->mass = mass;
}

void cSprite::SetThrust( float thrust ) {
	this->thrust = thrust;
}

SDL_Surface *cSprite::GetImage( float angOverride ) {
	cTrig *trig = cTrig::Instance();

	return( image->GetImage( trig->RadToDeg( angOverride ) ) );
}

SDL_Surface *cSprite::GetImage( void ) {
	cCamera *camera = cCamera::Instance();
	
	return( GetImage( ang + (camera->GetAngle() - 1.57) ) );
}

bitmask *cSprite::GetBitmask( void ) {
	cCamera *camera = cCamera::Instance();

	return( GetBitmask( ang + (camera->GetAngle() - 1.57) ) );
}

float cSprite::GetMass( void ) {
	return( mass );
}

vector2D cSprite::GetVelocity( void ) {
	return( velocity );
}

float cSprite::GetAngle( void ) {
	return( ang );
}

int cSprite::GetScreenX( void ) {
	return( sx );
}

int cSprite::GetScreenY( void ) {
	return( sy );
}

Uint32 cSprite::GetBlipClr( void ) {
	return( radarBlip );
}

bool cSprite::NeedsDelete( void ) {
	return( deleteMe );
}
