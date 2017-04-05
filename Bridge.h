#include "Beam.h"
#include <set>
#include <map>
#include <vector>

using namespace std;

class Bridge {
	public:
		set<Point*> points;
		set<Beam*> beams;
		map<Point*, set<Beam*> > pb;
		Bridge(); // constructor
	private:
};

Bridge::Bridge() {
	
}