#ifndef BRIDGE_H
#define BRIDGE_H

#include "Beam.h"
#include <set>
#include <map>
#include <vector>
#include <cmath>

using namespace std;

class Bridge {
	public:
		Bridge(); // constructor
		Bridge(Bridge* a, Bridge* b, double k);
		void generateBridge(int n, double k);
		set<Point*> getPoints();
		set<Beam*> getBeams();

	private:
		double distanceBetweenPoints(Point* p1, Point* p2);
		void calculateForce();
		set<Point*> points;
		set<Beam*> beams;
		map<Point*, set<Beam*> > point_to_beams;
};

Bridge::Bridge() {
	// Default constructor
}

Bridge::Bridge(Bridge* a, Bridge* b, double k)
{	//Finds the number of points we want to keep from a bridge. 
	//Dependant on the the number of points in the smaller bridge. 
	int set_size = a->points.size()>b->points.size() ? b->points.size() : 
													   a->points.size();
	int kept_points = ((double) rand()/RAND_MAX) * set_size;

	set<Point*>::iterator it = a->points.begin();

	//Keep first kept_points of a;
	for(int x = 0; x<kept_points; x++)
	{
		points.insert(new Point((*it)->x, (*it)->y));
		it++;
	}

	//Keep last kept_points of b;
	it = b->points.begin();
	advance(it, kept_points);
	for(int x = kept_points; x< b->points.size(); x++)
	{
		points.insert(new Point((*it)->x, (*it)->y));
		it++;
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

void Bridge::calculateForce() {
	for (Point* p : points) {
		double Fx = 0.0;
		double Fy = 0.0;
		for (Beam* beam : point_to_beams[p]) {
			if (p != beam->p1) {
				double dist = distanceBetweenPoints(beam->p1, beam->p2);
				pair<double, double> unit_vector = make_pair((beam->p1->x - beam->p2->x) / dist, (beam->p1->y - beam->p2->y)/ dist);
				
				double F = beam->k * (beam->r - dist);
				Fx += F * unit_vector.first;
				Fy += F * unit_vector.second;
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


#endif