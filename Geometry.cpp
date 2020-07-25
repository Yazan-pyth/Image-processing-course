#include"opencv2/highgui/highgui.hpp"
#include<bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#define _(i,j) at<uchar>(i,j)
using namespace std;
using namespace cv;
long long i,j;
void NN(Mat small)
{

        for(i=0;i<small.cols-1;i=i+2)
        for(j=0;j<small.rows-1;j=j+2)
    {
       small.at<uchar>(i,j+1)=small.at<uchar>(i,j);
       small.at<uchar>(i+1,j)=small.at<uchar>(i,j);
    small.at<uchar>(i+1,j+1)=small.at<uchar>(i,j);
    }
    imshow("NN resize",small);
    waitKey(0);
}
void masknne(Mat small)
{
    long long m=small.cols;
    long long n=small.rows;
    int a[3][3];
    a[0][0]=1;a[0][1]=1;a[0][2]=0;
    a[1][0]=1;a[1][1]=1;a[1][2]=0;
    a[2][0]=0;a[2][1]=0;a[2][2]=0;
     Mat nne=Mat::zeros(m,n,CV_8UC1);
     for(i=1;i<m-1;i++)
        for(j=1;j<n-1;j++)
     {
          long long p=0;
        for(int x=-1;x<2;x++)
            for(int y=-1;y<2;y++)
        {
            p=p+((a[1+x][1+y])*(small.at<uchar>(i+x,j+y)));
        }
        nne.at<uchar>(i,j)=p;
     }
     imshow("NN 2D",nne);
    waitKey(0);
}
void bil(Mat small)
{
    for(i=1;i<small.cols;i=i+2)
    for(j=1;j<small.rows;j=j+2)
    {
        small.at<uchar>(i-1,j)=(small.at<uchar>(i-1,j-1)+small.at<uchar>(i-1,j+1))/2;
         small.at<uchar>(i,j-1)=(small.at<uchar>(i-1,j-1)+small.at<uchar>(i+1,j-1))/2;
          small.at<uchar>(i+1,j)=(small.at<uchar>(i+1,j+1)+small.at<uchar>(i-1,j-1))/2;
           small.at<uchar>(i,j)=(small.at<uchar>(i-1,j)+small.at<uchar>(i+1,j))/2;
    }
    imshow("bilinear ",small);
    waitKey(0);
}
void maskbil(Mat small)
{
 /*   Mat dd=Mat::zeros(small.cols+2,small.rows+2,CV_8UC1);
    for(int i=1;i<dd.cols-1;i++)
        for(int j=1;j<dd.rows-1;j++)
    {
        dd.at<uchar>(i,j)=small.at<uchar>(i-1,j-1);
    }*/
    long long m=small.cols;
    long long n=small.rows;
    double a[3][3];
    a[0][0]=0.25;a[0][1]=0.5;a[0][2]=0.25;
    a[1][0]=0.5;a[1][1]=1;a[1][2]=0.5;
    a[2][0]=0.25;a[2][1]=0.5;a[2][2]=0.25;
     Mat nne=Mat::zeros(m,n,CV_8UC1);
     //imshow("ss",small);
    for(i=1;i<m-1;i++)
        for(j=1;j<n-1;j++)
    {

        long long p=0;
        for(int x=-1;x<2;x++)
            for(int y=-1;y<2;y++)
        {
            p=p+((a[1+x][1+y])*(small.at<uchar>(i+x,j+y)));
        }
        nne.at<uchar>(i,j)=p;
    }
    imshow("2D bilinear",nne);
    waitKey(0);
}
void bicub(Mat small)
{
    Mat cubic;
    cubic=small.clone();
    for(int i=3;i<small.cols-3;i=i+3)
        for(int j=3;j<small.rows-3;j=j+3)
    {
     cubic._(i,j+1)=cubic._(i,j) + 0.5 * cubic._(i,j+1)*(cubic._(i,j+2) - cubic._(i,j-1) +
                       cubic._(i,j+1)*(2.0*cubic._(i,j-1) - 5.0*cubic._(i,j) + 4.0*cubic._(i,j+2) -
                        cubic._(i,j+3) + cubic._(i,j+1)*(3.0*(cubic._(i,j) - cubic._(i,j+2)) + cubic._(i,j+3)-
                        cubic._(i,j-1))));
        cubic._(i+1,j)=cubic._(i,j) + 0.5 * cubic._(i+1,j)*(cubic._(i+2,j) - cubic._(i,j) +
                    cubic._(i+1,j)*(2.0*cubic._(i,j) - 5.0*cubic._(i,j) + 4.0*cubic._(i+2,j) -
                    cubic._(i+3,j) + cubic._(i+1,j)*(3.0*(cubic._(i,j) - cubic._(i+2,j)) + cubic._(i+3,j) -
                    cubic._(i,j))));
        cubic._(i+1,j+1)=cubic._(i+1,j) + 0.5 * cubic._(i+1,j+1)*(cubic._(i+1,j+2) - cubic._(i+1,j-1) +
                    cubic._(i+1,j+1)*(2.0*cubic._(i+1,j-1) - 5.0*cubic._(i+1,j) + 4.0*cubic._(i+1,j+2) -
                    cubic._(i+1,j+3) + cubic._(i+1,j+1)*(3.0*(cubic._(i+1,j) - cubic._(i+1,j+2)) +
                    cubic._(i+1,j+3) - cubic._(i+1,j-1))));
    }
    imshow("Cubic interpolation",small);
}
int main (){
Mat im;
im=imread("ss.jpg");
imshow("ds",im);
Mat gray(im.size(),CV_8UC1);
cvtColor(im,gray,CV_BGR2GRAY);
long long length,width;
width=gray.cols;
length=gray.rows;
Mat small=Mat::zeros(2*length,2*width,CV_8UC1);
long long m=small.cols;
long long n=small.rows;
for(i=0;i<m;i++)
    for(j=0;j<n;j++)
{
    if((i%2==0)&&(j%2==0))
        small.at<uchar>(i,j)=gray.at<uchar>(i/2,j/2);
    else
        small.at<uchar>(i,j)=0;
}
imshow("Zero interlave",small);

  Mat nne=Mat::zeros(small.size(),CV_8UC1);
  Mat ff;
  ff=small.clone();
NN(small);
masknne(ff);
bil(small);
maskbil(small);
bicub(small);
waitKey(0);
destroyAllWindows();
cvRelease();
return 0;
}
