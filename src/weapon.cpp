#include "includes.h"
#include "sprite_list.h"
#include "timer.h"
#include "vector.h"
#include "weapon.h"

cWeapon::cWeapon() {
	SetType( WNONE );
	lastFire = 0;
}

cWeapon::cWeapon( weaponType type ) {
	SetType( type );
	lastFire = 0;
}

void cWeapon::SetType( weaponType type ) {
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

void cWeapon::Fire( cSprite *owner ) {
	cTimer *timer = cTimer::Instance();
	
	if(( lastFire + rechargeDelay ) < timer->GetTicks() ) {
		cSpriteList *spriteList = cSpriteList::Instance();
		lastFire = timer->GetTicks();
		
		// fire the weapon
		switch( type ) {
			case WLASER:
			{
				cAmmo *laser = new cAmmo( owner, owner->GetX(), owner->GetY(), owner->GetAngle() );
			
				spriteList->Add( laser );
			}
				break;
			case WNONE:
				break;
		}
	}
}
