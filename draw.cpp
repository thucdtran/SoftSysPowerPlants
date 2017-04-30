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
void evolveBridge(vector<Bridge *> *bridges, int road_points,double max_dist_between_points);
vector<Bridge *> generateMultipleBridges(int road_points, int n, double max_dist_between_points,int quantityOfBridges);

using namespace std;
using namespace std::this_thread; // For sleep
using namespace std::chrono;  // For sleep

// Initializes GLUT, the display mode, and main window; registers callbacks;
// enters the main event loop.
int main(int argc, char** argv) {
    srand(time(NULL));
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


    //Generates a bridge pointer vector
    vector<Bridge*> bridges(50);
    //Fill the vector with random bridges. 
    bridges = generateMultipleBridges(15, 1, 1, 50);

    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
    
    //Tries to evolve our bridges. 
    for(int x = 0; x<1000; x++)
    {
        evolveBridge(&bridges, 15,1);
        //Draws to screen the best bridge. 
        glClear(GL_COLOR_BUFFER_BIT);
        drawBridge(bridges[0]);
        glutSwapBuffers();
    }
    cout<<"done evolving\n";
    glutMainLoop();
}

//Returns the bridge that is more fit. True if a is better, b otherwise. 
bool bridgeComp(Bridge* a, Bridge* b)
{
    return a->fitness<b->fitness;
}

//Generates a vector of bridges.
vector<Bridge *> generateMultipleBridges(int road_points, int n, double max_dist_between_points,   int quantityOfBridges){
  
  vector <Bridge *> allBridges(quantityOfBridges);
  //Generates a new bridge for each one. 
  for(int x = 0; x<quantityOfBridges; x++)
  {
    allBridges[x] = new Bridge();
    allBridges[x]->generateBridge(n, max_dist_between_points, road_points);
    allBridges[x]->stripBridge();
  }
  //Sorts by fitness. 
  sort(allBridges.begin(), allBridges.end(), bridgeComp);
  return allBridges;
}


//Takes in a vector of bridges, and acts on it to produce a new set of 
//Hopefully better bridges. 
void  evolveBridge(vector<Bridge *> *bridges, int road_points,double max_dist_between_points)
{
  //Assumption is that the bridge is already sorted coming in. 
  //We keep the 30 best bridges of the previous generation


  //Generating 15 new bridges entirely
  for(int x=30; x<45; x++)
  {
        Bridge* bridge = new Bridge();
        bridge->generateBridge(rand()%25, max_dist_between_points, road_points);
        (*bridges)[x] = bridge;
  }

  //Tries to use genetic crossover to make new bridges.
  for(int x= 45; x<bridges->size(); x++)
  {
    //Picks between the top ten bridges. 
    int a = rand()%10;
    int b = rand()%10;
    //Creates a new bridge based off of the A-th and B-th best bridges. 
    (*bridges)[x] = new Bridge((*bridges)[a], (*bridges)[b], max_dist_between_points);
    (*bridges)[x]->mutateBridge();
    (*bridges)[x]->stripBridge();
  }
   
   //Attempt to multithread the gradient descent step of our simulation
  vector<thread> threads;
  for (int x = 0; x< bridges->size(); x++){
    threads.push_back(thread(convergeBridge, (*bridges)[x], road_points));
  }

  for(int i = 0; i<bridges->size(); i++)
  {
    threads[i].join();
  }

  //Calculates the fitness of each newly simulated bridge. 
  for(int x = 0; x<50;x++){
    (*bridges)[x]->calculateFitness();
  }
  //Sorts the bridges based on our fitness function. 
  sort(bridges->begin(), bridges->end(), bridgeComp);

  return;

}

//Simulates the bridge over time. 
void convergeBridge(Bridge * bridge, int road_points)
{

    bool converged = false;
    int iter = 0;
    //Only does 2000 iterations here due to time constraint.
    while(!converged && iter<2000) {
       for(int i = 0; i < 5; i++) {
          converged = bridge->calculateForce(road_points);
       }
       iter++;
    }
}

//Draws the bridge to the buffer. 
void drawBridge(Bridge* bridge) {
  for (Beam* beam : bridge->getBeams()) {
    drawBeam(beam);
  }
  for (Point* point : bridge->getPoints()) {
    drawPoint(point);
  }
}

//Draws each beam on the bridge. 
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

//Draws each point on the bridge. 
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