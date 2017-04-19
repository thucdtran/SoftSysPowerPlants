using namespace std;

class Point {
	public:
		int order;
		double x;
		double y;
		double mass;
		bool fixed;
		Point(double _x, double _y, int _count);
		Point(double _x, double _y, bool _fixed, int _count);
		//bool cmp(Point* a, Point* b);
	private:
};

Point::Point(double _x, double _y, int _count) {
  x = _x;
  y = _y;
  mass = 10.0;
  fixed = false;
  order = _count;
}

Point::Point(double _x, double _y, bool _fixed, int _count) {
  x = _x;
  y = _y;
  mass = 10.0;
  fixed = _fixed;
  order = _count;
}

/*
bool Point::cmp(Point &a, Point &b) {
	return a->order < b->order;
}*/