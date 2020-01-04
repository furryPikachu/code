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
