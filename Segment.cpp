template <>
Real Segment<2>::slope() const
{
  Point<2> delta = endpoint[1]-endpoint[0];
  return (delta.coord[1] / delta.coord[0]);
}


template <> inline 
bool Segment<2>::PointInSegment(const Point<2> &p, Real tol) const
{
  Real mindist=0;
  bool signp1 = ((endpoint[0]-p).dot(endpoint[0]-endpoint[1]) > tol);
  bool signp2 = ((endpoint[1]-p).dot(endpoint[1]-endpoint[0]) > tol);
   if(signp1 != signp2)
     {
     if ((endpoint[0]-p).dot(endpoint[0]-endpoint[1]) <= tol)
       mindist = (endpoint[0]-p).norm();
     else
       mindist = (endpoint[1]-p).norm();
     }
   else
     mindist = fabs((endpoint[0]-p).cross((endpoint[1]-p)))/(2*((endpoint[0]-endpoint[1]).norm()));
   
   if (mindist < tol)
     return true;
   else
     return false;
}

template <>
bool Segment<2>::IsParallel(const Segment<2> &that, Real tol, Real M)
{
  Point<2> p1 = this->endpoint[0]-this->endpoint[1];
  Point<2> p2 = that.endpoint[0]-that.endpoint[1];
  if (  (p1/p1.norm(2)-p2/p2.norm(2)).norm(2) > tol/M)
    return false;
  else
    return true;
}

template <>
Point<2> Segment<2>::Intersection(const Segment<2> &that, Real tol, Real M)
{
  
  Point<2> p1=this->endpoint[0], p2=this->endpoint[1],p3=that.endpoint[0],p4=that.endpoint[1];
  Point<2> r;
  Real x1=p1.coord[0],y1=p1.coord[1],x2=p2.coord[0],y2=p2.coord[1];
  Real x3=p3.coord[0],y3=p3.coord[1],x4=p4.coord[0],y4=p4.coord[1];
  if(!this->IsParallel(that, tol, M))
    {
  r.coord[0]=((x1*y2-x2*y1)*(x4-x3)-(x3*y4-x4*y3)*(x2-x1))/((x1-x2)*(y4-y3)-(x3-x4)*(y2-y1));
  r.coord[1]=((x1*y2-x2*y1)*(y4-y3)-(x3*y4-x4*y3)*(y2-y1))/((x1-x2)*(y4-y3)-(x3-x4)*(y2-y1));
  return r;
    }
  else
    assert(!"Segments Parallel!");
}


template <>
vector<Point<2>> Segment<2>::overlapPoints(const Segment<2> &that, Real tol, Real M )
{
  vector<Point<2>> r;
  Point<2> p1=this->endpoint[0];
  Point<2> p2=this->endpoint[1];
   Point<2> p3=that.endpoint[0];
    Point<2> p4=that.endpoint[1];
       
    if(this->PointInSegment(p3,tol))
      r.push_back(p3);
    if(this->PointInSegment(p4,tol))
      r.push_back(p4);
    if(that.PointInSegment(p1,tol))
      r.push_back(p1);
    if(that.PointInSegment(p2,tol))
      r.push_back(p1);

    if(r[0].IsEqual(r[1],tol))
      r.erase(r.begin());
    vector<Point<2>> result{r[0],r[1]};
    return result;
    
}




template <>
int Segment<2>::Position( Segment<2> &that, Real tol, Real M)
{
  if(this->IsParallel(that, tol,M))
    {
      if((this->PointInSegment(that.endpoint[0],tol)) || (this->PointInSegment(that.endpoint[1],tol)) || (that.PointInSegment(this->endpoint[0],tol)) || (that.PointInSegment(this->endpoint[1],tol)))
      return 2;
    else
      return 0;
    }
  else if( this->PointInSegment(this->Intersection(that)) ||  that.PointInSegment(this->Intersection(that)))
    return 1;
  else
    return 0;
      
}
