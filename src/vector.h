#ifndef H_VECTOR
#define H_VECTOR

#include "includes.h"

class vector2D {
	public:
		vector2D();
		vector2D( float x, float y );
	
		void Set( float x, float y );
	
		float GetX( void );
		float GetY( void );
		float GetAngle( void );
		float GetMagnitude( void );
	
		vector2D operator+(const vector2D &rhs);
		vector2D operator*(const float &rhs);
		vector2D operator=(const vector2D &rhs);
		friend ostream& operator << (ostream& os, const vector2D &vector );

	private:
		float x, y;
};

#endif // H_VECTOR
