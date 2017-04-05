#include "Beam.h"
#include <set>
#include <map>
#include <vector>
#include <cmath>

using namespace std;

class Bridge {
	public:
		set<Point*> points;
		set<Beam*> beams;
		map<Point*, set<Beam*> > point_to_beams;
		Bridge(); // constructor
		void generateBridge(int n, int k);
	private:
		double distanceBetweenPoints(Point* p1, Point* p2);
};

Bridge::Bridge() {

}

void Bridge::generateBridge(int n, int k) {
	// Generates n points
	for (int i = 0; i < n; i++) {
		double x = ((double) rand() / (RAND_MAX)); // 0 to 1
		double y = ((double) rand() / (RAND_MAX)); // 0 to 1
		points.insert(new Point(x, y));
	}

	// Construct beams between points within k distance. O(n^2) runtime.
	for (Point* p1 : points) {
		for (Point* p2 : points) {
			//if ()
		}
	}
}

double Bridge::distanceBetweenPoints(Point* p1, Point* p2) {
	return 0.0;
	//return (pow(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2)), 0.5); 
}