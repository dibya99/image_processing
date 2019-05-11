#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
Mat src,gray,blu,result;
Mat black=Mat::zeros(src.size(),src.type());
int low_thresh=0;
 void call(int,void*)
{
  Canny(blu,result,low_thresh,low_thresh*2,3);
  src.copyTo(black,result);
  imshow("W4",result);
  imshow("W5",black);


}
int main(int argc,char** argv)
{
  src=imread(argv[1],IMREAD_COLOR);
  cvtColor(src,gray,COLOR_BGR2GRAY);
  blur(gray,blu,Size(2,2));
  namedWindow("W1",WINDOW_NORMAL);
  namedWindow("W2",WINDOW_NORMAL);
  namedWindow("W3",WINDOW_NORMAL);
  namedWindow("W4",WINDOW_NORMAL);
  namedWindow("W5",WINDOW_NORMAL);
  createTrackbar("thresh","W4",&low_thresh,100,call);
  imshow("W1",src);
  imshow("W2",gray);
  imshow("W3",blu);
  char ch=waitKey(0);
  if (ch=='k')
  std::exit(0);
}
