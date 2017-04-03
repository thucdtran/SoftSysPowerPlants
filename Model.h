#include <vector>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


class Point {
  public:
    double x;
    double y;
    Point(double _x, double _y);
    //set<Beam*> neighbors;
  private:
};


class Beam {
  public:
    Point* p1;
    Point* p2;
    Beam(Point* _p1, Point* _p2);
  private: 
};

class Model{
	public:
		Model();
    void AddPoint(int _x, int _y);
    void AddBeam(Point* _p1, Point* _p2);
    void mouse(int button, int state, int x, int y);
    void keyboard(unsigned char key, int x, int y);
    char status; 

	private:
    std::vector<Point*> p;
    std::vector<Beam*> b;
};



extern void drawPoint(Point* p);
extern void drawLine(Beam* b);