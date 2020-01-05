#ifndef SEGMENT_H
#define SEGMENT_H

#include<iostream>
#include<vector>
#include "Point.h"
using namespace std;

/* typedef double Real */

/* Segment in \mathbb{R}^{dim}  */
/* constructed or repersented by  two points in Class Point */
template <int dim>
class Segment
{
 public:
  vector<Point<dim>> endpoint;
 public:
  
  /* Constructor. */
  Segment(initializer_list<Point<dim>> s){
    for(int i =0; i<2; i++)
      endpoint.push_back(*(s.begin()+i));
  }
  /* copy constructor. */
 Segment(const Segment<dim> &copy) : endpoint(copy.endpoint){}
  
  void PrintSegment(void)
  {
    for (int j =0; j<2; j++){
    for (int i = 0; i< dim; i++)
      {
	cout << endpoint[j].coord[i] << " "; 
      }
    cout << "|"<< " " ;
    }
    cout << endl;
  }

  bool PointInSegment(const Point<dim> &p, Real tol=0.05) const;

 public:
  /* slope() for 2-D  segment */
  Real slope() const;
  
  /* Test parallel. */
  bool IsParallel(const Segment<dim> &that, Real tol=0.05, Real M=1.0);
  
  /* Position for segments in plane: separation=0, intersection=1, overlap=2. */
  int  Position( Segment<2> &that, Real tol=0.05, Real M=1.0);
  
 public:
  /* When separation, caculate the intersection. */
  Point<2> Intersection(const Segment<dim> &that, Real tol=0.05, Real M=1.0);

  vector<Point<2>> overlapPoints(const Segment<dim> &that, Real tol= 0.05,Real M =1.0);

 
    
 protected:
  /* Default constructor. */
  Segment(){};
    
};

#include "Segment.cpp"	
#endif
