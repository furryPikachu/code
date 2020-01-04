#ifndef POLYGON_H
#define POLYGON_H

#include "Point.h"
#include "Segment.h"

using namespace std;

/* suppose the input is a well-defined oriented polygon, no self-intersection */
/* use the points list to represent the polygon */

template <int dim>
class Polygon
{
 public:
  vector<Point<dim>> polygon;

 public:
  /* Default Constructor. */
  Polygon(){};
  /* Constructor. */
  Polygon(initializer_list<Point<dim>> p)
    {
      for (auto a : p)
	{
	  polygon.push_back(a);
	}
      polygon.push_back(*(p.begin()));
  }

  /* Copy Constructor. */
 Polygon(const Polygon<dim> &copy) : polygon(copy.polygon){}

  void PrintPolygon(void)
  {
    cout << "The Polygon: " << endl ;
    for (int j=0; j< polygon.size(); j++)
      {
      for (int i = 0; i< dim; i++)
	cout << polygon[j].coord[i] << " ";
      
    cout << "| " ;
  }
    cout << endl;
  }

  /* Found the relative location of a point with the polygon. */
  int PointPolygon(const Point<2> &q, Real tol=0.05) const;

  /* box of polygon:x_min,x_max,y_min,y_max */
  vector<Real> box(void) const;

  /* Compute the relative locations of two almost disjoint polygons. */
  bool PolygonCovering(const Polygon<dim> &that, Real tol=0.05) const;

  /* Show the position. */
  void ShowPointLocation(const Point<2> &q, Real tol = 0.05) const
  {
    int position = PointPolygon(q, tol);
    switch(position){
    case 0:
      cout << "Point out the Polygon." << endl;break;
    case 1:
      cout << "Point in the interior of Polygon." << endl;break;
    case 2:
      cout << "Point on the edge of Polygon." << endl;break;
    }
  }

  friend ostream &operator<<(ostream &os,
			     const Polygon<dim> &p)
  {
    
  }

  /* print Polygon */
  void ShowPolygon(void)
  {
    for(int j=0; j<polygon.size();j++)
      {
	cout<< "("  << polygon[j].coord[0];
	for (int i = 1; i<dim; i++)
	  {
	    cout <<", " << polygon[j].coord[i] ;
	  }
	cout << ") ";
      }
    cout << endl;	
  }

  /* print as path */
  void ShowPath(void)
  {
    for(int j=0; j<polygon.size()-1;j++)
      {
	cout<< "("  << polygon[j].coord[0];
	for (int i = 1; i<dim; i++)
	  {
	    cout <<", " << polygon[j].coord[i] ;
	  }
	cout << ") ";
      }
    cout << endl;
  }


   void PrintPath(void)
  {
    cout << "The Path: " << endl ;
    for (int j=0; j< polygon.size()-1; j++)
      {
      for (int i = 0; i< dim; i++)
	cout << polygon[j].coord[i] << " ";
      
    cout << "| " ;
  }
    cout << endl;
  }
  
};

#include "Polygon.cpp"
#endif
