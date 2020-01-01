template <> inline
Real Point<2>::cross(const Point<2> &that) const
{
  return (this->coord[0]*that.coord[1]-this->coord[1]*that.coord[0]);
} 
