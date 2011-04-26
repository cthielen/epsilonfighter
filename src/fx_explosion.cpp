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
	Sprite::Update( px, py );
}

void fxExplosion::Draw( void ) {
	Video *video = Video::Instance();
	Trig *trig = Trig::Instance();
	Camera *camera = Camera::Instance();
	
	//if( !video->OutOfBounds( sx, sy ) )
	//explosion.Draw( sx, sy );
	
	// draw partial image (not the entire strip)
}
