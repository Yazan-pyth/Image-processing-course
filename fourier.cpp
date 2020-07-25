#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace std;
using namespace cv;

void shiftDFT(Mat& fImage )
{
  	Mat tmp, q0, q1, q2, q3;

	// first crop the image, if it has an odd number of rows or columns

	fImage = fImage(Rect(0, 0, fImage.cols & -2, fImage.rows & -2));

	int cx = fImage.cols/2;
	int cy = fImage.rows/2;

	// rearrange the quadrants of Fourier image
	// so that the origin is at the image center

	q0 = fImage(Rect(0, 0, cx, cy));
	q1 = fImage(Rect(cx, 0, cx, cy));
	q2 = fImage(Rect(0, cy, cx, cy));
	q3 = fImage(Rect(cx, cy, cx, cy));

	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
}


void create_butterworth_lowpass_filter(Mat &dft_Filter, int D, int n)
{
	Mat tmp = Mat(dft_Filter.rows, dft_Filter.cols, CV_32F);

	Point centre = Point(dft_Filter.rows / 2, dft_Filter.cols / 2);
	double radius;

	// based on the forumla in the IP notes (p. 130 of 2009/10 version)
	// see also HIPR2 on-line
	//log(dft_Filter,dft_Filter);
	for(int i = 0; i < dft_Filter.rows; i++)
	{
		for(int j = 0; j < dft_Filter.cols; j++)
		{
			radius = (double) sqrt(pow((i - centre.x), 2.0) + pow((double) (j - centre.y), 2.0));
			tmp.at<float>(i,j) = (float)
						( 1 / (1 + pow((double) (D /  radius), (double) (2 * n))));
		}
	}

    Mat toMerge[] = {tmp, tmp};
	merge(toMerge, 2, dft_Filter);

}
int main(int argc, char ** argv)
{
    const char* filename = argc >=2 ? argv[1] : "ss.png";
    Mat filter;
    Mat I = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
    if( I.empty())
        return -1;
    Mat padded;                            //expand input image to optimal size
    int m = getOptimalDFTSize( I.rows );
    int n = getOptimalDFTSize( I.cols ); // on the border add zero values
    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);         // Add to the expanded another plane with zeros
//log(complexI,complexI);
    dft(complexI, complexI);            // this way the result may fit in the source matrix
    Mat imgOutput;
    // compute the magnitude and switch to logarithmic scale
    // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
    split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
    magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    Mat magI = planes[0];

    magI += Scalar::all(1);                    // switch to logarithmic scale
    log(magI, magI);

    // crop the spectrum, if it has an odd number of rows or columns
    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

    // rearrange the quadrants of Fourier image  so that the origin is at the image center
    int cx = magI.cols/2;
    int cy = magI.rows/2;

    Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

    Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);
    Mat filterOutput;
    normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
                                            // viewable image form (float between values 0 and 1).
    imshow("Input Image"       , I   );    // Show the result
    imshow("spectrum magnitude", magI);
    waitKey();
    Mat img;
     filter = complexI.clone();
    create_butterworth_lowpass_filter(filter,2,2);
    shiftDFT(complexI);
            mulSpectrums(complexI, filter, complexI, 0);
            shiftDFT(complexI);
  cv::Mat inverseTransform;
   // cv::idft(complexI, inverseTransform, cv::DFT_INVERSE|cv::DFT_REAL_OUTPUT);
    //exp(inverseTransform,inverseTransform);
    normalize(inverseTransform, inverseTransform, 0,255, CV_MINMAX);
   /* for(int i=0;i<inverseTransform.rows;i++)
        for(int j=0;j<inverseTransform.cols;j++)
        cout<<(int)inverseTransform.at<uchar>(i,j)<<endl;*/
         idft(complexI, complexI);
//exp(complexI,complexI);
            // split into planes and extract plane 0 as output image

            split(complexI, planes);
            normalize(planes[0], imgOutput, 0, 1, CV_MINMAX);
cout<<"**";
            // do the same with the filter image

            split(filter, planes);
            normalize(planes[0], filterOutput, 0, 1, CV_MINMAX);


    imshow("Reconstructed", imgOutput);
    waitKey();
    long long lse=0;
    int ez=I.cols;
    int ee=I.rows;
for(int i=0;i<I.cols;i++)
    for(int j=0;j<I.rows;j++)
{
    lse=lse+pow(I.at<uchar>(i,j)-imgOutput.at<uchar>(i,j),2);

}
lse=lse/(ee*ez);

cout<<lse<<endl;
    return 0;
}
