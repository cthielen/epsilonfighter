#ifndef H_LEVEL
#define H_LEVEL

#include "camera.h"
#include "includes.h"
#include "sprite.h"

class Level {
	public:
		Level( int which );

	private:
		vector<Sprite *> sprites;
		Camera *camera;

};

#endif // H_LEVEL
