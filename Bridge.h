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
		void mutateBridge(double mutation_rate);
		void stripBridge();
		
		bool calculateForce();
		double calculateFitness();
		double getCost();
		set<Point*> getPoints();
		set<Beam*> getBeams();

	private:
		double distanceBetweenPoints(Point* p1, Point* p2);
		void remove_smaller_graphs();
		void _color_connected(Point* p, int color, map<Point*, int> *point_colors, map<Point*, bool> *visited, map<int, int>*color_count);
		set<Point*> points;
		set<Beam*> beams;
		map<Point*, set<Beam*> > point_to_beams;
};


Bridge::Bridge() {
	// Default constructor
}

Bridge::Bridge(Bridge* a, Bridge* b, double r)
{	//Finds the number of points we want to keep from a bridge. 
	//Dependant on the the number of points in the smaller bridge. 
	int set_size = a->points.size()>b->points.size() ? b->points.size() : 
													   a->points.size();
	int kept_points = ((double) rand()/RAND_MAX) * set_size+1;

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
			if (distanceBetweenPoints(p1, p2) < r) {
				Beam* beam = new Beam(p1, p2, r);
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
	
	points.insert(new Point(-1, 0.5, true));
	points.insert(new Point(1, 0.5, true));
	int count = 2;
	for (int i = 0; i < n; i++) {
		double x = 2*((double) rand() / (RAND_MAX))-1; // 0 to 1
		double y = 2*((double) rand() / (RAND_MAX))-1; // 0 to 1
		points.insert(new Point(x, y));
		count++;
	}

	
	int p1_count = 0;
	for (Point* p1 : points) {
		int p2_count = 0;
		for (Point* p2 : points) {
			if (p2 <= p1) 
				continue;
			double dist = distanceBetweenPoints(p1, p2);
			if (dist < k) {
				Beam* beam = new Beam(p1, p2, dist);
				beams.insert(beam);
				// Add to map
				point_to_beams[p1].insert(beam);
				point_to_beams[p2].insert(beam);
			}
			p2_count++;
		}
		p1_count++;
	}
}

void Bridge::mutateBridge(double mutation_rate = .25){
	//Randomly changes the position of some set of points in the bridge
	int mutated_points = mutation_rate*points.size();
	for(int x = 0; x<mutated_points; x++)
	{
		set<Point*>::iterator it = points.begin();
		advance(it, rand()%points.size());
		//Tries to mutate the x and y position of a random point by up 
		//to 50%, limited to +-1 in order to stay on screen
//		double new_x = (*it)->x*(((double) rand()/RAND_MAX-.5)+1);
//		double new_y = (*it)->y*(((double) rand()/RAND_MAX-.5)+1);
//		if(new_x>1)
//			new_x = .8;
//		if(new_x<-1)
//			new_x = -.8;
//		if(new_y>1)
//			new_y = .8;
//		if(new_y<-1)
//			new_y = -.8;

//		(*it)->x = new_x;
//		(*it)->y = new_y;
	}


}

void Bridge::stripBridge()
{
	for (Point* p : points) {
		if (p->fixed) {
		}
		if (!p->fixed && point_to_beams[p].empty()) {
			points.erase(p);
		}
	}
	set<Point*>::iterator it;
	remove_smaller_graphs();
	remove_smaller_graphs();
}


void Bridge::_color_connected(Point* p, int color, map<Point*, int> *point_colors, map<Point*, bool> *visited, map<int, int> *color_count)
{
	//Colors the point as the given color, and increments associated count
	(*color_count)[color]++;
	(*point_colors).insert(pair<Point*, int>(p, color));
	(*visited).insert(pair<Point*, bool>(p, true));

	//Check to see if any neighboring nodes exist, and then recursively 
	//Look at them.
	set<Beam*>  connected_beams = point_to_beams[p];
		for (Beam* beam : connected_beams){
			if((*visited).count(beam->p1)==0)
				_color_connected(beam->p1, color, point_colors, visited, color_count);
			if((*visited).count(beam->p2)==0)
				_color_connected(beam->p2, color, point_colors, visited, color_count);			
		}
	

}

void Bridge::remove_smaller_graphs(){
	map<Point*, int > point_color;
	map<Point*, bool> visited;
	map<int, int> color_count;


	set<Point*>::iterator it;	
	it = points.begin();
	set<Point*>::iterator end = points.end();

	int total_used_colors = 1;
	for(it; it!=end; it++)
	{
		if(visited.count(*it)==0&&(*it)->fixed==true){
			_color_connected(*it, total_used_colors, &point_color, &visited, &color_count);
		}

	}

	map<int, int>::iterator itt;
	int currKey = 0;
	int currVal = 0;

	for (itt=color_count.begin(); itt!=color_count.end(); itt++){
		if(itt->second>currVal)
		{
			currKey = itt->first;
			currVal = itt->second;
		}
	}

	it = points.begin();
	end = points.end();

    for(it; it!=end; it++)
    {
    	if(point_color[*it]!=currKey){
			set<Beam*> beams_to_delete = point_to_beams[*it];
			set<Beam*>::iterator i = beams_to_delete.begin();
			set<Beam*>::iterator e = beams_to_delete.end();
			for(i; i!=e;i++)
				beams.erase(*i);
			points.erase(it);
    	}
    }


}



double Bridge::getCost()
{
	return 0;
}

bool Bridge::calculateForce() {
	bool converged = true;
	for (Point* p : points) {
		if (p->fixed) 
			continue;

		double Fx = 0.0;
		double Fy = 0.0;

		double Mx = 0.0; //How far the point will move
		double My = 0.0; //based on gradient descent


		Point* p_other;
		for (Beam* beam : point_to_beams[p]) {
			if (p != beam->p1){
				p_other = beam->p1;
			}else{
				p_other = beam->p2;
			}
			double dist = distanceBetweenPoints(p, p_other);
			pair<double, double> unit_vector = make_pair((p->x - p_other->x) / dist, (p->y - p_other->y)/ dist);
			
			if (beam->fail(dist)) {
				//cout << "Beam failed!" << endl;
			}
			double F = beam->k * (beam->r - dist);
			Fx += F * unit_vector.first;
			Fy += F * unit_vector.second;
			Fy -= p->mass * 9.8; // gravity
		}


		//cout<<Fx<<", "<<Fy<<endl;

		//cout<<Fx<<", "<<Fy<<endl;
		double dx = Fx / p->mass / 100000.0;
		double dy = Fy / p->mass / 100000.0;
		p->x += dx;
		p->y += dy;
		if (abs(dx) > 0.000001 || abs(dy) > 0.000001) {
			converged = false;
		}
	}
	//cout << "Converged: " << converged << endl;
	return converged;
}

// Returns the average stress on the beams. Use to evaluate fitness of a bridge.
double Bridge::calculateFitness() {
	double avg_stress = 0.0;
	for (Beam* beam : beams) {
		avg_stress += beam->getStress();
	}
	double score = avg_stress / beams.size();
	cout << score << " w/ " << beams.size() << " beams." << endl;
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