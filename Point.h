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

Point::Point(double _x, double _y) {
  x = _x;
  y = _y;
  mass = 10.0;
  fixed = false;
  road = false;
}

Point::Point(double _x, double _y, bool _fixed) {
  x = _x;
  y = _y;
  mass = 10.0;
  fixed = _fixed;
  road = false;
}
Point::Point(double _x, double _y, bool _fixed, bool _road)
{
	x = _x;
  y = _y;
  mass = 10.0;
  fixed = _fixed;
  road = _road;
}