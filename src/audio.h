#ifndef H_AUDIO
#define H_AUDIO

#include "includes.h"

class cAudio {
	public:
		static cAudio *Instance();

		bool Init( void );
		bool Close( void );

		void Play( int which );

	protected:
		cAudio();
		cAudio( const cAudio & );
  		cAudio& operator= (const cAudio&);

  	private:
		static cAudio *pInstance;
		Mix_Music *mars;
};

#endif // H_AUDIO
