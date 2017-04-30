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
vector<Bridge*> evaluateBridge(vector<Bridge *> bridges);
vector<Bridge*> evolveBridge(vector<Bridge*> bridges);
void animateBridge(Bridge* bridge);

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
  int r = 1.0;
  Bridge* bridge = new Bridge(r);
  bridge->generateBridge(30);
  bridge->stripBridge();
  int k;
  cin >> k;
  animateBridge(bridge);
  //bridge->calculateForce();
  /*
  drawBridge(bridge);
  glutSwapBuffers();

  vector<Bridge*> bridges(100);
  for (int i = 0; i < 100; i++) {
    bridges[i] = new Bridge(r);
    bridges[i]->generateBridge(15);
    bridges[i]->stripBridge();
  }

  // start with 10 bridges
  for (int i = 0 ; i < 10; i++) {
    //cout << endl << "Iteration " << i << endl << endl;
    vector<Bridge*> best_bridges = evaluateBridge(bridges); // returns 10 of the best bridges
    vector<Bridge*> new_bridges = evolveBridge(best_bridges); // generate 100 new bridges from 10 best ones
    bridges = new_bridges;  

    cout << "Animating first bridge..." << endl;
    animateBridge(bridges[0]);
    int k = 0;
    cin >> k;
  }  
  */
  glutMainLoop();

  return 0;
}

void animateBridge(Bridge* bridge) {
  cout << "Animating bridge..." << endl;
  bool converged = false;
  int iter = 0;
  while (!converged && iter < 1000) {
    sleep_for(nanoseconds(10000000));
    for (int i = 0; i < 5; i++) {
      converged = bridge->calculateForce();
    }
    iter++;
    glClear(GL_COLOR_BUFFER_BIT);
    drawBridge(bridge);
    glutSwapBuffers();
  }
  //cout << "Fitness: ";
  //bridge->calculateFitness();
  cout << "Animation done, convergence found..." << endl;
}

// returns 10 best bridges
vector<Bridge*> evaluateBridge(vector<Bridge*> bridges)
{
  cout << "checking " << bridges.size() << " bridges" << endl;
  vector<Bridge*> best_bridges;

  for (int n = 0; n < 10; n++) {
    int best_score = 0.0;
    Bridge* best_bridge;

    for (Bridge* bridge : bridges) {
      bool converged = false;
      int iter = 0;
      while(!converged && iter<1000) {
         for(int i = 0; i < 5; i++) {
            converged = bridge->calculateForce();
         }
      }
      int fitness_score = bridge->calculateFitness();
      if (fitness_score > best_score) {
        best_score = fitness_score;
        best_bridge = bridge;
      }
      iter++;
    }
    best_bridges.push_back(best_bridge);
  }
  cout << "Done selecting 10 best bridges..." << endl << endl;
  return best_bridges;
}

// generates 10 new bridges from each bridge
vector<Bridge*> evolveBridge(vector<Bridge*> bridges) {
  cout << "Generating 100 new bridges " << endl;
  vector<Bridge*> new_bridges;
  for (Bridge* bridge: bridges) {
    for (int i = 0; i < 10; i++) {
      Bridge* new_bridge = bridge->copy_jittered(0.1);
      //cout << new_bridge->getPoints().size() << endl;
      //cout << new_bridge->getBeams().size() << endl;
      new_bridges.push_back(new_bridge);
    }
  }
  cout << "Done creating 100 new bridges..." << endl << endl;
  return new_bridges;
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
    glVertex2f(beam->p1->x, beam->p1->y);
    glVertex2f(beam->p2->x, beam->p2->y);
  glEnd();
}

void drawPoint(Point* p) {
  double x = p->x;
  double y = p->y;
  glBegin(GL_POLYGON);
    if (p->fixed) glColor3f(0, 0, 1);
    else glColor3f(0, 1, 0); 
    glVertex3f(x - 0.02, y - 0.025, 0);
    glVertex3f(x + 0.02, y - 0.025, 0);
    glVertex3f(x, y + 0.025, 0);
  glEnd();
}