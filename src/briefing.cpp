#include "briefing.h"
#include "font.h"
#include "includes.h"
#include "video.h"

Briefing::Briefing( int which ) {
	Video *video = Video::Instance();
	font.SetFont( "data/font1.af" );

	if( which == 1 ) {
		video->Blank();

		font.Render( 5, 10, " Good morning, pilot. I know you haven't had your coffee yet" );
		font.Render( 5, 20, " but the fate of the universe rests your hands and the" );
		font.Render( 5, 30, " hands of your teammates." );

		font.Render( 5, 50, " Early this morning our colony on Galanti V was attacked" );
		font.Render( 5, 60, " and destroyed in under five minutes." );

		font.Render( 5, 80, " Before their radar was jammed they sent out a recent scan " );
		font.Render( 5, 90, " report that, after analyzing, shows us that whoever ");
		font.Render( 5, 100, " attacked Galanti was using a radar station on the other" );
		font.Render( 5, 110, " side of the galaxy to control their fleet." );

		font.Render( 5, 130, " Your mission is to fly into the enemy's territory, find" );
		font.Render( 5, 140, " the radar station and destroy it." );

		font.Render( 5, 160, " Good luck pilot, may luck be on our side...");

		video->Update();

		SDL_Delay( 5000 );
	}
}
