#include "Segment.h"
#include "Polygon.h"
#include "Point.h"
#include "RealizableSpadjor.h"
#include "SegmentedRealizableSpadjor.h"

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

  Point<2> a1{0,2},a2{4,-2},a3{8,2},a4{4,6};
  Point<2> b1{4,2},b2{8,-2},b3{12,2},b4{8,6};


  Polygon<2> red1{a1,a2,a3,a4};
  Polygon<2> blue1{b1,b2,b3,b4};
  Polygon<2> copy(red1);

  red1.PrintPolygon();
  blue1.PrintPolygon();
  copy.PrintPolygon();
  
  RealizableSpadjor<2> RS{red1};
  RS.Print();
  
  vector<Point<2>> v1{a1,a2,a3};
  vector<Point<2>> v2{b1,b2,b3,b4};
  SegmentedRealizableSpadjor<2> SRS{v1,v2};
  SRS.PrintSegmented();

  Point<2> is1{6,0},is2{6,3};
    vector<Point<2>> path1{b1,is1};
    vector<Point<2>> path2{is2,b1};
    vector<Point<2>> path3{is1,a3,is2};
    SegmentedRealizableSpadjor<2> first{path1,path2,path3};
    first.PrintSegmented();
     RealizableSpadjor<2> test = first.Pasting();
     test.Print();
    cout << a1.IsEqual(a2,10) << endl;

    Point<2> f1=a2-a1;
    Point<2>  f2=b4-b3;
    f1.PrintPoint();
    cout <<(f1.dot(f2))/(f1.norm(2)*f2.norm(2))<<endl;

    // PolygonCovering Test
    Point<2> out1{0,0},out2{2,0},out3{2,-2},out4{0,-2};
    Polygon<2> out{out1, out2,out3,out4};
    Point<2> in1{5,2},in2{6,3},in3{7,2},in4{6,1};
    Polygon<2> in{in1,in2,in3,in4};
    Polygon<2> loc = test.jordan[0];

    loc.box();
    cout<< loc.box()[0]<< loc.box()[1]<< loc.box()[2]<< loc.box()[3] <<endl;
    cout<< in.box()[0]<< in.box()[1]<< in.box()[2]<< in.box()[3] <<endl;
    cout<< "out " << loc.PolygonCovering(out) <<endl;
    cout << "in " << (loc.PolygonCovering(in) )<<endl; 
 cout << "in " << (red1.PolygonCovering(in) )<<endl;
 cout << "in " << (blue1.PolygonCovering(in) )<<endl; 

 blue1.PolygonCovering(in);
    cout<< (1&&0);
    cout << (0&&1);
    cout<<test.BuildHasse().size()<< endl;
  return 0;
}
