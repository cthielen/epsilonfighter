#ifndef H_SPRITE
#define H_SPRITE

#include "image.h"
#include "vector.h"

class cSprite {
	public:
		cSprite( void );
		cSprite( float x, float y );

		// pass the player's x,y to update in order to calculate rotated coords
		virtual void Update( float px, float py );
		virtual void Draw( void );
	
		// check to see if a colision has occured
		virtual void CheckCollision( cSprite &sprite );
		// this sprite has been involved in a collision
		virtual void Collision( float severity ) = 0;
	
		void SetMass( float mass );
		float GetMass( void );
		void SetThrust( float thrust );

		bool SetImage( cImage *image );
		SDL_Surface *GetImage( float angOverride );
		SDL_Surface *GetImage( void );
		bitmask *GetBitmask( float angOverride );
		bitmask *GetBitmask( void );

		float GetX( void );
		float GetY( void );
		int GetScreenX( void );
		int GetScreenY( void );
		vector2D GetVelocity( void );
	
		void SetAngle( float ang );
		float GetAngle( void );
		
		Uint32 GetBlipClr( void );
		
		bool Delete( void );

	protected:
		// radar blip color
		Uint32 radarBlip;
	
		bool deleteMe; // set to true if this sprite needs to be deleted
	
		// coords
		float x, y;
		float rx, ry; // rotated world coord (x,y)
		int sx, sy;
	
		cImage *image;
	
		// physics data
		vector2D velocity;
		float ang;
		float throttle; // percentage thrust to apply
		float mass;
		float thrust; // engine thrust (the f in f=ma)
	
		cSprite *owner; // sprite that created this sprite (most sprites
						// done have this, but ammo, i.e., does
};

#endif // H_SPRITE
