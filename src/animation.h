#ifndef H_ANIMATION
#define H_ANIMATION

#include "image.h"
#include "includes.h"

class cAnimation {
 public:
  cAnimation();
  cAnimation( char *filename );
  
  // load a film strip
  bool Load( char *filename );
  // draw the strip centered at screen (x,y)
  void Draw( int cx, int cy );
  // calculates next frame. returns false if animation is over
  bool Update( void );

  // set the length of the animation
  void SetLength( Uint32 len );
  // set the number of frames
  void SetFrames( int num );
  // reset the timer
  void Reset( void );

 private:
  Image *strip;
  Uint32 length;
  Uint32 fps;
  int num; // total number of frames
  int w; // width of a single frame
  Uint32 start;
  int cur;
};

#endif // H_ANIMATION
