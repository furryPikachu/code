template <>
int Polygon<2>::PointPolygon(const Point<2> &q, Real tol) const
{
  // transform  coord.  make q = (0,0).
  Polygon<2> copy(*this);
  
  for (int i=0; i< copy.polygon.size(); i++)
      copy.polygon[i] = copy.polygon[i]-q;
  
  // add the fist point to the end of polygon to make it closed.
  copy.polygon.push_back(copy.polygon[0]);

  // check if q is on the edge.

  // count cross times for x axis.
  int Ucross;
  bool Ustrad;
  bool area;
  for (int i=0; i< copy.polygon.size()-1; i++)
    {
      Segment<2> edge{copy.polygon[i], copy.polygon[i+1]};
      if ( edge.PointInSegment(q,tol) )
	return 2;
      else
	{
	  Ustrad = (copy.polygon[i].coord[1] > tol) != (copy.polygon[i+1].coord[1] > tol);
	  area = copy.polygon[i].cross(copy.polygon[i+1] ) < tol;
	  if(Ustrad)
	    {
	      if((copy.polygon[i].coord[1]> tol) && (area))
		Ucross++;
	      else if ((copy.polygon[i+1].coord[1]> tol) && !(area))
		Ucross++;
	      }
	}
    }

  if (1==(Ucross & 1))		// Ucross is odd
    return 1;			// q in open Polygon
  else
    return 0;  
}



 
