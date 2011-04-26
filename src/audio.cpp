#include "audio.h"
#include "log.h"

Audio *Audio::pInstance = 0;

Audio::Audio( void ) {

}

Audio *Audio::Instance( void ) {

	if( pInstance == 0 ) {
		pInstance = new Audio;
	}

	return( pInstance );
}

bool Audio::Init( void ) {
	int audio_rate;
	Uint16 audio_format;
	int audio_channels;
	int audio_buffers;
	int audio_volume = MIX_MAX_VOLUME;

	audio_rate = 22050;
	audio_format = AUDIO_S16;
	audio_channels = 2;
	audio_buffers = 4096;

	if( SDL_Init(SDL_INIT_AUDIO) != 0 ) {
		log( logError, "Couldn't initialize SDL sound: %s\n", SDL_GetError() );
		return( false );
	}

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers ) != 0 ) {
		log( logWarning, "Couldn't open audio: %s\n", SDL_GetError() );
		return( false );
	} else {
		Mix_QuerySpec( &audio_rate, &audio_format, &audio_channels );
		log( logMessage, "Opened audio at %d Hz %d bit %s, %d bytes audio buffer\n", audio_rate,
			(audio_format&0xFF),
			(audio_channels > 2) ? "surround" : (audio_channels > 1) ? "stereo" : "mono",
			audio_buffers );
	}

	Mix_VolumeMusic(audio_volume);

	mars = Mix_LoadMUS( "data/mars.ogg" );

	return( true );
}

void Audio::Play( int which ) {
	if( which == 0 )
		Mix_FadeInMusic( mars, 0, 2000);
}

bool Audio::Close( void ) {
	Mix_FreeMusic( mars );
	mars = NULL;

	Mix_CloseAudio();

	return( true );
}
