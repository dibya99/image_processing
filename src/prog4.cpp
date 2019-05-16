#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(int argc,char **argv)
{
  Mat img,gray,cannyout;
  img=imread(argv[1],IMREAD_COLOR);
  int h=0;
  int hm=23;
  int s=132;
  int sm=255;
  int v=44;
  int vm=163;
  int lthres=250;
  int erosion_size=1;
  int miny;
  int minx;
  int midx;
  minx=midx=INT_MAX;
  miny=0;
  vector<vector<Point> > contours;
vector<Vec4i> hierarchy;

  namedWindow("W1",WINDOW_FREERATIO);
  namedWindow("W2",WINDOW_FREERATIO);
  createTrackbar("h","W2",&h,255,NULL);
  createTrackbar("hm","W2",&hm,255,NULL);
  createTrackbar("s","W2",&s,255,NULL);
  createTrackbar("sm","W2",&sm,255,NULL);
  createTrackbar("v","W2",&v,255,NULL);
  createTrackbar("vm","W2",&vm,255,NULL);

    cvtColor(img,gray,COLOR_BGR2HSV);
    //blur(gray,gray,Size(9,9));
    inRange(gray,Scalar(h,s,v),Scalar(hm,sm,vm),gray);
    Mat element = getStructuringElement( 0,
                                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                       Point( erosion_size, erosion_size ) );

  /// Apply the erosion operation
  erode( gray, gray, element );
    imshow("W2",gray);
    Canny(gray,cannyout,lthres,3*lthres);
    imshow("W3",cannyout);
    findContours( cannyout, contours, hierarchy,
    RETR_CCOMP, CHAIN_APPROX_SIMPLE );
// iterate through all the top-level contours,
// draw each connected component with its own random color
/*int idx = 0;
for( ; idx >= 0; idx = hierarchy[idx][0] )
{
    Scalar color(0,0,255 );
    drawContours( img, contours, idx, color, FILLED, 8, hierarchy );
}*/
Point2f P[contours.size()];
vector<RotatedRect> minRect( contours.size() );

for( size_t i = 0; i < contours.size(); i++ )
     {
        minRect[i] = minAreaRect( Mat(contours[i]) );
    }
    for( size_t i = 0; i< contours.size(); i++ )
   {
     Scalar color = Scalar( 0,0,255) ;
     Point2f rect_points[4]; minRect[i].points( rect_points );
     for( int j = 0; j < 4; j++ )
        line( img, rect_points[j], rect_points[(j+1)%4], color,1,8);
   }
   for(size_t i=0;i<contours.size();i++)
   {
     //cout<<contours.size();
     P[i]=minRect[i].center;
  }

for(size_t i=0;i<contours.size();i++)
{
  cout<<P[i]<<endl;
  if(int(P[i].x)<minx)
  {
    midx=minx;
    minx=int(P[i].x);
  }
  else if(int(P[i].x)<midx && int(P[i].x)!=minx)
  midx=int(P[i].x);
  if(int(P[i].y)>miny)
  miny=int(P[i].y);
}
Point2f Cent((midx+minx)/2,miny);
cout<<Cent<<endl;
circle(img,Cent,10,(255,0,0),-1,8);
imshow("W1",img);
    waitKey(0);



}
