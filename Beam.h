/*
Beam class represents a beam structure. It consists of several 
physical characteristics and two Points.
*/

#include "Point.h"
#include <cmath>
#include <string.h>
using namespace std;


class Beam {
    public:
        Point* p1;
        Point* p2;
        double k;
        double r;
        double yield_strength;
        double cost_per_meter;
        double weight;
        Beam(Point* _p1, Point* p2, double _r);
        bool fail(double distance);
        double getStress();
        void assign_mat_properties(string material_name);
        short beamType;
        Beam(Point* _p1, Point* _p2, double _r, short _beamType, string material_name);

    private: 
        double stress;
};