#include "includes.h"
#include "sprite_list.h"
#include "timer.h"
#include "vector.h"
#include "weapon.h"

Weapon::Weapon() {
	SetType( WNONE );
	lastFire = 0;
}

Weapon::Weapon( weaponType type ) {
	SetType( type );
	lastFire = 0;
}

void Weapon::SetType( weaponType type ) {
	this->type = type;
	
	switch( type ) {
		case WNONE:
			rechargeDelay = 0;
			break;
		case WLASER:
			rechargeDelay = 50;
			break;
		case WLASER2:
			rechargeDelay = 15;
			break;
	}
}

void Weapon::Fire( Sprite *owner ) {
	Timer *timer = Timer::Instance();
	
	if(( lastFire + rechargeDelay ) < timer->GetTicks() ) {
		SpriteList *spriteList = SpriteList::Instance();
		lastFire = timer->GetTicks();
		
		// fire the weapon
		switch( type ) {
			case WLASER:
			{
				Ammo *laser = new Ammo( owner, owner->GetX(), owner->GetY(), owner->GetAngle() );
			
				spriteList->Add( laser );
			}
				break;
			case WNONE:
				break;
		}
	}
}
