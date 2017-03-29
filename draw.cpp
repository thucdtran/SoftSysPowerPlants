#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
//#include "Point.h"

// compile via 
//  g++ draw.cpp -lm -lGL -lGLU -lglut

// A simple introductory program; its main window contains a static picture
// of a triangle, whose three vertices are red, green and blue.  The program
// illustrates viewing with default viewing parameters only.

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

static vector<pair<int, int> > points;

// Clears the current window and draws a triangle.
void display() {

  // Set every pixel in the frame buffer to the current clear color.
  glClear(GL_COLOR_BUFFER_BIT);

  // Drawing is done by specifying a sequence of vertices.  The way these
  // vertices are connected (or not connected) depends on the argument to
  // glBegin.  GL_POLYGON constructs a filled polygon.
  glBegin(GL_POLYGON);
    glColor3f(1, 0, 0); glVertex3f(-0.6, -0.75, 0.5);
    glColor3f(0, 1, 0); glVertex3f(0.6, -0.75, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0.75, 0);
  glEnd();

  // Flush drawing command buffer to make drawing happen as soon as possible.
  glFlush();
}


void drawPoints() {

	// Drawing is done by specifying a sequence of vertices.  The way these
	// vertices are connected (or not connected) depends on the argument to
	// glBegin.  GL_POLYGON constructs a filled polygon.
	for (int i = 0; i < points.size(); i++) {
		glBegin(GL_POLYGON);
			glColor3f(1, 0, 0); glVertex3f(points[i].first - 0.1, points[i].second - 0.1, 0);
			glColor3f(0, 1, 0); glVertex3f(points[i].first - 0.1, points[i].second + 0.1, 0);
			glColor3f(0, 0, 1); glVertex3f(points[i].first + 0.1, points[i].second + 0.1, 0);
			glColor3f(1, 1, 1); glVertex3f(points[i].first + 0.1, points[i].second - 0.1, 0);
		glEnd();
		cout << "Drawing point " << i << endl;
		glFlush();
	}

	// Flush drawing command buffer to make drawing happen as soon as possible.
}

// Initializes GLUT, the display mode, and main window; registers callbacks;
// enters the main event loop.
int main(int argc, char** argv) {

  // Use a single buffered window in RGB mode (as opposed to a double-buffered
  // window or color-index mode).
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  // Position window at (80,80)-(480,380) and give it a title.
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(400, 300);
  glutCreateWindow("A Simple Triangle");

  // Tell GLUT that whenever the main window needs to be repainted that it
  // should call the function display().
  glClear(GL_COLOR_BUFFER_BIT);

  points.push_back(make_pair(0, 0));
  points.push_back(make_pair(0.5, 0.1));
  points.push_back(make_pair(-0.1, -0.3));
  glutDisplayFunc(drawPoints);

  // Tell GLUT to start reading and processing events.  This function
  // never returns; the program only exits when the user closes the main
  // window or kills the process.

  //Point p1 = new Point(10.0, 10.0);

  glutMainLoop();
}



/*
void addBeam() {
	int x1, y1;
	int x2, y2;

	point p1 = new point(x1, y1);
	point p2 = new point(x2, y2);
}

void draw(Point p1) {

}*/