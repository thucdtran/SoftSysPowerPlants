//This contains the Bridge class, and all of the
//methods of Bridge. A bridge represents the colection of 
//points and beams and all of the information needed to simulate
//and analyze a bridge.

#include "Beam.h"
#include <set>
#include <map>
#include <vector>
#include <cmath>
using namespace std;

struct csorter  //This is the comparator function for Points, sorting
		//them based on their distance from the left.
{
	bool operator()(const Point* a, const Point* b) const
	{
		return a->x<b->x;
	}
};


class Bridge {
	public:
		Bridge(); // constructor
		Bridge(Bridge* a, Bridge* b, double k);
		void generateBridge(int n, double k);
		void generateBridge(int n, double k, int roadPoints);
		void mutateBridge(double mutation_rate);
		void stripBridge();
		
		bool calculateForce(int road_points, pair<double, double>Force);
		pair<pair<double, double>, pair<double, double>> distributeLoad(Beam b, pair<double, double> Force, Point forcePoint);

		double calculateFitness();
		double getCost();
		set<Point*,csorter> getPoints();
		set<Beam*> getBeams();
		double fitness;
		int get_points_size();
	private:
		double distanceBetweenPoints(Point* p1, Point* p2);
		void remove_smaller_graphs();
		void _color_connected(Point* p, int color, map<Point*, int> *point_colors, map<Point*, bool> *visited, map<int, int>*color_count);
		set<Point*,csorter> points;
		set<Beam*> beams;
		map<Point*, set<Beam*> > point_to_beams;
		vector<Point *> ordered_points;
		double max_beam_distance; 
};
