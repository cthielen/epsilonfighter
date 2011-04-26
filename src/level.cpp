#include "camera.h"
#include "hud.h"
#include "includes.h"
#include "level.h"
#include "ship.h"
#include "sprite_list.h"
#include "starfield.h"
#include "timer.h"
#include "video.h"

Level::Level( int which ) {
	Starfield starfield( 350 );
	Hud hud;
	Timer *timer = Timer::Instance();
	Video *video = Video::Instance();
	SpriteList *spriteList = SpriteList::Instance();
	Ship *player = new Ship(); // the player sprite
	bool quit = false;
	SDL_Event event;

	camera = Camera::Instance();

	camera->Follow( player );

	player->UseAI( false );
	player->IsPlayer( true );

	player->SetThrust( 5. );
	
	// add player
	spriteList->Add( player );

	Ship *test = new Ship( 15, 15 );
	
	spriteList->Add( test );

	if( SDL_Init( SDL_INIT_JOYSTICK ) != 0 )
		cout << "massive joystick error" << endl; // move to an input class

	timer->Reset();
	
	hud.Message( HUD_MSG_COMMAND, "Good morning, pilot." );
	
	while( !quit ) {
		// erase
		video->Blank();

		// update
		// get user input
		while( SDL_PollEvent( &event ) ) {
			switch( event.type ) {
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_JOYAXISMOTION:
					cout << "joystick motion!" << endl;
					if(event.jaxis.which == 0)
						player->Turn( (float)-20 * 0.15f );
					break;
				case SDL_KEYDOWN:
					switch( event.key.keysym.sym ) {
						case SDLK_ESCAPE:
							quit = true;
							break;
						case SDLK_w:
							player->ThrottleUp();
							break;
						case SDLK_s:
							player->ThrottleDown();
							break;
						default:
							break;
					}
					break;
				case SDL_MOUSEMOTION:
					if(( event.motion.xrel ) && ( event.motion.xrel != 160 )) {
						if( abs(event.motion.xrel) > 20 )
							if(event.motion.xrel < 0)
								player->Turn( (float)-20 * 0.15f );
							else
								player->Turn( (float)20 * 0.15f );
						else
							player->Turn( (float)event.motion.xrel * 0.15f );
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if( event.button.button == 1) player->Fire();
					if( event.button.button == 4) player->ThrottleUp();
					if( event.button.button == 5) player->ThrottleDown();
					break;
				default:
					break;
			}
		}

		for( int n = timer->GetLoops(); n ; --n ) {
			// update various systems
			camera->Update();
			starfield.Update();
			spriteList->Update();
			hud.Update();
		}

		// draw
		starfield.Draw();
		spriteList->Draw();
		hud.Draw();

		video->Update();

		timer->Delay();
	}
}
