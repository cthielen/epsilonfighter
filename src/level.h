#ifndef H_LEVEL
#define H_LEVEL

#include "camera.h"
#include "includes.h"
#include "sprite.h"

class cLevel {
	public:
		cLevel( int which );

	private:
		vector<cSprite *> sprites;
		cCamera *camera;

};

#endif // H_LEVEL
