using namespace std;

class Point {
	public:
		double x;
		double y;
		double mass;
		bool fixed;
		Point(double _x, double _y);
		Point(double _x, double _y, bool _fixed);
		//bool cmp(Point* a, Point* b);
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