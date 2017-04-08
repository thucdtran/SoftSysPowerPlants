#include "Model.h"

Point::Point(double _x, double _y) {
  x = _x;
  y = _y;
}



Beam::Beam(Point* _p1, Point* _p2) {
  p1 = _p1;
  p2 = _p2;
}


Model::Model()
{
  std::cout<<"Initial Beam Count:"<<b.size()<<"\n";
  std::cout<<"Initial Point Count:"<<p.size()<<"\n";
  status = 0;

}

void Model::AddPoint(int _x, int _y)
{
  Point * P = new Point((_x-200.0)/200.0,-(_y-150.0)/150.0);
  p.push_back(P);
  drawPoint(P);
}

void Model::AddBeam(Point* _p1, Point* _p2)
{
  Beam * B = new Beam(_p1, _p2);
  b.push_back(B);
  drawLine(B);
}


void Model::mouse(int button, int state, int x, int y)
{
  AddPoint(x,y);
  if(status == 0)
  {

  }
  else if(status==1)
  {
    AddBeam(p.end()[-1], p.end()[-2]);
  }

  //Switches the buffer to display new content
  glutSwapBuffers();

}


void Model::keyboard(unsigned char key, int x, int y)
{
  //Insert keyboard specific code here. 
  std::cout<<"You just pressed:"<<key<<"!\n";
  if(key=='q')
    exit(0);
  if(key=='1')
    status = 1;
  if(key=='0')
    status = 0;

}
