#include <iostream>
#include <armadillo>
#include <map>
#include <multimap>
using namespace std;
using namespace arma;




/*
Springs_Map takes a point index as a key 
and the value is a list of spring structs the point
is connected to. Each of these springs has two points, 
a spring constant, and an initial length.
*/

class point
{
	public:
		double x;
		double y;
};

class beam {
    public:
        double rest;        // rest length of beam
        double youngs_mod;  // Effectively the spring constant
        point p1;           // First point of the beam
        point p2;           // Second point of the beam
};



int* sim_step(vec Point_Array, map<int, int> &Springs_Map){
	float damp = .07;


	float t = 30;
	float frame_rate = 20;
	float t_step = t*frame_rate;
	float dt = t/t_step;
	damp = 1-damp*dt;




}


int main()
  {
  mat A = randu<mat>(4,5);
  mat B = randu<mat>(4,5);
  
  cout << A*B.t() << endl;
  
  return 0;
  }
