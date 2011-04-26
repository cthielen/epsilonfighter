#include "audio.h"
#include "briefing.h"
#include "image.h"
#include "includes.h"
#include "level.h"
#include "menu.h"
#include "trig.h"
#include "video.h"

#define NUM_STARS 300

void menu( void ) {
	Image presents( "data/presents.png" );
	Image title( "data/title.png" );
	Image menu( "data/menu.png" );
	Image rageful( "data/rageful.png" );
	Video *video = Video::Instance();
	Trig *trig = Trig::Instance();
	Audio *audio = Audio::Instance();
	int cx, cy; // center of screen

	Uint32 end_time;
	struct {
		double x, y;
		Uint32 clr;
		int ang;
	} stars[NUM_STARS];
	int i;

	cx = video->GetWidth() / 2;
	cy = video->GetHeight() / 2;

	// start the march music
	audio->Play( 0 );

	for( i = 0; i < NUM_STARS; i++ ) {
		stars[i].ang = rand() % 360;

		stars[i].x = cx;
		stars[i].y = cy;

		// give the star a random starting position to avoid a
		// bursting effect
		stars[i].x += (int)((float)(rand() % 75) * trig->GetCos( stars[i].ang ));
		stars[i].y -= (int)((float)(rand() % 75) * trig->GetSin( stars[i].ang ));

		stars[i].clr = video->RGBtoClr( 0, 0, rand() % 256 );
	}

	end_time = SDL_GetTicks() + 3300; // 3.3s

	// do the "Little Rage Presents" text with the flying stars
	while( SDL_GetTicks() < end_time ) {
		video->Blank();

		// update the stars
		for( i = 0; i < NUM_STARS; i++ ) {
			stars[i].x += 1.7f * trig->GetCos( stars[i].ang );
			stars[i].y -= 1.7f * trig->GetSin( stars[i].ang );

			if( video->OutOfBounds( (int)stars[i].x, (int)stars[i].y ) ) {
				// star has gone offscreen
				stars[i].x = cx;
				stars[i].y = cy;
			}
		}

		// draw the stars
		for( i = 0; i < NUM_STARS; i++ ) {
			video->DrawPixel( (int)stars[i].x, (int)stars[i].y, stars[i].clr );
		}

		presents.DrawCentered( video->GetWidth() / 2, video->GetHeight() / 2 );

		video->Update();
		SDL_Delay( 15 );
	}

	end_time = SDL_GetTicks() + 3300; // 3.3s

	// do the "A Rageful 2005 Experiment ..." text with the flying stars
	while( SDL_GetTicks() < end_time ) {
		video->Blank();

		// update the stars
		for( i = 0; i < NUM_STARS; i++ ) {
			stars[i].x += 1.7f * trig->GetCos( stars[i].ang );
			stars[i].y -= 1.7f * trig->GetSin( stars[i].ang );

			if( video->OutOfBounds( (int)stars[i].x, (int)stars[i].y ) ) {
				// star has gone offscreen
				stars[i].x = cx;
				stars[i].y = cy;
			}
		}

		// draw the stars
		for( i = 0; i < NUM_STARS; i++ ) {
			video->DrawPixel( (int)stars[i].x, (int)stars[i].y, stars[i].clr );
		}

		rageful.DrawCentered( video->GetWidth() / 2, video->GetHeight() / 2 );

		video->Update();
		SDL_Delay( 15 );
	}

	end_time = SDL_GetTicks() + 3300; // 3.3s

	// do the title screen image with the flying stars
	while( SDL_GetTicks() < end_time ) {
		video->Blank();

		// update the stars
		for( i = 0; i < NUM_STARS; i++ ) {
			stars[i].x += 1.7f * trig->GetCos( stars[i].ang );
			stars[i].y -= 1.7f * trig->GetSin( stars[i].ang );

			if( video->OutOfBounds( (int)stars[i].x, (int)stars[i].y ) ) {
				// star has gone offscreen
				stars[i].x = cx;
				stars[i].y = cy;
			}
		}

		// draw the stars
		for( i = 0; i < NUM_STARS; i++ ) {
			video->DrawPixel( (int)stars[i].x, (int)stars[i].y, stars[i].clr );
		}

		title.DrawCentered( video->GetWidth() / 2, video->GetHeight() / 2 );

		video->Update();
		SDL_Delay( 15 );
	}

	end_time = SDL_GetTicks() + 3300; // 3.3s

	// do the title screen image with the flying stars
	while( SDL_GetTicks() < end_time ) {
		video->Blank();

		// update the stars
		for( i = 0; i < NUM_STARS; i++ ) {
			stars[i].x += 1.7f * trig->GetCos( stars[i].ang );
			stars[i].y -= 1.7f * trig->GetSin( stars[i].ang );

			if( video->OutOfBounds( (int)stars[i].x, (int)stars[i].y ) ) {
				// star has gone offscreen
				stars[i].x = cx;
				stars[i].y = cy;
			}
		}

		// draw the stars
		for( i = 0; i < NUM_STARS; i++ ) {
			video->DrawPixel( (int)stars[i].x, (int)stars[i].y, stars[i].clr );
		}

		menu.DrawCentered( video->GetWidth() / 2, video->GetHeight() / 2 );

		video->Update();
		SDL_Delay( 15 );
	}

	// do the mission briefing
	Briefing briefing( 1 );

	Level level( 1 );
}
