#include "Beam.h"

// Constructor for beam. Takes two points and the maximum allowed
// length for beams.
Beam::Beam(Point* _p1, Point* _p2, double _r) {
  p1 = _p1;
  p2 = _p2;
  k = 100000.0;
  r = _r;
  yield_strength = 0.02;
}

// Alternate constructor for beam that allows for defining beamtype.
Beam::Beam(Point* _p1, Point* _p2, double _r, short _beamType)
{
	p1 = _p1;
	p2 = _p2;
	k = 100000.0;
	r = _r;
	beamType = _beamType;
	yield_strength = 0.02;
}

// Returns true if a beam has failed.
bool Beam::fail(double distance) {
	stress = 1 - (abs(distance) - r) / 0.02;
	return abs(distance) > (r + yield_strength);
}

// Returns the stress on a beam.
double Beam::getStress() {
	return stress;
}
