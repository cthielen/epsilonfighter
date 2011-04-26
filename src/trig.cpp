#include "includes.h"
#include "trig.h"

Trig *Trig::pInstance = 0;

Trig::Trig( void ) {
	int i;

	convdr = M_PI / 180.;
	convrd = 180. / M_PI;

	for( i = 0; i < 360; i++ ) {
		cosTable[i] = cos( (double)i * convdr );
		sinTable[i] = sin( (double)i * convdr );
		tanTable[i] = tan( (double)i * convdr );
	}
}

Trig *Trig::Instance( void ) {

	if( pInstance == 0 ) {
		pInstance = new Trig;
	}

	return( pInstance );
}

double Trig::DegToRad( int i ) {
	return( i * convdr );
}

double Trig::DegToRad( double i ) {
	return( i * convdr );
}

int Trig::RadToDeg( double i ) {
	return( (int)(i * convrd) );
}

double Trig::GetCos( int ang ) {
	return( cosTable[ang] );
}

double Trig::GetCos( double ang ) {
	return( cos( ang ) );
}

double Trig::GetSin( int ang ) {
	return( sinTable[ang] );
}

double Trig::GetSin( double ang ) {
	return( sin(ang) );
}

// rotates point (x, y) about point (ax, ay) and sets nx, ny to new point
void Trig::RotatePoint( float x, float y, float ax, float ay, float *nx, float *ny, float ang ) {
	float theta = atan2( y - ay, x - ax );
	float dist = sqrt( ((x - ax)*(x-ax)) + ((y - ay)*(y-ay)) );
	float ntheta = theta + ang;

	*nx = ax + (dist * cos( ntheta ) );
	*ny = ay - (dist * sin( ntheta ) );
}
