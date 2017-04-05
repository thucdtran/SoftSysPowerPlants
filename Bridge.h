#include "Beam.h"
#include <set>
#include <map>
#include <vector>
#include <cmath>

using namespace std;

class Bridge {
	public:
		Bridge(); // constructor
		void generateBridge(int n, double k);
		set<Point*> getPoints();
		set<Beam*> getBeams();
	private:
		double distanceBetweenPoints(Point* p1, Point* p2);
		set<Point*> points;
		set<Beam*> beams;
		map<Point*, set<Beam*> > point_to_beams;
};

Bridge::Bridge() {
	// Default constructor
}

void Bridge::generateBridge(int n, double k) {
	// Generates n points
	for (int i = 0; i < n; i++) {
		double x = ((double) rand() / (RAND_MAX)); // 0 to 1
		double y = ((double) rand() / (RAND_MAX)); // 0 to 1
		points.insert(new Point(x, y));
	}

	// Construct beams between points within k distance. O(n^2) runtime.
	for (Point* p1 : points) {
		for (Point* p2 : points) {
			if (p1 == p2) continue;
			if (distanceBetweenPoints(p1, p2) < k) {
				Beam* beam = new Beam(p1, p2);
				beams.insert(beam);
				// Add to map
				point_to_beams[p1].insert(beam);
				point_to_beams[p2].insert(beam);
			}
		}
	}
}

double Bridge::distanceBetweenPoints(Point* p1, Point* p2) {
	return pow(pow((p1->x - p2->x), 2) + pow(p1->y - p2->y, 2), 0.5); 
}


set<Point*> Bridge::getPoints() {
	return points;
}

set<Beam*> Bridge::getBeams() {
	return beams;
}