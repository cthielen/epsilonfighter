#include "timer.h"

Timer *Timer::pInstance = 0;

Timer::Timer( void ) {
	dfps = 30;
	multiplier = 1.;
	loopLen = 1000 / dfps;
	pauseDelay = 0;
}

Timer *Timer::Instance( void ) {

	if( pInstance == 0 ) {
		pInstance = new Timer;
	}

	return( pInstance );
}

void Timer::SetDesiredFPS( int fps ) {
	dfps = fps;
	loopLen = 1000 / dfps;
}

// returns the number of logic loops to run
int Timer::GetLoops( void ) {
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

void Timer::Reset( void ) {
	lastTick = SDL_GetTicks();
}

void Timer::Delay( void ) {
	Uint32 delay;
	
	delay = loopLen - (SDL_GetTicks() - lastTick);
	
	if(delay < 0) delay = 15; // we didn't have extra time (we're running behind)
	
	SDL_Delay( 15 );
}

float Timer::GetMultiplier( void ) {
	return( multiplier );
}

Uint32 Timer::GetTicks( void ) {
	return( SDL_GetTicks() - pauseDelay );
}
