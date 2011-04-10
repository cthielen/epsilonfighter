#include "includes.h"
#include "log.h"

void log( int severity, char *message, ... ) {
	va_list arguments;
	char *p;

	if( severity == logMessage )
		printf( "Message: " );
	else if( severity == logWarning )
		printf( "Warning: " );
	else if( severity == logError )
		printf( "Error: ");

	p = message;

	va_start( arguments, message );

	while( *p ) {
		if( *p == '%' ) {
			*p++;
			assert( *p ); // it is assumed that '%' is not at the end of a string

			if( *p == 'd' )
				printf( "%d", va_arg( arguments, int ) );
			else if( *p == 'f' )
				printf( "%f", va_arg( arguments, double ) );
			else if( *p == 's' )
				printf( "%s", va_arg( arguments, char * ) );
			else
				printf( "?" );

		} else {
			printf( "%c", *p );
		}

		++p;
	}

	if( *--p != '\n' )
		printf( "\n" );

	va_end( arguments );

	return;
}
