#ifndef H_SHIP
#define H_SHIP

#include "fx_shield.h"
#include "sprite.h"
#include "weapon.h"

class cShip : public cSprite {
	public:
		cShip();
		cShip( float x, float y );
	
		void Update( float px, float py );
		void Draw( void );
		void Collision( float severity );
	
		void UseAI( bool useAI );
		void IsPlayer( bool isPlayer );
		bool GetIsPlayer( void );
	
		void Turn( float ang );
		void ThrottleUp( void );
		void ThrottleDown( void );
		void Fire( void );

	private:
		bool useAI;
		bool isPlayer;

		float shieldStrength, hullStrength;
	
		cWeapon weapon;
	
		fxShield flare; // the shield flare eye candy
};

#endif // H_SHIP
