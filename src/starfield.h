#ifndef H_STARFIELD
#define H_STARFIELD


class cStarfield {
	public:
		cStarfield( int num );
		~cStarfield( void );

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
