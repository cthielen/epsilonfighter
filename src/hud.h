#ifndef H_HUD
#define H_HUD

#include "font.h"
#include "includes.h"

#define MAX_RADAR_RANGE (1500.)

enum msgType {HUD_MSG_NORMAL, HUD_MSG_COMMAND};

class Hud {
	public:
		Hud( void );
	
		void Update( void );
		void Draw( void );
	
		void Message( char *msg );
		void Message( msgType type, char *msg );

	private:
		vector<string> messages;
		vector<enum msgType> messageType;
		vector<Uint32> messageTime; // the delay length of every message

		Font font;
		Image pilot1;
	
		float radarRange; // in game world units
	
		bool OutOfRadarBounds( float x, float y );

};

#endif // H_HUD
