/*
Beam class represents a beam structure. It consists of several 
physical characteristics and two Points.
*/

#include "Point.h"
#include <cmath>

using namespace std;

class Beam {
	public:
		Point* p1;
		Point* p2;
		double k;
		double r;
		double yield_strength;
		Beam(Point* _p1, Point* p2, double _r);
		bool fail(double distance);
		double getStress();
		short beamType;
		Beam(Point* _p1, Point* _p2, double _r, short _beamType);

	private: 
		double stress;
};