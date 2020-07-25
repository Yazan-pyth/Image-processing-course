#include<bits/stdc++.h>
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include<opencv2/core/core.hpp>
#include"opencv2/imgproc/imgproc.hpp"
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/legacy/legacy.hpp>    //BruteForceMatcheに必要。opencv2.4で移動した？
using namespace std;
using namespace cv;
int index;
  Mat grayImg1, grayImg2;
  string face[9]={"101.jpg","102.jpg","103.jpg","104.jpg","105.jpg","106.jpg","107.jpg","100.jpg"};
  string base[17]={"1.jpg","2.jpg","3.jpg","4.jpg","6.jpg","7.jpg","8.jpg","9.jpg","11.jpg","12.jpg","13.jpg","14.jpg"};


int main(int argc, char *argv[])
{
    //画像読み込み
    for(int x=0;x<8;x++)
    {
        cout<<"The face is ...."<<x+1<<endl;
    Mat colorImg1 = imread(face[x]);
    float m=200000;
    for(int i=0;i<12;i++)
    {
    Mat colorImg2 = imread(base[i]);
    if(colorImg1.empty() || colorImg2.empty()){
        cout << "No Image" << endl;
        return -1;
    }


    cvtColor(colorImg1, grayImg1, CV_BGR2GRAY);
    normalize(grayImg1, grayImg1, 0, 255, cv::NORM_MINMAX);
    cvtColor(colorImg2, grayImg2, CV_BGR2GRAY);
    normalize(grayImg2, grayImg2, 0, 255, cv::NORM_MINMAX);
        //SURF
   // cv::SurfFeatureDetector detector(6000);
   // cv::SurfDescriptorExtractor extractor;

    //SIFT
    SiftFeatureDetector detector;
    SiftDescriptorExtractor extractor;
    vector<cv::KeyPoint> keypoints1;
    keypoints1.clear();
    detector.detect(grayImg1, keypoints1);
    vector<cv::KeyPoint> keypoints2;
    keypoints2.clear();
    detector.detect(grayImg2, keypoints2);

    Mat descriptors1;
    extractor.compute(grayImg1, keypoints1, descriptors1);
    Mat descriptors2;
    extractor.compute(grayImg2, keypoints2, descriptors2);
    vector<cv::DMatch> matches,matchen;
    matches.clear();
    BruteForceMatcher<L2<float> > matcher;
    matcher.match(descriptors1, descriptors2, matches);
    int N=5;
   sort(matches.begin(),matches.end());
    nth_element(matches.begin(), matches.begin()+N-1, matches.end());
    matches.erase(matches.begin()+N, matches.end());
    double midis=100;
    for(int j=0;j<matches.size();j++)
    {
        double dist=matches[j].distance;
        midis=min(dist,midis);
        if((matches[j].distance)<=4*(midis))
                matchen.push_back(matches[j]);
    }
    sort(matchen.begin(),matchen.end());
    /*int sum=0;
    for(int j=0;j<matches.size();j++)
    {
        sum+=matches[j].distance;
    }

    if(sum<m&&i<5){ m=sum;index=i;}
*/
    Mat matchedImg;

    drawMatches(colorImg1, keypoints1, colorImg2, keypoints2, matchen, matchedImg,Scalar::all(-1),Scalar::all(-1),
                vector<char>(),DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    namedWindow("image", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
    imshow("image", matchedImg);
    cout<<i<<endl;
    waitKey(0);
    }
    }
    return 0;
}
