/*
The point class represents a pin in the structure of the bridge.
*/
using namespace std;

class Point {
	public:
		double x;
		double y;
		double mass;
		bool fixed;
		bool road;
		Point(double _x, double _y);
		Point(double _x, double _y, bool _fixed);
		Point(double _x, double _y, bool _fixed, bool _road);
	private:
};