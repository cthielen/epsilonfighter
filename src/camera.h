#ifndef H_CAMERA
#define H_CAMERA

#include "sprite.h"

class cCamera {
	public:
		static cCamera *Instance();

		void Update( void );

		void GetDelta( float *dx, float *dy );

		void WorldtoScreen( float x, float y, int *sx, int *sy );

		void Look( int x, int y );
		bool Follow( cSprite *sprite );

		void SetAngle( float ang );
		float GetAngle( void );

	protected:
		cCamera();
		cCamera( const cCamera & );
  		cCamera& operator= (const cCamera&);

	private:
		static cCamera *pInstance;

		float x, y; // camera position
		float dx, dy; // the change in camera position from the last update
		float ang;
		cSprite *following; // the sprite we're following (NULL if not following)

};

#endif // H_CAMERA
