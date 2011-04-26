#ifndef H_FONT
#define H_FONT

#include "afont/afont_sdl.h"

class Font {
 public:
	Font();
	Font( char *filename );
	~Font();

	bool SetFont( char *filename );
	void Render( int x, int y, char *text, ... );
	void SetColor( float r, float g, float b );

 private:
	afont *font; // handle to font
	char *filename; // filename of the loaded font
	float r, g, b; // color of text
};

#endif // H_FONT
