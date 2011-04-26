#include "camera.h"
#include "includes.h"
#include "video.h"

Camera *Camera::pInstance = 0;

Camera *Camera::Instance( void ) {

	if( pInstance == 0 ) {
		pInstance = new Camera;
	}

	return( pInstance );
}

Camera::Camera( void ) {
	x = 0;
	y = 0;
	dx = 0;
	dy = 0;
	ang = 0.;

	following = NULL;
}

void Camera::Look( int x, int y ) {

}

bool Camera::Follow( Sprite *sprite ) {

	following = sprite;

	return( true );
}

void Camera::Update( void ) {
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

void Camera::GetDelta( float *dx, float *dy ) {
	*dx = this->dx;
	*dy = this->dy;
}

void Camera::WorldtoScreen( float x, float y, int *sx, int *sy ) {
	Video *video = Video::Instance();
	
	*sx = (int)(x - this->x) + (video->GetWidth() / 2);
	*sy = (int)(y - this->y) + (video->GetHeight() / 2);
}

void Camera::SetAngle( float ang ) {
	this->ang = ang;
}

float Camera::GetAngle( void ) {
	return( ang + 1.57 );
}
