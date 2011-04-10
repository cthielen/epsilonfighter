#include "camera.h"
#include "fx_explosion.h"
#include "image.h"
#include "trig.h"
#include "video.h"

fxExplosion::fxExplosion( void ) {
	explosion.Load( "data/explosion1.png" );
}

void fxExplosion::Collision( void ) {
	
}

void fxExplosion::Update( float px, float py ) {
	cSprite::Update( px, py );
}

void fxExplosion::Draw( void ) {
	cVideo *video = cVideo::Instance();
	cTrig *trig = cTrig::Instance();
	cCamera *camera = cCamera::Instance();
	
	//if( !video->OutOfBounds( sx, sy ) )
	//explosion.Draw( sx, sy );
	
	// draw partial image (not the entire strip)
}
