#include "Point.h"

// Create a point from coordinates
Point::Point(double _x, double _y) {
  x = _x;
  y = _y;
  mass = 10.0;
  fixed = false;
  road = false;
}

// Created a point from coordinates and define whether it is fixed
Point::Point(double _x, double _y, bool _fixed) {
  x = _x;
  y = _y;
  mass = 10.0;
  fixed = _fixed;
  road = false;
}

// Create a point on the road
Point::Point(double _x, double _y, bool _fixed, bool _road)
{
	x = _x;
  y = _y;
  mass = 10.0;
  fixed = _fixed;
  road = _road;
}