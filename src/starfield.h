#ifndef H_STARFIELD
#define H_STARFIELD


class Starfield {
	public:
		Starfield( int num );
		~Starfield( void );

		void Update();
		void Draw( void );

	private:
		struct _stars {
			float x, y;
			float sx, sy;
			Uint32 clr;
			float s; // speed
		} *stars;

		int num; // number of stars
		float ang; // the last known camera angle
};

#endif // H_STARFIELD
