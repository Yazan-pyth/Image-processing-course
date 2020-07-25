#include"opencv2/highgui/highgui.hpp"
#include<bits/stdc++.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;



int main (){
    Mat im;
    im=imread("gray.jpg");

if(im.empty())
{
    cout<<"Please check the image type or save it in the same place withe the code "<<endl;
    return 0;
}
    Mat gr(im.size(),CV_8UC1);

cvtColor(im,gr,CV_BGR2GRAY);
imshow("old",gr);
waitKey(0);
Mat ss(gr.size(),CV_8UC1);
Mat sss;
sss=gr.clone();
Mat s(gr.size(),CV_8UC1);
//cout<<gr.cols<<"  "<<gr.rows;
int m=gr.rows;
int n=gr.cols;
int randval;
for(int i=0;i<m;i++)
    for(int j=0;j<n;j++)
{
  randval=rand()%50;
  s.at<uchar>(i,j)=randval;
}

for(int i=0;i<m;i++)
    for(int j=0;j<n;j++)
    {
        if(s.at<uchar>(i,j)==49)
            gr.at<uchar>(i,j)=255;
        if(s.at<uchar>(i,j)==0)
            gr.at<uchar>(i,j)=0;

    }
  imshow("salt and pepper",gr);
waitKey(0);

int v;
cout<<"Enter mask size"<<endl;
cin>>v;
double a[v][v],y;
for(int i=0;i<v;i++)
    for(int j=0;j<v;j++)
    a[i][j]=1.0/(v*v);
    Mat lin=Mat::zeros(gr.size(),CV_8UC1);
 int mm=(v-1)/2;

    for(int i=v;i<m-v;i++)
        for(int j=v;j<n-v;j++)
    {
 long long p=0;
        for(int x=-(v-1)/2;x<(v+1)/2;x++)
            for(int y=-(v-1)/2;y<(v+1)/2;y++)
        {
            p=p+((a[mm+x][mm+y])*(gr.at<uchar>(i+x,j+y)));
        }
        lin.at<uchar>(i,j)=p;
    }
imshow("average filter",lin);
 waitKey(0);
cout<<"Enter the qaussian mask size"<<endl;
cin>>v;
cout<<"Enter  segma "<<endl;
double segma,pi=3.14;
cin>>segma;
    Mat gus=Mat::zeros(gr.size(),CV_8UC1);
mm=(v-1)/2;

    for(int i=v;i<m-v;i++)
        for(int j=v;j<n-v;j++)
    {
 long long p=0;
        for(int x=-(v-1)/2;x<(v+1)/2;x++)
            for(int y=-(v-1)/2;y<(v+1)/2;y++)
        {
            p=p+(((exp(-(x*x+y*y)/(2*segma*segma)))/(2*pi*segma*segma))*(gr.at<uchar>(i+x,j+y)));
        }
        gus.at<uchar>(i,j)=p;
    }
    imshow("gaussian",gus);
    waitKey(0);
//mean mask
cout<<"Enter mean mask size "<<endl;
cin>>v;
    Mat meani=Mat::zeros(gr.size(),CV_8UC1);
mm=(v-1)/2;
vector<int> men;
mm=(v-1)/2;
    for(int i=v;i<m-v;i++)
        for(int j=v;j<n-v;j++)
    {
 long long p=0;men.clear();
        for(int x=-(v-1)/2;x<(v+1)/2;x++)
            for(int y=-(v-1)/2;y<(v+1)/2;y++)
        {
           men.push_back(gr.at<uchar>(i+x,j+y));
        }
        sort(men.begin(),men.end());
       if(men.size()%2==0)
        gus.at<uchar>(i,j)=(men[(v*v)/2]+men[(v*v)/2-1])/2;
        else
         gus.at<uchar>(i,j)=men[(v*v-1)/2];
        meani.at<uchar>(i,j)=gus.at<uchar>(i,j);

}
    imshow("mean",meani);
   waitKey(0);
//unsharp mask
//coputing average mask first
double k;
cout<<"Enter k please for unsharp masking";
cin>>k;
mm=1;
    for(int i=1;i<m-1;i++)
        for(int j=1;j<n-1;j++)
    {
 long long p=0;
        for(int x=-1;x<2;x++)
            for(int y=-1;y<2;y++)
        {
            p=p+((a[mm+x][mm+y])*(sss.at<uchar>(i+x,j+y)));
        }
       //cout<<p<<endl;
        ss.at<uchar>(i,j)=p;

    }
    Mat unsharp=Mat::zeros(sss.size(),CV_8UC1);
      for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
        {
            unsharp.at<uchar>(i,j)=max((int)(sss.at<uchar>(i,j)*3-k*ss.at<uchar>(i,j)*3),0);
             unsharp.at<uchar>(i,j)= unsharp.at<uchar>(i,j)/3;
        }


        imshow("unsharp mask",unsharp);
        waitKey(0);
return 0;
}
