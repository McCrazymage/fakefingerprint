#pragma once
#include <opencv2/opencv.hpp>

#define GRIDWIDTH 16
#define M_PI 3.1415926

using namespace cv;
using namespace std;
class FeatureExtract
{
public:
    FeatureExtract(void);
    FeatureExtract(Mat& inputImage,vector<double>& feature);
    double getAngleOfSubImg(Rect subRegion);//using private variable dx & dy.
    void gaborFilter(Rect subRegion,double angle,Mat& outputImage);
    ~FeatureExtract(void);
private:
    Mat img;
    Mat mask;
    Mat dx;
    Mat dy;
};

