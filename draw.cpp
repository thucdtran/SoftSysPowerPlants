// compile via 
// compile first: 
// g++ Point.h -std=
//
//  g++ draw.cpp -lm -lGL -lGLU -lglut -std=c++11 -o draw

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include "Generation.h"
#include <chrono>
#include <thread>
#include <random>

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void drawBridge(Bridge* bridge);
void drawBeam(Beam* beam);
void drawPoint(Point* p);
void convergeBridge(Bridge * bridge, int road_points);
void evolveBridge(vector<Bridge *> *bridges, int road_points,double k);
vector<Bridge *> generateMultipleBridges(int road_points, int n, double k);

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
  //bridge->generateBridge(10, .25,0);
  int road_points = 8;
  bridge->generateBridge(5, 1, road_points);

  // Beam* b = new Beam(p1, p2, r);
  // bridge->distributeLoad(Beam b, pair Force);

  drawBridge(bridge);
  glutSwapBuffers();
  vector<Bridge*> bridges(50);
  bridges = generateMultipleBridges(20, 1, 1);
  drawBridge(bridges[0]);
    glClear(GL_COLOR_BUFFER_BIT);
    drawBridge(bridges[0]);
    glutSwapBuffers();
  for(int x = 0; x<1000; x++)
   {
    evolveBridge(&bridges, road_points,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    drawBridge(bridges[0]);
    glutSwapBuffers();
    cout<<bridges[0]->get_points_size()<<"\n";
    }
  cout<<"done evolving\n";


  glutMainLoop();
}


bool bridgeComp(Bridge* a, Bridge* b)
{
    return a->fitness<b->fitness;
}

vector<Bridge *> generateMultipleBridges(int road_points, int n, double k){
  int quantityOfBridges = 50;
  vector <Bridge *> allBridges(quantityOfBridges);
 cout<<"test\n";
  for(int x = 0; x<quantityOfBridges; x++)
  {
    allBridges[x] = new Bridge();
    allBridges[x]->generateBridge(n, k, road_points);
    allBridges[x]->stripBridge();
  }

  sort(allBridges.begin(), allBridges.end(), bridgeComp);
  return allBridges;
}



void  evolveBridge(vector<Bridge *> *bridges, int road_points,double k)
{
  //Assumption is that the bridge is already sorted coming in. 
  for(int x=30; x<45; x++)
  {
        Bridge* bridge = new Bridge();
        bridge->generateBridge(5, 1, road_points);
        (*bridges)[x] = bridge;
  }
  for(int x= 45; x<bridges->size(); x++)
  {
    int a = rand()%10;
    int b = rand()%10;
    (*bridges)[x] = new Bridge((*bridges)[a], (*bridges)[b], k);
    (*bridges)[x]->mutateBridge();
    (*bridges)[x]->stripBridge();
  }
   
  vector<thread> threads;
  for (int x = 0; x< bridges->size(); x++){
    threads.push_back(thread(convergeBridge, (*bridges)[x], road_points));
  }

  for(int i = 0; i<bridges->size(); i++)
  {
    threads[i].join();
  }
  for(int x = 0; x<50;x++){
    (*bridges)[x]->calculateFitness();
  }
  sort(bridges->begin(), bridges->end(), bridgeComp);
  double fit = 0;
  for(int x = 0; x<50;x++){

      fit+=(*bridges)[x]->fitness;
  }
  cout<<fit/50.0<<"\n";
   return;

}


void convergeBridge(Bridge * bridge, int road_points)
{
    bool converged = false;
    int iter = 0;
    while(!converged && iter<2000) {
       for(int i = 0; i < 5; i++) {
          converged = bridge->calculateForce(road_points);
       }
       iter++;
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