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
#include <chrono>
#include <thread>

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void drawBridge(Bridge* bridge);
void drawBeam(Beam* beam);
void drawPoint(Point* p);
void simulate(Bridge* bridge, int road_points);
void gradientDescent(Bridge* bridge, int road_points);

using namespace std;
using namespace std::this_thread; // For sleep
using namespace std::chrono;  // For sleep

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
  Bridge* best_bridge = bridge;
  double old_score = bridge->calculateFitness();
  double best_score = 20;
  int best_road_points = 0;
  for (int i = 0; i <30; ++i)
  {
      bridge = new Bridge();

      //bridge->generateBridge(10, .25,0);
      int road_points = 15;
      
      bridge->generateBridge(20, 1, road_points);
      printf("%f\n", bridge->getCost());
      bridge->stripBridge();
      gradientDescent(bridge, road_points);
      // Beam* b = new Beam(p1, p2, r);
      // bridge->distributeLoad(Beam b, pair Force);

      drawBridge(bridge);
      glutSwapBuffers();

    simulate(bridge, road_points);

    if(bridge->calculateFitness() < best_score) {
      best_bridge = bridge;
      best_road_points = road_points;
      best_score = bridge->calculateFitness();
    }
    old_score = bridge->calculateFitness();
    cout << "Animation done, convergence found..." << endl;

  }
  cout << "Best Score :" << best_score << endl;
  simulate(best_bridge, best_road_points);


  glutMainLoop();
}

void simulate(Bridge* bridge, int road_points){
  double time_start  = time(NULL);
  double time_elapsed = 0;
  bool converged = false;
  while (!converged) {
    sleep_for(nanoseconds(500000));
    time_elapsed = time(NULL) - time_start;
    //cout << "next frame...." << endl;
    for (int i = 0; i < 5; i++) {
      converged = bridge->calculateForce(road_points);
      if (time_elapsed > 2) {
        converged = 1;
      }
    }
    //usleep(300);
    glClear(GL_COLOR_BUFFER_BIT);
    drawBridge(bridge);
    glutSwapBuffers();
  }

}

void gradientDescent(Bridge* bridge, int road_points){
  Bridge bridge_copy = bridge;
  for (Point* p : bridge_copy->points) {
    simulate(bridge_copy);
    p.x += .001;
  }
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
    double color = beam->getStress();
    if (color < 0) 
      glColor3f(1, 1, 0);
    else 
      glColor3f(color, 0, 0);
  /*if(beam->beamType == 1) 
    glColor3f(0,1,0);*/

    glVertex2f(beam->p1->x, beam->p1->y);
    glVertex2f(beam->p2->x, beam->p2->y);
  glEnd();
}

void drawPoint(Point* p) {
  double x = p->x;
  double y = p->y;
  glBegin(GL_POLYGON);
    if (p->fixed) glColor3f(0, 0, 1);
    else if (p->road) glColor3f(0,1,1);
    else glColor3f(0, 1, 0); 
    glVertex3f(x - 0.02, y - 0.025, 0);
    glVertex3f(x + 0.02, y - 0.025, 0);
    glVertex3f(x, y + 0.025, 0);
  glEnd();
}