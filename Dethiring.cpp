#include"opencv2/highgui/highgui.hpp"
#include<bits/stdc++.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
void q1()
{
 Mat img;
    int n,m,x,y;
img=imread("gr2.jpg");
Mat grayscaleMat (img.size(), CV_8UC1);
cvtColor( img, grayscaleMat, CV_BGR2GRAY );
Mat b(img.size(), CV_8UC1);
cvtColor( img,b, CV_BGR2GRAY );
Mat a(grayscaleMat.size(), grayscaleMat.type());
int d[4][4]={0,128,32,160,192,64,224,96,48,176,16,144,240,112,208,80};
for(int i=0;i<a.rows;i++)
{
    for(int j=0;j<a.cols;j++)
       {
        x=i%4;
        y=j%4;
        grayscaleMat.at<uchar>(i,j)=d[x][y];
        if((grayscaleMat.at<uchar>(i,j))>(b.at<uchar>(i,j)))
            a.at<uchar>(i,j)=255;
            else
             a.at<uchar>(i,j)=0;
    //cout<< int(a.at<uchar>(i,j));

        }
}
        imshow("I",img);
imshow("I'",a);
//imshow("b",b);
waitKey(0);
}
void q2()
{
    int q[4][4],d1[4][4],z;
    Mat img;
    int n,m,x,y;
img=imread("gr2.jpg");
Mat grayscaleMat (img.size(), CV_8UC1);
cvtColor( img, grayscaleMat, CV_BGR2GRAY );
Mat b(img.size(), CV_8UC1);
cvtColor( img,b, CV_BGR2GRAY );
Mat a(grayscaleMat.size(), grayscaleMat.type());
int d[4][4]={0,128,32,160,192,64,224,96,48,176,16,144,240,112,208,80};

//imwrite("des.jpg",a);
//namedWindow("2");

cin>>n;
m=255/(n-1);
for(int i=0;i<a.rows;i++)
{
    for(int j=0;j<a.cols;j++)
       {

        x=i%4;
        y=j%4;
        q[x][y]=grayscaleMat.at<uchar>(i,j)/m;
        d1[x][y]=d[x][y]%m;
        z=grayscaleMat.at<uchar>(i,j)-m*q[x][y];
        if(z>d1[x][y])
            b.at<uchar>(i,j)=q[x][y]+1;
            else
             b.at<uchar>(i,j)=q[x][y]+0;
    if( (b.at<uchar>(i,j))==1)
         (b.at<uchar>(i,j)=128);
    else
    if( (b.at<uchar>(i,j))==2)
     (b.at<uchar>(i,j)=255);
        }
}
imshow("I",img);
//imshow("I'",a);
imshow("b",b);
waitKey(0);

}
void q3()
{
 Mat img;
    int n,m,x,y;
img=imread("gr2.jpg");
Mat grayscaleMat (img.size(), CV_8UC1);
cvtColor( img, grayscaleMat, CV_BGR2GRAY );
Mat b(img.size(), CV_8UC1);
cvtColor( img,b, CV_BGR2GRAY );
Mat a(grayscaleMat.size(), grayscaleMat.type());
int d[4][4]={0,128,32,160,192,64,224,96,48,176,16,144,240,112,208,80};
for(int i=0;i<a.rows-1;i++)
{
    for(int j=0;j<a.cols-1;j++)
    {
       if(grayscaleMat.at<uchar>(i,j)<128)
            a.at<uchar>(i,j)=b.at<uchar>(i,j);
            else
            a.at<uchar>(i,j)=b.at<uchar>(i,j)-255;
     b.at<uchar>(i,j+1)=b.at<uchar>(i,j+1)+7/16*a.at<uchar>(i,j);
     b.at<uchar>(i+1,j-1)=b.at<uchar>(i+1,j-1)+3/16*a.at<uchar>(i,j);
     b.at<uchar>(i+1,j)=b.at<uchar>(i+1,j)+5/16*a.at<uchar>(i,j);
     b.at<uchar>(i+1,j+1)=b.at<uchar>(i+1,j+1)+1/16*a.at<uchar>(i,j);

     if(b.at<uchar>(i,j)<128)
     b.at<uchar>(i,j)=0;
     else
        b.at<uchar>(i,j)=255;
    }
}
imshow("b",b);
waitKey(0);
}
int main (){
  //q1();
    //q2();
    q3();

return 0;
}
