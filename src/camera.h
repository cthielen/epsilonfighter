#ifndef H_CAMERA
#define H_CAMERA

#include "sprite.h"

class Camera {
	public:
		static Camera *Instance();

		void Update( void );

		void GetDelta( float *dx, float *dy );

		void WorldtoScreen( float x, float y, int *sx, int *sy );

		void Look( int x, int y );
		bool Follow( Sprite *sprite );

		void SetAngle( float ang );
		float GetAngle( void );

	protected:
		Camera();
		Camera( const Camera & );
  		Camera& operator= (const Camera&);

	private:
		static Camera *pInstance;

		float x, y; // camera position
		float dx, dy; // the change in camera position from the last update
		float ang;
		Sprite *following; // the sprite we're following (NULL if not following)

};

#endif // H_CAMERA
