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

Beam::Beam(Point* _p1, Point* _p2, double _r) {
  p1 = _p1;
  p2 = _p2;
  k = 100000.0;
  r = _r;
  yield_strength = 0.02;
}

bool Beam::fail(double distance) {
	stress = 1 - (abs(distance) - r) / 0.02;
	return abs(distance) > (r + yield_strength);
}

double Beam::getStress() {
	return stress;
  beamType = 0;
}

Beam::Beam(Point* _p1, Point* _p2, double _r, short _beamType)
{
	p1 = _p1;
	p2 = _p2;
	k = 100000.0;
	r = _r;
	beamType = _beamType;
	yield_strength = 0.02;
}