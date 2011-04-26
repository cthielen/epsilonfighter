#include "audio.h"
#include "includes.h"
#include "level.h"
#include "log.h"
#include "menu.h"
#include "video.h"

int main( int argc, char **argv ) {
	Video *video = Video::Instance();
	Audio *audio = Audio::Instance();

	log( logMessage, "Epsilon Fighter v%d.%d.%d starting ...",
		VERSION_MAJOR, VERSION_MINOR, VERSION_MICRO );

	video->SetWindow( 640, 480, 16 );
	audio->Init();

	SDL_ShowCursor( 0 );

	if( argc > 1) {
		if( !strcmp( argv[1], "--debug" ) ) {
			Level level( 1 );
		} else
			menu();
	} else {
		menu();
	}

	log( logMessage, "Epsilon Fighter shutting down ..." );

	audio->Close();

	SDL_ShowCursor( 1 );

	return( success );
}
