#ifndef POINT_H
#define POINT_H

#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
#include<initializer_list>
using namespace std;

typedef double Real;
/* point or vector  in \mathbb{R}^{dim} */
/* set all members as public for efficient */
template <int dim>
class Point
{
 public:
  Real coord[dim];

 public:
  /* Default constructor. */
  Point(){};

  /* Constructor.  */
  Point(initializer_list<Real> q){
    for(int i=0; i<dim; i++)
      coord[i] = *(q.begin()+i);
  }
  void PrintPoint(void)
  {
    cout << "The vector: " << endl;
    for (int i = 0; i<dim; i++)
      {
	cout << coord[i] << " ";
      }
    cout << endl;
  }
  /* The copy constructor */
  Point (const Point<dim> &copy) {
    for(int i= 0; i< dim; i++)
      this->coord[i]= copy.coord[i];
  }
  

  /* vector: The dot product */
  Real dot(const Point<dim> &that) const{
    Real value = 0;
    for (int i=0; i<dim; i++)
      value += this->coord[i]* that.coord[i];
    return value;
  }

  /* vector: The cross product in dim 2 */
  Real cross(const Point<dim> &that) const; 


  /* absolute value of coordinate. */
  Point<dim> abs() const
    {
      Point<dim> a;
      for(int i = 0; i< dim; i++)
	a.coord[i] = fabs(coord[i]);
      return a;
    }
  
  /* vector flex: vector/constant */
  Point<dim> operator/(const Real coefficient) const{
    Point<dim> r;
    for(int i=0; i<dim; i++)
      r.coord[i]= (this->coord[i])/coefficient;
    return r;
  }

  /* element-wise addition  */
  Point<dim> operator+(const Point<dim> &that) const {
    Point<dim> r;
    for(int i =0; i<dim; i++)
      r.coord[i] = this->coord[i] + that.coord[i];
    return r;
  }
  
  /* element-wise substraction to product a vector */
  Point<dim> operator-(const Point<dim> &that) const {
    Point<dim> r;
    for(int i=0; i<dim; i++)
      r.coord[i]= this->coord[i] - that.coord[i];
    return r;
  }

  /* vector: norm 2 or infty */
  Real norm(int type = 2){
    switch(type) {
    case 2:
      return sqrt(this->dot(*this));
    case 0:
      {
	Point<dim> a = this-> abs();
	return *(max_element(a.coord,a.coord+dim));
      }
    }
    assert(!"Unsupported norm type");
  }
bool  IsEqual(const Point<dim> &that, Real tol=0.05 , int type = 2) const {
    if( (*this-that).norm(type) - tol > 0)
      return false;
    else
      return true;
  }
  
  
};

#include "Point.cpp"
#endif  
