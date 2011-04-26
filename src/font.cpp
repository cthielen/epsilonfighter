#include "afont/afont_sdl.h"
#include "font.h"
#include "includes.h"
#include "log.h"
#include "video.h"

Font::Font() {
	font = NULL;
	filename = NULL;

	r = 1.0f;
	g = 1.0f;
	b = 1.0f;
}

Font::Font( char *filename ) {
	font = NULL;
	this->filename = NULL;

	r = 1.0f;
	g = 1.0f;
	b = 1.0f;

	SetFont( filename );
}

Font::~Font() {
	afont_free( font );

	log( logMessage, "Font '%s' freed.", filename );

	free( filename );
}

bool Font::SetFont( char *filename ) {
	font = afont_load( filename );

	if( font == NULL ) {
		log( logError, "Failed to load font '%s'.", filename );
		return( false );
	}

	this->filename = strdup( filename );

	log( logMessage, "Font '%s' loaded.", filename );

	return( true );
}

void Font::Render( int x, int y, char *text, ... ) {
	Video *video = Video::Instance();
	char string[100] = {0};
	va_list args;
	int w, h, base;
	
	va_start( args, text );
	vsnprintf( string, 99, text, args );
	va_end( args );

	// calculate base
	afont_size_text( font, string, &w, &h, &base );
	
	afont_render_text( font, 0x50ff50, 0x000000ff, AFONT_RENDER_SHADED,
	                video->GetScreen(), x, y + base, string );
}

void Font::SetColor( float r, float g, float b ) {
	this->r = r;
	this->g = g;
	this->b = b;
}
