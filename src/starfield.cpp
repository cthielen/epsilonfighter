#include "camera.h"
#include "includes.h"
#include "starfield.h"
#include "timer.h"
#include "trig.h"
#include "video.h"

cStarfield::cStarfield( int num ) {
	cVideo *video = cVideo::Instance();
	stars = (struct _stars *)malloc( sizeof( struct _stars ) * num );
	int i;

	this->num = num;

	for( i = 0; i < num; i++ ) {
		int c = rand() % 200; // star colors between (0,0,0) and (200,200,200)

		stars[i].x = rand() % (video->GetWidth() + 90) - 45;
		stars[i].y = rand() % (video->GetHeight() + 170) - 85;
		stars[i].clr = video->RGBtoClr( c, c, c );
		stars[i].s = 1.;
	}
}

cStarfield::~cStarfield( void ) {
	free( stars );
}

void cStarfield::Update( void ) {
	float dx, dy;
	cVideo *video = cVideo::Instance();
	cCamera *camera = cCamera::Instance();
	cTrig *trig = cTrig::Instance();
	cTimer *timer = cTimer::Instance();
	int i;
	int w, h;

	w = video->GetWidth();
	h = video->GetHeight();

	// get the change in camera coordinates
	camera->GetDelta( &dx, &dy );

	for( i = 0; i < num; i++ ) {
		stars[i].x += dx * stars[i].s * timer->GetMultiplier();
		stars[i].y += dy * stars[i].s * timer->GetMultiplier();

		while( stars[i].x < -45 ) stars[i].x += (float)w + 45.;
		while( stars[i].x > (w + 45) ) stars[i].x -= (float)w + 45.;
		while( stars[i].y < -85 ) stars[i].y += (float)h + 85.;
		while( stars[i].y > (h + 85) ) stars[i].y -= (float)h + 85.;

		// calculate screen coords (we fake translation so only worry about rotation)
		trig->RotatePoint( stars[i].x, stars[i].y, video->GetWidth() / 2, video->GetHeight() / 2, &stars[i].sx, &stars[i].sy, camera->GetAngle() );
	}
}

void cStarfield::Draw( void ) {
	int i;
	cVideo *video = cVideo::Instance();

	for( i = 0; i < num; i++ ) {
		video->DrawPixel( (int)stars[i].sx, (int)stars[i].sy, stars[i].clr );
	}
}
