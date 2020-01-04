template <> inline
RealizableSpadjor<2>  SegmentedRealizableSpadjor<2>::Pasting(Real tol)
{
  RealizableSpadjor<2> rs;
  vector<vector<Point<2>>> temp;

  Point<2> v1,v2;
  Polygon<2> poly;
  vector<vector<Point<2>>>::iterator it,it2,itcord,it3;
  Real cosang = 1,cosang1=1;
  bool sign = 1,sign1=1;			// 0 for smaller than 180, 1 for bigger than 180
  // Remove all self-loops in $E$ and insert them into ${\cal J}$.

    for(it = this->SRS.begin(); it != this->SRS.end(); ++it)
  	{
  	  if ( (*(it->begin())).IsEqual((*(it->end()-1)),tol) )
  		 // Point equal with tol
  	{
	  Polygon<2> t;
	  t.polygon=(*it);
  	  rs.jordan.push_back(t);
  	  this-> SRS.erase(it);
  	  it--;	  
  	}
  	}
    rs.Print();

    
  // Pasting
    while( !(this->SRS).empty() )
    {
      cout<< this->SRS.size()<<endl;
      it = this->SRS.begin();
      temp.push_back(*it);

      itcord=it+1;
      while(!temp.empty())
  	{
	  int count =0;
      for(it2 = it+1; it2 != this->SRS.end(); ++it2)
      	{
      	  if((*((temp.end()-1)->end()-1)).IsEqual( (*(it2->begin()) )) )
      	    { 
	      count ++;
	      if(count ==1)
		{v1=*((temp.end()-1)->end()-2)-*((temp.end()-1)->end()-1);
	       v1.PrintPoint();
      	       v2=*(it2->begin()+1)-*(it2->begin());
	       v2.PrintPoint();
      	      cosang =(v1.dot(v2))/(v1.norm(2)*v2.norm(2));
      	      sign = (v1.cross(v2) > tol);
	      itcord=it2;
		}
	      if(count>=2){
      	       v1=*((temp.end()-1)->end()-2)-*((temp.end()-1)->end()-1);
	       v1.PrintPoint();
      	       v2=*(it2->begin()+1)-*(it2->begin());
	       v2.PrintPoint();
      	      cosang1 =(v1.dot(v2))/(v1.norm(2)*v2.norm(2));
      	      sign1 = (v1.cross(v2) > tol);
	      
	      cout << cosang1 <<" "<< sign1<<endl;//
	      
      	      if(sign1<sign)
      		{
      		  sign=sign1;
		   cosang=cosang1;
      		  itcord=it2;
      		}
      	       if  (sign ==1 && sign1 == 1 && cosang1 <cosang)
      		{
      		  cosang=cosang1;
      		  itcord=it2;
      		}
	        if  (sign ==0 && sign1 == 0 && cosang1 >cosang)
      		{
      		  cosang=cosang1;
      		  itcord=it2;
      		}
	      } // end count
      	    }
	  cout << "for end" <<endl;  
      	}
      cout<<"next"<<endl;

      
       temp.push_back(*itcord);
      cout<<"temp"<<temp.size()<<endl;
      
      for(it3 = temp.begin(); it3!=temp.end(); ++it3)
	{
	   if(it3 != (temp.end()-1)){
	    
	    (*((temp.end()-1)-> end()-1 )).PrintPoint();//Test
	    (*(it3->begin())).PrintPoint();//Test
	    // form a loop
	  if ( (*(it3->begin())).IsEqual( (*((temp.end()-1)-> end()-1 )) ) )
	    {	   
  	    while( ! temp.empty())
  	      {
		cout<< "int while" <<endl;//Test
  	      poly.polygon.insert(poly.polygon.end(),it3->begin(),it3->end()-1);
	      cout<<"polysize:"<<poly.polygon.size()<<endl;
  	    temp.erase(it3);
  	    cout<<"temp:   "<<temp.size()<<endl;//Test
  	      }
	    poly.polygon.push_back(*(poly.polygon.begin()));
	    rs.jordan.push_back(poly);
	    
	    rs.Print();//Test
	    poly.polygon.clear();
	    cout<<poly.polygon.size()<<endl;
	    it3=temp.end()-1;
  	  }//end if
	  
	  }//if
	  
	}//end for
      cout<<"for"<<endl;
        this-> SRS.erase(itcord);
      cout<< this->SRS.size()<<endl;
	}//while temp
      
      this-> SRS.erase(it);
      cout<< this->SRS.size()<<endl;
    }//while srs
    
 rs.Print();
    return rs;
  
}
