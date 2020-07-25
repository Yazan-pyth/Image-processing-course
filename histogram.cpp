#include"opencv2/highgui/highgui.hpp"
#include<bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;
int main (){
//import the image
Mat img;
img=imread("hist.tif");
if(img.empty())
{
    cout<<"please check if you saved the code and the image in the same place"<<endl;
    return 0;
}
//convert the image to a gray image with 1 channel
Mat gray (img.size(), CV_8UC1);
cvtColor( img, gray, CV_BGR2GRAY );
//counting pixel values
long long a[299]={0};
for(int i=0;i<gray.cols;i++)
for(int j=0;j<gray.rows;j++)
    {int m=(int)gray.at<uchar>(Point(i,j));
        ++a[m];
    }
//find the maximum pixel iteration for image scaling to veiw the histogram
Mat im(300,255,CV_8UC1);
long long maxi=0;
for(int i=0;i<256;i++)
    maxi=max(maxi,a[i]);
//Drawing the Histogram
for(int i=0;i<256;i++ )
{
  line( im, Point(i,0) , Point(i,300-a[i]*300/maxi), Scalar(255,255,255));
    }
//veiw the histogram
namedWindow("Histogram");
imshow("Histogram",im);
waitKey(0);
//equalization process :
Mat cc=Mat::ones(300,255,CV_8UC1);
long long rep=0;
long long b[299]={0},m1[256];
double z;
int wid,lon;
wid=img.cols;
lon=img.rows;
for(int i=0;i<256;i++)
{if(a[i]!=0)
    {
        rep=rep+a[i];
        z=double(rep)/double(wid*lon);
        z=z*255;
        m1[i]=round(z);
        b[m1[i]]=a[i];
    }
    }
for(int i=0;i<256;i++ )
{
Point pt1,pt2;
  pt1.x=i;
  pt1.y=300;
  pt2.x=i;
  pt2.y=300-b[i]*300/maxi;
  line( cc, pt2,pt1, Scalar(100,100,100));

}
namedWindow("equalization");
imshow("equalization",cc);
waitKey(0);
//view the equalized image and the old one.
Mat hisim(gray.size(),CV_8UC1);
for(int i=0;i<gray.cols;i++)
    for(int j=0;j<gray.rows;j++)
    hisim.at<uchar>(i,j)=m1[gray.at<uchar>(i,j)];

namedWindow("image");
imshow("oldimage",img);
imshow("image",hisim);
waitKey(0);
//egualization between the new histogram and a given histogram
int o;
Mat gg=Mat::zeros(300,255,CV_8UC1);
int c[256]={0},mm=7000,h=12000,u=12000,r=0;
maxi=maxi/20;
for(int i=0;i<256;i++)
{
if(i<=20)
{
    u=u+(maxi-12000);
    c[i]=u;
}
if(i>20&&i<=40)
    {u=u-(maxi-12000);
    c[i]=u;}
if(i>40&&i<=180)
{
    h=h-12000/140;
    c[i]=h;
}
if(i>180&&i<=205)
{
    c[180]=0;
    r=r+8000/25;
    c[i]=r;
}
if(i>205&&i<=255)
{
    c[205]=8000;
    mm=mm-8000/50;
    c[i]=mm;
}
}
for(int i=0;i<256;i++)cout<<c[i]<<endl;waitKey(0);
int f[256]={0};
Mat egu=Mat::zeros(300,256,CV_8UC1);
int i=0;
/*while(i<256)
{
    for(int j=0;j<256;j++)
    {
        if((a[j]>(c[j]-75))&&(a[j]<(c[j]+75)))
        {
          //  cout<<i<<"  "<<a[i]<<"  "<<c[i]<<endl;
            line(egu,Point(i,300),Point(i,300-a[i]*300/(2*maxi)),Scalar(200,200,200));
            ++i;
            break;
        }
    }
}

for(int i=0;i<256;i++)
    {//cout<<c[i]<<endl;
        line( gg, Point(i,300),Point(i,300-c[i]*300/(10*maxi)), Scalar(100,100,100));}
       imshow("new",gg);*/
////////////////////////////
int trns[300];
for(int i=0;i<256;i++){
        int mini=200000;
    for(int j=0;j<256;j++){
        if(mini>abs(c[i]-a[j])){
            mini=abs(c[i]-a[j]);
            trns[j]=i;
        }
    }
}
Mat egf=Mat::zeros(gray.size(),CV_8UC1);

for(int i=0;i<wid;i++)
    for(int j=0;j<lon;j++)
{
    egf.at<uchar>(i,j)=trns[gray.at<uchar>(i,j)];
}
int aa[300];memset(aa,0,sizeof aa);
for(int i=0;i<gray.cols;i++)
for(int j=0;j<gray.rows;j++)
    {int m=(int)egf.at<uchar>(Point(i,j));
        ++aa[m];
    }
for(int i=0;i<256;i++)
    cout<<c[i]<<' '<<aa[i]<<endl;
waitKey(0);
imshow("final",egu);
imshow("rrr",egf);
waitKey(0);
waitKey(0);
return 0;
}
