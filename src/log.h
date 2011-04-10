#ifndef H_LOG
#define H_LOG

#define logMessage 0
#define logWarning 1
#define logError 2

void log( int severity, char *message, ... );

#endif // H_LOG
