#include "vector.h"

vector2D::vector2D() {
	x = 0.;
	y = 0.;
}

vector2D::vector2D( float x, float y ) {
	this->x = x;
	this->y = y;
}

vector2D vector2D::operator+(const vector2D &rhs) {
	x += rhs.x;
	y += rhs.y;
	
	return( *this );
}

vector2D vector2D::operator*(const float &rhs) {
	x *= rhs;
	y *= rhs;
	
	return( *this );
}

void vector2D::Set( float x, float y ) {
	this->x = x;
	this->y = y;
}

vector2D vector2D::operator=(const vector2D &rhs) {
	return( *this );
}

ostream& operator<<(ostream& os, const vector2D& vector) {
	os << "(" << vector.x << ", " << vector.y << ")";
	
	return( os );
}

float vector2D::GetX( void ) {
	return( x );
}

float vector2D::GetY( void ) {
	return( y );
}

float vector2D::GetAngle( void ) {
	return( atan2( (double)y, (double)x ) );
}

float vector2D::GetMagnitude( void ) {
	return( (float)sqrt( (x*x) + (y*y) ) );
}
