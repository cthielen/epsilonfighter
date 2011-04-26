#ifndef H_VIDEO
#define H_VIDEO

#include "image.h"

class Video {
	public:
		static Video *Instance();

		bool SetWindow( int w, int h, int bpp );

		void Update( void );

		int GetWidth( void );
		int GetHeight( void );

		bool OutOfBounds( int x, int y );

		SDL_Surface *GetScreen( void );

		void Blank( void );

		void DrawRect( int x, int y, int w, int h, Uint32 clr );
		void DrawPixel( int x, int y, Uint32 clr );
		Uint32 RGBtoClr( int r, int g, int b );

		Uint32 clrBlack;

	protected:
		Video();
		Video( const Video & );
  		Video& operator= (const Video&);

  	private:
		static Video *pInstance;

		SDL_Surface *screen, *window; // screen we draw to, window is the actual window we flip
		int pxMul; // pixel multipler for DrawPixel
};

#endif // H_VIDEO
