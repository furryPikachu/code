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
    return 0;  //out
}


template <>
vector<Real> Polygon<2>::box(void) const
{
  vector<Real> temp{0,0,0,0};
  temp[0] = this->polygon.begin()->coord[0];
  temp[1] = this->polygon.begin()->coord[0];
  temp[2] = this->polygon.begin()->coord[1];
  temp[3] = this->polygon.begin()->coord[1];
  for(int i =0; i<this->polygon.size()-1;i++){
    temp[0] = min(temp[0],(this->polygon.begin()+1+i)->coord[0]);
 temp[1] = max(temp[1],(this->polygon.begin()+1+i)->coord[0]);
  temp[2] = min(temp[2],(this->polygon.begin()+1+i)->coord[1]);
  temp[3] = max(temp[3],(this->polygon.begin()+1+i)->coord[1]);
  }
  return temp;
}

template <>
bool Polygon<2>::PolygonCovering(const Polygon<2> &that, Real tol) const
{
  // box of polygon:x_min,x_max,y_min,y_max 
  bool inclu= 1;
  inclu= (((that.box()[0])-(this->box()[0]))>-tol) && inclu;
    inclu= (((this->box()[1])-(that.box()[1]) )>-tol) && inclu;
  inclu= (((that.box()[2])-(this->box()[2]))>-tol) && inclu;
    inclu= (((this->box()[3])-(that.box()[3]) )>-tol) && inclu;

    //cout<<"inclu"<<inclu<<endl;
  
  if(inclu==1)
    {
      // cout<<"in if "<<endl;
      Point<2> p1 = that.polygon[0];
      Point<2> p2 = that.polygon[1];
      int count=0;
      while((p1-p2).norm(2) >tol)
	{
	  //cout<<"in while "<<endl;
	   cout<<"";
	  count ++;
	  if( count > 100)
	    assert(!"inproper condition");
	  
	  if (this->PointPolygon(p1)==1)
	    {
	      //  cout<<"inpolygon";
	      return true;break;}
	  else if (this->PointPolygon(p1)==0)
	    {
	      //cout<<"in else if"<<endl;
	      return false;}
	  else
	    p1=(p1+p2)/2;
	  
	}
    }
  else
    return false;
  
}
 
