#ifndef H_AUDIO
#define H_AUDIO

#include "includes.h"

class Audio {
	public:
		static Audio *Instance();

		bool Init( void );
		bool Close( void );

		void Play( int which );

	protected:
		Audio();
		Audio( const Audio & );
  		Audio& operator= (const Audio&);

  	private:
		static Audio *pInstance;
		Mix_Music *mars;
};

#endif // H_AUDIO
