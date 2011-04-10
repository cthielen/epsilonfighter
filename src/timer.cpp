#include "timer.h"

cTimer *cTimer::pInstance = 0;

cTimer::cTimer( void ) {
	dfps = 30;
	multiplier = 1.;
	loopLen = 1000 / dfps;
	pauseDelay = 0;
}

cTimer *cTimer::Instance( void ) {

	if( pInstance == 0 ) {
		pInstance = new cTimer;
	}

	return( pInstance );
}

void cTimer::SetDesiredFPS( int fps ) {
	dfps = fps;
	loopLen = 1000 / dfps;
}

// returns the number of logic loops to run
int cTimer::GetLoops( void ) {
	Uint32 currentTick = SDL_GetTicks();
	Uint32 dt;
	int loops;
	
	dt = currentTick - lastTick;
	loops = (int)((float)dfps * ((float)dt * 0.001)); // calculate the number of frames to run
	
	lastTick = currentTick;
	
	if( loops == 0 )
		loops++;
	
	multiplier = 1. / (float)loops;
	
	return( loops );
}

void cTimer::Reset( void ) {
	lastTick = SDL_GetTicks();
}

void cTimer::Delay( void ) {
	Uint32 delay;
	
	delay = loopLen - (SDL_GetTicks() - lastTick);
	
	if(delay < 0) delay = 15; // we didn't have extra time (we're running behind)
	
	SDL_Delay( 15 );
}

float cTimer::GetMultiplier( void ) {
	return( multiplier );
}

Uint32 cTimer::GetTicks( void ) {
	return( SDL_GetTicks() - pauseDelay );
}
