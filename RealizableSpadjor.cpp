template <>
vector<vector<int>> RealizableSpadjor<2>::BuildHasse(Real tol) const
{
  int quan=this->jordan.size();
  vector<int> zero (quan,0);
  vector<vector<int>> result(quan,zero);
  
  for(int i =0; i< quan;i++)
    for(int j =0; j!=i && j<quan; j++)
      result[i][j]=this->jordan[i].PolygonCovering(this->jordan[j]);

  return result;
  
}


template <>
bool RealizableSpadjor<2>::PathInRS(const vector<Point<2>> &p, Real tol) const
{
  return true;
}


template <>
SegmentedRealizableSpadjor<2>
RealizableSpadjor<2>::Cutting(const RealizableSpadjor<2> &that,
			      Real tol) const
{
 
  vector<Point<2>> vertex;
 
  for(int i =0; i< this->jordan.size(); i++)
    // for each edge in this -> jordan, get segment from this:s1
    for(int j =0 ; j < this-> jordan[i].polygon.size()-1;j++)
      {
	
	Segment<2> s1{this-> jordan[i].polygon[j],
	    this-> jordan[i].polygon[j+1]};
	
	for(int k =0; k< that.jordan.size(); k++)
	  // for each edge in that -> jordan, position of edges 
	  for(int l =0 ; l< that. jordan[k].polygon.size()-1;l++)
	    {
	    Segment<2> s2{that. jordan[k].polygon[l],
		that. jordan[k].polygon[l+1]};
	
	if(s1.Position(s2,tol)==1)
	  {
	  Point<2> p=s1.Intersection(s2,tol);
	  vertex.push_back(p);
	  
	  }
	
	if(s1.Position(s2,tol)==2)
	  {
	  Point<2> p1=s1.overlapPoints(s2,tol)[0];
	  Point<2> p2=s1.overlapPoints(s2,tol)[1];
	  vertex.push_back(p1);
	  vertex.push_back(p2);	  
	  }
		  
	  }//end for	
      }//end for

  //we get the intersection points set "vertex"

  vector<vector<Point<2>>> pathset;
  RealizableSpadjor<2> copythat(that);
  //begin cutting status: empty pathset and copythat = RealizableSpadjor that.
 

  // cut the "that" Realizable Spadjor
  //for each point in vertex(vector<Point<2>>)
      vector<Point<2>>::iterator it;      
      for( it  = vertex.begin(); it !=vertex.end(); it++)
	{
	  // check if *it in pathset
	  if(!pathset.empty())
	    {
	      vector<vector<Point<2>>>::iterator itpath=pathset.begin();
	      for(itpath;itpath!=pathset.end();itpath++)
		{
		  vector<Point<2>>::iterator itpoint;
   		  for(itpoint=(*itpath).begin();
		      itpoint!=(*itpath).end()-1;itpoint++)
		    {
		      Segment<2> s2{*itpoint,*(itpoint+1)};
		      if(s2.PointInSegment(*it,tol)==1) // *it cut the segment s2
			  {
			    if ((*it).IsEqual(s2.endpoint[0],tol) && itpoint!=(*itpath).begin())
			      {
				vector<Point<2>>::iterator itemp;
				 vector<Point<2>> temp;
				 for(itemp =(*itpath).begin(); itemp!=itpoint+1;itemp++)
				   temp.push_back(*itemp); // keep orientation
				 pathset.push_back(temp);
				 vector<Point<2>>::iterator itemp1;
				 vector<Point<2>> temp1;
				 for(itemp1=itpoint; itemp1!=(*itpath).end();itemp1++)
				   temp1.push_back(*itemp1);
				 pathset.insert(itpath,temp1);//need to erase *itpath
				 pathset.erase(itpath+1);
			      }
			    else if ( (*it).IsEqual(s2.endpoint[1],tol) && itpoint!=(*itpath).end()-1)
			      {
				vector<Point<2>>::iterator itemp;
				 vector<Point<2>> temp;
				 for(itemp =(*itpath).begin(); itemp!=itpoint+2;itemp++)
				   temp.push_back(*itemp); // keep orientation
				 pathset.push_back(temp);
				 vector<Point<2>>::iterator itemp1;
				 vector<Point<2>> temp1;
				 for(itemp1=itpoint+1; itemp1!=(*itpath).end();itemp1++)
				   temp1.push_back(*itemp1);
				 pathset.insert(itpath,temp1);//need to erase *itpath
				 pathset.erase(itpath+1);
			      }
			      else
			       {
				 vector<Point<2>>::iterator itemp;
				 vector<Point<2>> temp;
				 for(itemp =(*itpath).begin(); itemp!=itpoint+1;itemp++)
				   temp.push_back(*itemp); // keep orientation
				 temp.push_back(*it);
				 pathset.push_back(temp);
				 vector<Point<2>>::iterator itemp1;
				 vector<Point<2>> temp1;
				 temp1.push_back(*it);
				 for(itemp1=itpoint+1; itemp1!=(*itpath).end();itemp1++)
				   temp1.push_back(*itemp1);
				 pathset.insert(itpath,temp1);//need to erase *itpath
				 pathset.erase(itpath+1);
			       }
			    itpoint=(*itpath).end()-2;
			    // end the loop for path temp: no self-intersection
			    // go to next path
			  }
		    }//end for each segment
		}//end for each path
	      }
	  //check *it in copythat
	  if(!copythat.jordan.empty())
	    {
	for(int k =0; k< copythat.jordan.size(); k++)
	  {
	    for(int l =0 ;l< copythat.jordan[k].polygon.size()-1;l++)
	      {
		Segment<2> s2{copythat. jordan[k].polygon[l],
		    copythat. jordan[k].polygon[l+1]};
		if(s2.PointInSegment(*it,tol)==1)//*it should be in cutseg
		  {
		    if ((*it).IsEqual(s2.endpoint[0],tol))
		      {
			vector<Point<2>> temp;		 
			for(int i =l; i<copythat.jordan[k].polygon.size()-1;i++)
			  temp.push_back(copythat.jordan[k].polygon[i]);
			for(int i =0 ; i< l+1;i++)
			  temp.push_back(copythat.jordan[k].polygon[i]);
			pathset.push_back(temp);
		      }
		   else if ((*it).IsEqual(s2.endpoint[1],tol))
		      {
			vector<Point<2>> temp;		 
			for(int i=l+1;i<copythat.jordan[k].polygon.size()-1;i++)
			  temp.push_back(copythat.jordan[k].polygon[i]);
			for(int i =0 ; i< l+2;i++)
			  temp.push_back(copythat.jordan[k].polygon[i]);
			pathset.push_back(temp);
		      }
		   else
		     {
		       	vector<Point<2>> temp;
			temp.push_back(*it);
			for(int i=l+1;i<copythat.jordan[k].polygon.size()-1;i++)
			  temp.push_back(copythat.jordan[k].polygon[i]);
			for(int i =0 ; i< l+1;i++)
			  temp.push_back(copythat.jordan[k].polygon[i]);
			temp.push_back(*it);
			pathset.push_back(temp);		       
		     }
		  }//end if point *it in s2, cut polygon into path
		l=copythat.jordan[k].polygon.size()-1;
		//end for; no self-intersection polygon
	      }
	  }//end for polygon k in copythat
	    } // end if(!copythat.empty())
	}//for each vertex point, cut that into paths

     
      
       SegmentedRealizableSpadjor<2> result;
      // vector<vector<Point<2>>> result.SRS;
      for(int i =0; i<pathset.size();i++)
	if(this->PathInRS(pathset[i])==1)
	  result.SRS.push_back(pathset[i]);
      if(!copythat.jordan.empty())
	{
	for(int i=0; i< copythat.jordan.size(); i++)
	  if(this->PathInRS(copythat.jordan[i].polygon)==1)
	    result.SRS.push_back(copythat.jordan[i].polygon);
	}
      
      // this: cut Realizable Spadjor
      //Repeat the process

      pathset.clear();
      copythat.jordan=this->jordan;
  //begin cutting status: empty pathset and copythat = RealizableSpadjor this.

  // cut the "this" Realizable Spadjor
  //for each point in vertex(vector<Point<2>>)
      // vector<Point<2>>::iterator it;      
      for( it  = vertex.begin(); it !=vertex.end(); it++)
	{
	  // check if *it in pathset
	  if(!pathset.empty())
	    {
	      vector<vector<Point<2>>>::iterator itpath=pathset.begin();
	      for(itpath;itpath!=pathset.end();itpath++)
		{
		  vector<Point<2>>::iterator itpoint;
   		  for(itpoint=(*itpath).begin();
		      itpoint!=(*itpath).end()-1;itpoint++)
		    {
		      Segment<2> s2{*itpoint,*(itpoint+1)};
		      if(s2.PointInSegment(*it,tol)==1) // *it cut the segment s2
			  {
			    if ((*it).IsEqual(s2.endpoint[0],tol) && itpoint!=(*itpath).begin())
			      {
				vector<Point<2>>::iterator itemp;
				 vector<Point<2>> temp;
				 for(itemp =(*itpath).begin(); itemp!=itpoint+1;itemp++)
				   temp.push_back(*itemp); // keep orientation
				 pathset.push_back(temp);
				 vector<Point<2>>::iterator itemp1;
				 vector<Point<2>> temp1;
				 for(itemp1=itpoint; itemp1!=(*itpath).end();itemp1++)
				   temp1.push_back(*itemp1);
				 pathset.insert(itpath,temp1);//need to erase *itpath
				 pathset.erase(itpath+1);
			      }
			    else if ( (*it).IsEqual(s2.endpoint[1],tol) && itpoint!=(*itpath).end()-1)
			      {
				vector<Point<2>>::iterator itemp;
				 vector<Point<2>> temp;
				 for(itemp =(*itpath).begin(); itemp!=itpoint+2;itemp++)
				   temp.push_back(*itemp); // keep orientation
				 pathset.push_back(temp);
				 vector<Point<2>>::iterator itemp1;
				 vector<Point<2>> temp1;
				 for(itemp1=itpoint+1; itemp1!=(*itpath).end();itemp1++)
				   temp1.push_back(*itemp1);
				 pathset.insert(itpath,temp1);//need to erase *itpath
				 pathset.erase(itpath+1);
			      }
			      else
			       {
				 vector<Point<2>>::iterator itemp;
				 vector<Point<2>> temp;
				 for(itemp =(*itpath).begin(); itemp!=itpoint+1;itemp++)
				   temp.push_back(*itemp); // keep orientation
				 temp.push_back(*it);
				 pathset.push_back(temp);
				 vector<Point<2>>::iterator itemp1;
				 vector<Point<2>> temp1;
				 temp1.push_back(*it);
				 for(itemp1=itpoint+1; itemp1!=(*itpath).end();itemp1++)
				   temp1.push_back(*itemp1);
				 pathset.insert(itpath,temp1);//need to erase *itpath
				 pathset.erase(itpath+1);
			       }
			    itpoint=(*itpath).end()-2;
			    // end the loop for path temp: no self-intersection
			    // go to next path
			  }
		    }//end for each segment
		}//end for each path
	      }
	  //check *it in copythat
	  if(!copythat.jordan.empty())
	    {
	for(int k =0; k< copythat.jordan.size(); k++)
	  {
	    for(int l =0 ;l< copythat.jordan[k].polygon.size()-1;l++)
	      {
		Segment<2> s2{copythat. jordan[k].polygon[l],
		    copythat. jordan[k].polygon[l+1]};
		if(s2.PointInSegment(*it,tol)==1)//*it should be in cutseg
		  {
		    if ((*it).IsEqual(s2.endpoint[0],tol))
		      {
			vector<Point<2>> temp;		 
			for(int i =l; i<copythat.jordan[k].polygon.size()-1;i++)
			  temp.push_back(copythat.jordan[k].polygon[i]);
			for(int i =0 ; i< l+1;i++)
			  temp.push_back(copythat.jordan[k].polygon[i]);
			pathset.push_back(temp);
		      }
		   else if ((*it).IsEqual(s2.endpoint[1],tol))
		      {
			vector<Point<2>> temp;		 
			for(int i=l+1;i<copythat.jordan[k].polygon.size()-1;i++)
			  temp.push_back(copythat.jordan[k].polygon[i]);
			for(int i =0 ; i< l+2;i++)
			  temp.push_back(copythat.jordan[k].polygon[i]);
			pathset.push_back(temp);
		      }
		   else
		     {
		       	vector<Point<2>> temp;
			temp.push_back(*it);
			for(int i=l+1;i<copythat.jordan[k].polygon.size()-1;i++)
			  temp.push_back(copythat.jordan[k].polygon[i]);
			for(int i =0 ; i< l+1;i++)
			  temp.push_back(copythat.jordan[k].polygon[i]);
			temp.push_back(*it);
			pathset.push_back(temp);		       
		     }
		  }//end if point *it in s2, cut polygon into path
		l=copythat.jordan[k].polygon.size()-1;
		//end for; no self-intersection polygon
	      }
	  }//end for polygon k in copythat
	    } // end if(!copythat.empty())
	}//for each vertex point, cut that into paths

      
       for(int i =0; i<pathset.size();i++)
	if(that.PathInRS(pathset[i])==1)
	  result.SRS.push_back(pathset[i]);
       if(!copythat.jordan.empty())
	 {
	 for(int i=0; i< copythat.jordan.size(); i++)
	   if(this->PathInRS(copythat.jordan[i].polygon)==1)
	     result.SRS.push_back(copythat.jordan[i].polygon);
	 }
       
       return result;
}//end of function










  // vector<vector<Point<2>>> pathSet;
  // for(int k =0; k< that.jordan.size(); k++)
  //   {
  //     // cut polygon k to paths; keep orientition.     
  //   for(int l =0 ; l< that. jordan[k].polygon.size()-1;l++)
  //     {
  //     Segment<2> s2{that.jordan[k].polygon[l],
  // 		that. jordan[k].polygon[l+1]};
  //     bool _begin == 0;
  //     bool _end == 0;
  //     vector<Point<2>> cutseg{s1.endpoint[0],s1.endpoint[1]};//: store point that cut segment s2
  //     //init it with endpoints of s2
  //     vector<Point<2>>::iterator it;
  //     for( it  = vertex.begin(); it !=vertex.end(); it++)
  // 	{
  // 	  if(s2.PointInSegment(*it)==1)//*it should be in cutseg
  // 	    {
  // 	      if (*it..IsEqual(s2.endpoint[0],tol))
  // 		_begin ==1;
  // 	      if (*it..IsEqual(s2.endpoint[01],tol))
  // 		_end == 1;
  // 	      vector<Point<2>>::iterator it1= cutseg.begin();
  // 	      for( it1 ; it1 != cutseg.end(); it1++)//check repeated elements
  // 		//	if (!(*it1).IsEqual((*it),tol) && *it1.coord<)
  // 		//add *it to cutseg
  // 		  if(  (*it-*it1).coord[0] > tol
  // 		     && (*(it1+1)-*it).coord[0] > tol)
  // 		  cutseg.bush_back(*it)
  // 		    else if(  (*it-*it1).coord[0] > tol
  // 		     && (*(it1+1)-*it).coord[0] > tol)
  // 		  cutseg.bush_back(*it)
		    
  // 		cutsegment.push_back(vertex);
  // 	    }
  //     if(this->RSpoint())
  // 	}//for each vertex point 
      
  //     }//for each segment l
  //   }//for each polygon k

