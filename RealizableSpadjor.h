#ifndef REALIZABLESPADJOR_H
#define REALIZABLESPADJOR_H

#include "Polygon.h"
//#include "SegmentedRealizableSpadjor.h"
/* Define a Relizable Spadjor. 
 * Consisted by a set of oriented Polygon
 */

/* Also reprented a segmented realizable spadjor
 * Since the end point in polygon is add manually 
 */

template <int dim>
class SegmentedRealizableSpadjor;

template <int dim>
class RealizableSpadjor
{
 public:
  vector<Polygon<dim>> jordan;
  

  /* Constructor. */
  RealizableSpadjor(initializer_list<Polygon<dim>> RS){
    for(int i=0; i<RS.size();i++)
      jordan.push_back(*(RS.begin()+i));
      }

  /* copy constructor. */
 RealizableSpadjor(const RealizableSpadjor<dim> &copy) : jordan(copy.jordan){}


  
 void  Print(void)
 {
   cout << "Realizable Spadjor: " <<
     jordan.size() << " Polygons." << endl;
    for(int j=0; j< jordan.size();j++)
      jordan[j].PrintPolygon();
  }
 /* Print as Segmented Realizable Spadjor */
  void  PrintSegmented(void)
 {
   cout << "Segmented Realizable Spadjor: " <<
     jordan.size() << " Paths." << endl;
    for(int j=0; j< jordan.size();j++)
      jordan[j].PrintPath();
 }

 
  /* Print HasseDiagram. */
  vector<vector<int>> BuildHasse(Real tol = 0.05) const;


  
  /* PathInRS:For cutting and decide wether the path in the RS */
  bool PathInRS(const vector<Point<2>> &p, Real tol=0.05) const;

  
  /* Cutting map */
  /*   Constructing Segmented Realizable Spadjor From Two Realizable
Spadjors */
  SegmentedRealizableSpadjor<2> Cutting(const RealizableSpadjor &that,
					Real tol=0.05) const;

  /* Default construct. */
 RealizableSpadjor(){}
 
};
#include "SegmentedRealizableSpadjor.h"
#include "RealizableSpadjor.cpp"
#endif	/* REALIZABLESPADJOR_H */
