#include "camera.h"
#include "includes.h"
#include "video.h"

cCamera *cCamera::pInstance = 0;

cCamera *cCamera::Instance( void ) {

	if( pInstance == 0 ) {
		pInstance = new cCamera;
	}

	return( pInstance );
}

cCamera::cCamera( void ) {
	x = 0;
	y = 0;
	dx = 0;
	dy = 0;
	ang = 0.;

	following = NULL;
}

void cCamera::Look( int x, int y ) {

}

bool cCamera::Follow( cSprite *sprite ) {

	following = sprite;

	return( true );
}

void cCamera::Update( void ) {
	if( following ) {
		float spx, spy;

		spx = following->GetX();
		spy = following->GetY();

		dx = -(spx - x);
		dy = -(spy - y);

		x = spx;
		y = spy;
	}
}

void cCamera::GetDelta( float *dx, float *dy ) {
	*dx = this->dx;
	*dy = this->dy;
}

void cCamera::WorldtoScreen( float x, float y, int *sx, int *sy ) {
	cVideo *video = cVideo::Instance();
	
	*sx = (int)(x - this->x) + (video->GetWidth() / 2);
	*sy = (int)(y - this->y) + (video->GetHeight() / 2);
}

void cCamera::SetAngle( float ang ) {
	this->ang = ang;
}

float cCamera::GetAngle( void ) {
	return( ang + 1.57 );
}
