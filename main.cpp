#include "Segment.h"
#include "Polygon.h"
#include "Point.h"
#include "RealizableSpadjor.h"

int main(int argc, char **argv)
{
  // Point<2> a{1,4},q1{0,0},q2{1,3},q3{2,3},q4{3,0},q5{2,-3}, q6{1,-3};
  // Point<2> b{5,6};
  //   Point<2> d{3,5.5}; 
  // a.PrintPoint();
  // Segment<2> s{a,b};
  // b=a;
  // b.PrintPoint();
  // Segment<2> g(s);
  // g.PrintSegment();
  // Polygon<2> p{a,b};
  // p.PrintPolygon();
  // Polygon<2> p1(p);
  // p1.PrintPolygon();
  // p1.PrintPath();
  
  // // test abs()
  // Point<2> c{-1,-3};

  // Segment<2> s2{c,d};
  // c.abs();
  // c.abs().PrintPoint();
  // // test cross
  // cout << "The cross: " << c.cross(a) << endl;
  // cout << "The dot: " << c.dot(a) << endl;
  //   cout <<  s.PointInSegment(d,0.1) << endl;
  // cout <<  s.PointInSegment(a,0.1) << endl;
  //    cout <<  s.PointInSegment(c,0.1) << endl;
  //  cout <<  s.PointInSegment(c,3) << endl;
  //   cout <<  s.PointInSegment(c,7.5) << endl;
  //   cout << "default tol = 0: "<< s.PointInSegment(c) << endl;   
  // cout << "norm:" << a.norm() << endl;
  // cout << "segment slope: " << s.slope() << endl;
  // cout << "Isparallel:s,g " << (s.IsParallel(g)) << endl;
  // cout << "Isparallel: " << (s.IsParallel(g,0)) << endl;
  // cout << "Isparallel: " << (s.IsParallel(s2,0)) << endl;
  // Point<2> r;
  
  // cout << "Intersection: " <<  endl;
  // (s.Intersection(s2)).PrintPoint();
  // cout << "s,s1 Position: " << s.Position(s2) << endl;
  // s.PrintSegment();g.PrintSegment();
  // cout << "s,g Position: " << g.Position(s) << endl;
  // cout <<  s.PointInSegment(g.endpoint[0],0.05) << endl;

  // Polygon<2> six{q1,q2,q3,q4,q5,q6};
  // six.ShowPath();
  // int judge = six.PointPolygon(c);
  // Point<2> c1{0,0.03};
  // cout << "PointPolygon:q1{0,0},q2{1,3},q3{2,3},q4{3,0},q5{2,-3}, q6{1,-3} " << judge << endl;
  //   cout << "PointPolygon:(0,0.03) q1{0,0},q2{1,3},q3{2,3},q4{3,0},q5{2,-3}, q6{1,-3} " << six.PointPolygon(c1) << endl;
  //    Point<2> c2{1,1};
  //    cout << "PointPolygon:(1,1) q1{0,0},q2{1,3},q3{2,3},q4{3,0},q5{2,-3}, q6{1,-3} " << six.PointPolygon(c2) << endl;
  //    Point<2> c3{1,0};
  //    cout << "PointPolygon:(1,0) q1{0,0},q2{1,3},q3{2,3},q4{3,0},q5{2,-3}, q6{1,-3} " << six.PointPolygon(c3,0.05) << endl;
  //    six.ShowPointLocation(c2);
  //    six.ShowPointLocation(c);
  //    six.ShowPolygon();
  //    six.ShowPath();
  //    RealizableSpadjor<2> RS{p,p1,six};
  //    RS.PrintRealizableSpadjor();
  //    RS.PrintSegmented();

  Point<2> a1{0,2},a2{4,0},a3{8,2},a4{4,6};
  Point<2> b1{4,2},b2{8,0},b3{12,2},b4{8,6};


  Polygon<2> red1{a1,a2,a3,a4};
  Polygon<2> blue1{b1,b2,b3,b4};

  red1.PrintPolygon();
  blue1.PrintPolygon();

  
     
  return 0;
}
