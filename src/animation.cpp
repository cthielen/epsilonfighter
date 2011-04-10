#include "animation.h"
#include "timer.h"

cAnimation::cAnimation() {
  cTimer *timer = cTimer::Instance();

  strip = NULL;
  length = 0;
  fps = 0;
  cur = 0;
  start = timer->GetTicks();
}

cAnimation::cAnimation( char *filename ) {
  cTimer *timer = cTimer::Instance();

  strip = NULL;
  length = 0;
  fps = 0;
  cur = 0;
  start = timer->GetTicks();

  Load( filename );
}

bool cAnimation::Load( char *filename ) {
  strip = new cImage();

  return( strip->Load( filename ) );
}

void cAnimation::SetLength( Uint32 len ) {
  length = len;
}

void cAnimation::SetFrames( int num ) {
  this->num = num;
  w = strip->GetWidth() / num;
}

void cAnimation::Reset( void ) {
  cTimer *timer = cTimer::Instance();

  start = timer->GetTicks();
}

// draw animation centered at (cx, cy)
void cAnimation::Draw( int cx, int cy ) {
  strip->DrawPartialCentered( cx, cy, cur * w, 0, w, strip->GetHeight() );
}

// calculates next frame. returns false if animation is over
bool cAnimation::Update( void ) {
  cTimer *timer = cTimer::Instance();

  
}
