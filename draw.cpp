// compile via 
// compile first: 
// g++ Point.h -std=
//
//  g++ draw.cpp -lm -lGL -lGLU -lglut -std=c++11 -o draw

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include "Generation.h"

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void drawBridge(Bridge* bridge);
void drawBeam(Beam* beam);
void drawPoint(Point* p);

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
  glutInitWindowSize(800, 600);
  glutCreateWindow("Drawing beams");

  // Tell GLUT that whenever the main window needs to be repainted that it
  // should call the function display().
  glClear(GL_COLOR_BUFFER_BIT);

  // Window stretches from (-1,1) in the x-axis and y-axis.

  srand(time(NULL));

  Bridge* bridge = new Bridge();
  bridge->generateBridge(20, .25);
  bridge->stripBridge();
  bridge->stripBridge();
  drawBridge(bridge);
  glutSwapBuffers();
  int x = 0;
  cin>>x;

  bridge->mutateBridge();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  drawBridge(bridge);
  glutSwapBuffers();

  x= 0 ;
  cin>>x;

  glutMainLoop();
}





void drawBridge(Bridge* bridge) {
  for (Beam* beam : bridge->getBeams()) {
    drawBeam(beam);
  }
  for (Point* point : bridge->getPoints()) {
    drawPoint(point);
  }
}

void drawBeam(Beam* beam) {
  glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex2f(beam->p1->x, beam->p1->y);
    glVertex2f(beam->p2->x, beam->p2->y);
  glEnd();
}

void drawPoint(Point* p) {
  double x = p->x;
  double y = p->y;
  glBegin(GL_POLYGON);
    glColor3f(0, 1, 0); 
    glVertex3f(x - 0.02, y - 0.025, 0);
    glVertex3f(x + 0.02, y - 0.025, 0);
    glVertex3f(x, y + 0.025, 0);
  glEnd();
}