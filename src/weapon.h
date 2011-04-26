#ifndef H_WEAPON
#define H_WEAPON

#include "ammo.h"
#include "sprite.h"

enum weaponType { WNONE, WLASER, WLASER2, WMISSILE, WBOMB, WRAY };

class Weapon {
	public:
		Weapon();
		Weapon( weaponType type );
	
		void SetType( weaponType type );
		void Fire( Sprite *owner );

	private:
		Uint32 rechargeDelay;
		Uint32 lastFire;
		enum weaponType type;
};

#endif // H_WEAPON
