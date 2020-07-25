#include"opencv2/highgui/highgui.hpp"
//opencv library
#include<bits/stdc++.h>
using namespace std;
using namespace cv;
int main(){
Mat img,image;
//define variables of type mat
int color,g,b,gray;
img=imread("rgb4.jpg");
Mat r(img.rows,img.cols,CV_8UC1);
//reading RGB image
image=img.clone();
//make a copy from the image
for(int i=0;i<img.rows;i++)
    for(int j=0;j<img.cols;j++)
{
    Vec3b chan = image.at<Vec3b>(i,j);
//chan is avector from 3 bits and image.at<>(i,j) help u to get the pixels value
uchar blue = chan.val[0]; //B
uchar green = chan.val[1];//G
uchar red = chan.val[2];//R
color=(blue+green+red)/3;//converting tp gray image
//image.at<Vec3b>(i,j)[1]=(blue+green+red)/3;
//image.at<Vec3b>(i,j)[2]=(blue+green+red)/3;
r.at<uchar>(i,j)=color;
}
// the next comment is a function can directly convert to gray image
//cvtColor(cc, img,COLOR_BGR2GRAY);
namedWindow("orginal pic");
imshow("orginal pic",img);
namedWindow("gray pic");
//displaying image
cout<<r.channels();
imshow("gray pic",r);
waitKey(0);
imwrite("gray.jpg",image);
return 0;
}
