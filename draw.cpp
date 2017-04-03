#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>

// compile via 
//  g++ draw.cpp -lm -lGL -lGLU -lglut -o draw


#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

class Point {
  public:
    double x;
    double y;
    Point(double _x, double _y);
    //set<Beam*> neighbors;
  private:
};

Point::Point(double _x, double _y) {
  x = _x;
  y = _y;
}

class Beam {
  public:
    Point* p1;
    Point* p2;
    Beam(Point* _p1, Point* _p2);
  private: 
};


Beam::Beam(Point* _p1, Point* _p2) {
  p1 = _p1;
  p2 = _p2;
}

void drawPoint(Point* p) {

	// Drawing is done by specifying a sequence of vertices.  The way these
	// vertices are connected (or not connected) depends on the argument to
	// glBegin.  GL_POLYGON constructs a filled polygon.

  double x = p->x;
  double y = p->y;
	glBegin(GL_POLYGON);
    /*glPointSize(40);
    glColor3f(0, 1, 0);
    glVertex3f(x, y, 0);*/
		glColor3f(0, 1, 0); 
    glVertex3f(x - 0.02, y - 0.025, 0);
		glVertex3f(x + 0.02, y - 0.025, 0);
		glVertex3f(x, y + 0.025, 0);
	glEnd();
	cout << "Drawing point (" << x << ", " << y << endl;

	// Flush drawing command buffer to make drawing happen as soon as possible.
}

void drawLine(Beam* beam) {
  glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex2f(beam->p1->x, beam->p1->y);
    glVertex2f(beam->p2->x, beam->p2->y);
  glEnd();
}


void mouse(int button, int state, int x, int y)
{
  //This is a temorary hack for scaling a location. DO DELETE -> or convert 
  //Into doing more stuff here. 
  Point * p4 = new Point((x-200.0)/200.0,-(y-150.0)/150.0);

  //When the button is first clicked
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    std::cout<<"Clicked on ("<<x<<","<<y<<")\n";
    drawPoint(p4);
  }
  //When the button is released
  else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    std::cout<<"goodbye!\n";
  }

  //Switches the buffer to display new content
  glutSwapBuffers();

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
  glutCreateWindow("Drawing beams");

  // Tell GLUT that whenever the main window needs to be repainted that it
  // should call the function display().
  glClear(GL_COLOR_BUFFER_BIT);

  // Window stretches from (-1,1) in the x-axis and y-axis.
  Point* p1 = new Point(0.2, 0.3);
  Point* p2 = new Point(-0.4, 0.14);
  Point* p3 = new Point(0, 0);
  Beam* b1 = new Beam(p1, p2);
  Beam* b2 = new Beam(p1, p3);

  drawLine(b1);
  drawLine(b2);
  drawPoint(p1);
  drawPoint(p2);
  drawPoint(p3);

  glutSwapBuffers();


  //Setting up Mouse Event for GLUT
  glutMouseFunc(mouse);


  // Tell GLUT to start reading and processing events.  This function
  // never returns; the program only exits when the user closes the main
  // window or kills the process.

  //Point p1 = new Point(10.0, 10.0);


  glutMainLoop();
}
