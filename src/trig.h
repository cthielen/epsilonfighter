#ifndef H_TRIG
#define H_TRIG

class cTrig {
	public:
		static cTrig *Instance();

		double DegToRad( int i );
		double DegToRad( double i );
		int RadToDeg( double i );

		double GetCos( int ang );
		double GetCos( double ang );
		double GetSin( int ang );
		double GetSin( double ang );

		void RotatePoint( float x, float y, float ax, float ay, float *nx, float *ny, float ang );

	protected:
		cTrig();
		cTrig( const cTrig & );
  		cTrig& operator= (const cTrig&);

	private:
		static cTrig *pInstance;

		double convdr; // conversion factor from degrees to radians
		double convrd; // conversion factor from radians to degrees

		double sinTable[360];
		double cosTable[360];
		double tanTable[360];
};

#endif // H_TRIG
