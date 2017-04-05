// compile via 
//  g++ draw.cpp -lm -lGL -lGLU -lglut -o draw

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include "Beam.h"

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void drawPoint(Point* p);
void drawLine(Beam* beam);

using namespace std;


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

  vector<Point*> point_list;
  point_list.push_back(p1);
  point_list.push_back(p2);
  point_list.push_back(p3);

  /*for (int i = 0; i < point_list.size(); i++) {
    cout << point_list[i]->x << ", " << point_list[i]->y << endl;
  }*/

  map<Point*, vector<Beam*> > point_to_beam();

  


  drawLine(b1);
  drawLine(b2);
  drawPoint(p1);
  drawPoint(p2);
  drawPoint(p3);



  glutSwapBuffers();

  // Tell GLUT to start reading and processing events.  This function
  // never returns; the program only exits when the user closes the main
  // window or kills the process.

  //Point p1 = new Point(10.0, 10.0);

  glutMainLoop();
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