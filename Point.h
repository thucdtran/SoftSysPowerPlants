using namespace std;

class Point {
	public:
		double x;
		double y;
		double mass;
		bool fixed;
		Point(double _x, double _y);
		Point(double _x, double _y, bool _fixed);
		Point* copy();
		//void copy(Point* other);
	private:
};

Point::Point(double _x, double _y) {
  x = _x;
  y = _y;
  mass = 10.0;
  fixed = false;
}

Point::Point(double _x, double _y, bool _fixed) {
  x = _x;
  y = _y;
  mass = 10.0;
  fixed = _fixed;
}

/*void Point::copy(Point* other) {
	other->x = x;
	other->y = y;
	other->mass = mass;
	other->fixed = fixed;
}*/


Point* Point::copy() {
	Point* cpy = new Point(x, y, fixed);
	return cpy;
}