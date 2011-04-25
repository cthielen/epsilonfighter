#include "camera.h"
#include "font.h"
#include "hud.h"
#include "includes.h"
#include "sprite_list.h"
#include "video.h"

cHud::cHud( void ) {
	font.SetFont( "data/font1.af" );
	pilot1.Load( "data/pilot1.png" );
	
	// ratio used in converting real world game coords to radar blips
	radarRange = 50. / MAX_RADAR_RANGE;
}

void cHud::Update( void ) {

}

void cHud::Draw( void ) {
	cVideo *video = cVideo::Instance();
	cSpriteList *spriteList = cSpriteList::Instance();
	int tx, ty;
	
	// draw hud messages
	if( messages.size() > 0 ) {
		if( messageType[0] == HUD_MSG_COMMAND ) {
			pilot1.Draw( 5, video->GetHeight() - pilot1.GetHeight() - 5 );
			tx = 10 + pilot1.GetWidth();
			ty = video->GetHeight() - pilot1.GetHeight() - 5;
			font.Render( tx, ty, "Command:" );
			ty += 10;
		}
		
		font.Render( tx, ty, (char *)messages[0].c_str() );
	}
	
	// draw radar
	video->DrawRect( (video->GetWidth() / 2) - 25, video->GetHeight() - 55, 50, 50, video->RGBtoClr( 0, 0, 100 ) );
	// draw the radar blips
	list<cSprite *>::iterator i = spriteList->Enumerate();
        
	while( i != (list<cSprite *>::iterator)NULL ) {
		float x, y;
		cSprite *sprite;
		
		sprite = spriteList->Retrieve( i );
		
		x = sprite->GetScreenX() - (video->GetWidth() / 2);
		y = sprite->GetScreenY() - (video->GetHeight() / 2);
		
		x *= radarRange;
		y *= radarRange;
		
		// center coord on the radar`
		x += (video->GetWidth() / 2);
		y += video->GetHeight() - 30;
		
		if( !OutOfRadarBounds( x, y ) )
			video->DrawPixel( (int)x, (int)y, sprite->GetBlipClr() );
		
		i = spriteList->Enumerate( i );
	}
}

void cHud::Message( char *msg ) {
	Message( HUD_MSG_NORMAL, msg );
}

void cHud::Message( msgType type, char *msg ) {
	messages.push_back( msg );
	messageType.push_back( type );
	messageTime.push_back( 3000 );
}

// ensures (x,y) is on graphical radar
bool cHud::OutOfRadarBounds( float x, float y ) {
	cVideo *video = cVideo::Instance();
	
	if( x < ((video->GetWidth() / 2) - 25) )
		return( true );
	if( y < (video->GetHeight() - 55) )
		return( true );
	if( x > ((video->GetWidth() / 2) - 25) + 50 )
		return( true );
	if( y > (video->GetHeight() - 55) + 50 )
		return( true );
	
	return( false );
}
