#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
Mat img,hsv,bl,gray,result,edge,net,img2;
int hthresh=5;
int h=0;
int hm=65;
int s=52;
int sm=171;int v=83;
int vm=255;
int ksize=19;
int ksize2=8;
int iterations=7;
Mat element;
int lowthreshold=100;
int para=1;
int x=11;
vector<Vec4i> lines;
int minlen=1;
int maxlinegap=15;
void job()
{
  bl=Mat::zeros(img.size(),img.type());
  hsv=Mat::zeros(img.size(),img.type());
  gray=Mat::zeros(img.size(),img.type());
  net=Mat::zeros(img.size(),img.type());
  img2=img.clone();
  if(ksize==0)
  ksize++;
  GaussianBlur(img,bl,Size(2*ksize+1,2*ksize+1),x);
//  GaussianBlur(bl,bl,Size(2*ksize+1,2*ksize+1),x);
  cvtColor(bl,hsv,COLOR_BGR2HSV);
  inRange(bl,Scalar(h,s,v),Scalar(hm,sm,vm),gray);
  element==getStructuringElement(MORPH_RECT,Size(ksize2,ksize2));
  //morphologyEx(gray,result,MORPH_CLOSE,element,Point(-1,-1),iterations);
  //morphologyEx(result,result,MORPH_DILATE,element,Point(-1,-1),iterations);
  //morphologyEx(result,result,MORPH_ERODE,element,Point(-1,-1),iterations);
  erode(gray,result,element);
  dilate(result,result,element);
  //dilate(result,result,element);
  Canny(result,edge,lowthreshold,lowthreshold*3);
  /*HoughLinesP(edge,lines,para,CV_PI/180,hthresh,minlen,maxlinegap);
  for( size_t i = 0; i < lines.size(); i++ )
{

    float angle=atan2(lines[i][3]-lines[i][1],lines[i][2]-lines[i][0])*180/CV_PI;
    cout<<angle<<endl;
    //cout<<Point(lines[i][0]);
    line( img2, Point(lines[i][0], lines[i][1]),
    Point( lines[i][2], lines[i][3]), Scalar(0,0,255),12,8);
}*/
vector<vector<Point> > contours;
vector<Vec4i> heirarchy;
findContours(edge,contours,heirarchy,RETR_TREE,CHAIN_APPROX_SIMPLE);
 vector<RotatedRect> minRect( contours.size() );
 for( size_t i = 0; i < contours.size(); i++ )
   { minRect[i] = minAreaRect( Mat(contours[i]) );

   }
   for( size_t i = 0; i< contours.size(); i++ )
    {
      Scalar color = Scalar(0,0,255 );
      // contour
    //  drawContours( img2, contours, (int)i, color, 1, 8, vector<Vec4i>(), 0, Point() );
      // ellipse

      Point2f rect_points[4]; minRect[i].points( rect_points );
      for( int j = 0; j < 4; j++ )
         line( img2, rect_points[j], rect_points[(j+1)%4], color, 1, 8 );
         cout<<minRect[i].angle<<endl;
    }

}
void show()
{
  imshow("W1",img);
  imshow("W2",bl);
  imshow("W3",gray);
  imshow("W4",result);
  imshow("W5",edge);
  imshow("W6",img2);
    //waitKey(15);
}
int main(int argc,char** argv)
{
  char ch='A';
  VideoCapture cap(argv[1]);
  namedWindow("W1",WINDOW_FREERATIO);
 namedWindow("W2",WINDOW_FREERATIO);
  namedWindow("W3",WINDOW_FREERATIO);
  namedWindow("W4",WINDOW_FREERATIO);
  namedWindow("W5",WINDOW_FREERATIO);
  namedWindow("W6",WINDOW_FREERATIO);
  createTrackbar("ksize2","W4",&ksize2,16,NULL);
  createTrackbar("iterations","W4",&iterations,40,NULL);
  createTrackbar("ksize","W2",&ksize,60,NULL);
  createTrackbar("h","W3",&h,255,NULL);
  createTrackbar("hm","W3",&hm,255,NULL);
  createTrackbar("s","W3",&s,255,NULL);
  createTrackbar("sm","W3",&sm,255,NULL);
  createTrackbar("v","W3",&v,255,NULL);
  createTrackbar("vm","W3",&vm,255,NULL);
  createTrackbar("th","W5",&lowthreshold,300,NULL);
  createTrackbar("hthresh","W6",&hthresh,15,NULL);
  createTrackbar("para","W6",&para,250,NULL);
  createTrackbar("SIGMAX","W2",&x,18,NULL);
  createTrackbar("ML","W6",&minlen,30,NULL);
  createTrackbar("MLG","W6",&maxlinegap,30,NULL);
  //cout<<cap.isOpened();
  while(cap.isOpened())
  {

    cap>>img;
    //imshow("W1",img);
    //waitKey(10);
    //job();
    //show();
   ch=waitKey(20);
    if(ch== ' ')
    {

      while(1)
      {
        ch=waitKey(20);
        if(ch==' ')
        break;
        else if(ch=='k')
        exit(0);
        job();
        show();
      }
    }
    else if(ch=='k')
    break;
    else
    {
    job();
    show();
  }
  }
}
