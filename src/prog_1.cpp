#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(int argc,char **argv)
{
while(1)
{
int k_size;
Mat img;
img=imread("/home/dibya/images/image1.jpg",IMREAD_COLOR);
Mat result=Mat::zeros(img.size(),img.type());
erode(img,result,Size(k_size,k_size));
namedWindow("W1",WINDOW_FREERATIO);
namedWindow("W2",WINDOW_FREERATIO);
createTrackbar("k_size","W2",&k_size,200,NULL);
imshow("W1",img);
imshow("W2",result);
waitKey(100);
}
}




