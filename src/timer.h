#ifndef H_TIMER
#define H_TIMER

#include "includes.h"

class Timer {
	public:
		static Timer *Instance();
	
		void SetDesiredFPS( int fps );
		int GetLoops( void ); // returns the number of logic loops to run
		void Reset( void );
		void Delay( void );
		float GetMultiplier( void ); // returns the multiplier for all update functions
		Uint32 GetTicks( void );

	protected:
		Timer();
		Timer( const Timer & );
  		Timer& operator= (const Timer&);

  	private:
		static Timer *pInstance;
		
		int dfps; // desired fps
		Uint32 lastTick;
		Uint32 loopLen; // desired loop length
		float multiplier;
		Uint32 pauseDelay;
};

#endif // H_TIMER
