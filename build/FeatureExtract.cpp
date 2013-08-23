#include "FeatureExtract.h"

//将 DEPTH_8U型二值图像进行细化  经典的Zhang并行快速细化算法
void thin(const Mat &src, Mat &dst, const int iterations)
{
    const int height =src.rows -1;
    const int width  =src.cols -1;

    //拷贝一个数组给另一个数组
    if(src.data != dst.data)
    {
        src.copyTo(dst);
    }


    int n = 0,i = 0,j = 0;
    Mat tmpImg;
    uchar *pU, *pC, *pD;
    bool isFinished =false;

    for(n=0; n<iterations; n++)
    {
        dst.copyTo(tmpImg); 
        isFinished =false;   //一次 先行后列扫描 开始
        //扫描过程一 开始
        for(i=1; i<height;  i++) 
        {
            pU = tmpImg.ptr<uchar>(i-1);
            pC = tmpImg.ptr<uchar>(i);
            pD = tmpImg.ptr<uchar>(i+1);
            for(int j=1; j<width; j++)
            {
                if(pC[j] > 0)
                {
                    int ap=0;
                    int p2 = (pU[j] >0);
                    int p3 = (pU[j+1] >0);
                    if (p2==0 && p3==1)
                    {
                        ap++;
                    }
                    int p4 = (pC[j+1] >0);
                    if(p3==0 && p4==1)
                    {
                        ap++;
                    }
                    int p5 = (pD[j+1] >0);
                    if(p4==0 && p5==1)
                    {
                        ap++;
                    }
                    int p6 = (pD[j] >0);
                    if(p5==0 && p6==1)
                    {
                        ap++;
                    }
                    int p7 = (pD[j-1] >0);
                    if(p6==0 && p7==1)
                    {
                        ap++;
                    }
                    int p8 = (pC[j-1] >0);
                    if(p7==0 && p8==1)
                    {
                        ap++;
                    }
                    int p9 = (pU[j-1] >0);
                    if(p8==0 && p9==1)
                    {
                        ap++;
                    }
                    if(p9==0 && p2==1)
                    {
                        ap++;
                    }
                    if((p2+p3+p4+p5+p6+p7+p8+p9)>1 && (p2+p3+p4+p5+p6+p7+p8+p9)<7)
                    {
                        if(ap==1)
                        {
                            if((p2*p4*p6==0)&&(p4*p6*p8==0))
                            {                           
                                dst.ptr<uchar>(i)[j]=0;
                                isFinished =true;                            
                            }

                            //   if((p2*p4*p8==0)&&(p2*p6*p8==0))
                            //    {                           
                            //         dst.ptr<uchar>(i)[j]=0;
                            //         isFinished =TRUE;                            
                            //    }

                        }
                    }                    
                }

            } //扫描过程一 结束


            dst.copyTo(tmpImg); 
            //扫描过程二 开始
            for(i=1; i<height;  i++)  //一次 先行后列扫描 开始
            {
                pU = tmpImg.ptr<uchar>(i-1);
                pC = tmpImg.ptr<uchar>(i);
                pD = tmpImg.ptr<uchar>(i+1);
                for(int j=1; j<width; j++)
                {
                    if(pC[j] > 0)
                    {
                        int ap=0;
                        int p2 = (pU[j] >0);
                        int p3 = (pU[j+1] >0);
                        if (p2==0 && p3==1)
                        {
                            ap++;
                        }
                        int p4 = (pC[j+1] >0);
                        if(p3==0 && p4==1)
                        {
                            ap++;
                        }
                        int p5 = (pD[j+1] >0);
                        if(p4==0 && p5==1)
                        {
                            ap++;
                        }
                        int p6 = (pD[j] >0);
                        if(p5==0 && p6==1)
                        {
                            ap++;
                        }
                        int p7 = (pD[j-1] >0);
                        if(p6==0 && p7==1)
                        {
                            ap++;
                        }
                        int p8 = (pC[j-1] >0);
                        if(p7==0 && p8==1)
                        {
                            ap++;
                        }
                        int p9 = (pU[j-1] >0);
                        if(p8==0 && p9==1)
                        {
                            ap++;
                        }
                        if(p9==0 && p2==1)
                        {
                            ap++;
                        }
                        if((p2+p3+p4+p5+p6+p7+p8+p9)>1 && (p2+p3+p4+p5+p6+p7+p8+p9)<7)
                        {
                            if(ap==1)
                            {
                                //   if((p2*p4*p6==0)&&(p4*p6*p8==0))
                                //   {                           
                                //         dst.ptr<uchar>(i)[j]=0;
                                //         isFinished =TRUE;                            
                                //    }

                                if((p2*p4*p8==0)&&(p2*p6*p8==0))
                                {                           
                                    dst.ptr<uchar>(i)[j]=0;
                                    isFinished =true;                            
                                }

                            }
                        }                    
                    }

                }

            } //一次 先行后列扫描完成          
            //如果在扫描过程中没有删除点，则提前退出
            if(isFinished ==false)
            {
                break; 
            }
        }

    }
}

void eraseThron(Mat& img)
{
    int width=img.cols;
    int height=img.rows;
    for(int i=0;i<width;i++)
    {
        if(img.at<uchar>(0,i)==255&&img.at<uchar>(1,i)==0) 
        {
                img.at<uchar>(0,i)=0;
        }
        if(img.at<uchar>(height-1,i)==255&&img.at<uchar>(height-2,i)==0) 
        {
                img.at<uchar>(height-1,i)=0;
        }
    }
    for(int i=0;i<height;i++)
    {
        if(img.at<uchar>(i,0)==255&&img.at<uchar>(i,1)==0) {
            img.at<uchar>(i,0)=0;
        }
        if(img.at<uchar>(i,width-1)==255&&img.at<uchar>(i,width-2)==0){
            img.at<uchar>(i,width-1)=0;
        }
    }
}

FeatureExtract::FeatureExtract(void)
{
}

FeatureExtract::FeatureExtract( Mat& inputImage,vector<double>& feature )
{
    img = inputImage.clone();
    dx = Mat::zeros(img.rows, img.cols, CV_32F);
    dy = Mat::zeros(img.rows, img.cols, CV_32F);

    Sobel(img, dx, CV_32F, 1, 0, 3, 1, 0, BORDER_REPLICATE);
    Sobel(img, dy, CV_32F, 0, 1, 3, 1, 0, BORDER_REPLICATE);
    Mat gradient;
    sqrt(dx.mul(dx) + dy.mul(dy), gradient);
    double minVal,maxVal;
    minMaxLoc(gradient,&minVal,&maxVal);
    gradient.convertTo(gradient,CV_8UC1,255/maxVal);

    threshold(gradient,gradient,0,255,THRESH_BINARY|THRESH_OTSU);

    vector<double> k;
    //k.push_back(0.7);//top 20% gradient
    vector<double> kperc;
    //ComputeKPercentile(gradient, Mat(), k, kperc);

    Mat bw = gradient > 128;//kperc[0];

    //imshow("bw",bw);
    //waitKey(0);
    Mat element = getStructuringElement(MORPH_ELLIPSE, Size(31, 31));
    Mat mask;
    morphologyEx(bw, mask, MORPH_CLOSE, element);

#pragma region segmentation
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);    //生成区域边界
    int maxBound = 0;
    for(int i = 1; i < contours.size(); i++)
    {
        if(contourArea(contours[i]) > contourArea(contours[maxBound]))maxBound = i;
    }
    vector<Point> maxBoundRegion = contours[maxBound];
    int xmin = 9999, xmax = 0, ymin = 9999, ymax = 0;
    for(int j = 0; j < maxBoundRegion.size(); j++)
    {
        if(xmin > maxBoundRegion[j].x)xmin = maxBoundRegion[j].x;
        if(xmax < maxBoundRegion[j].x)xmax = maxBoundRegion[j].x;
        if(ymin > maxBoundRegion[j].y)ymin = maxBoundRegion[j].y;
        if(ymax < maxBoundRegion[j].y)ymax = maxBoundRegion[j].y;
    }
    Rect ROI = Rect(xmin, ymin, xmax - xmin + 1, ymax - ymin + 1);
    mask = Mat::zeros(ROI.height, ROI.width, CV_8UC1);
    drawContours(mask, contours, maxBound, Scalar(255), CV_FILLED, 8, noArray(), 2147483647, Point(-xmin, -ymin));
#pragma endregion segmentation
    img = img(ROI);
    dx = dx(ROI);
    dy = dy(ROI);
    imshow("image", img.mul(mask / 255));
    waitKey(1);

    Mat minMean = Mat::ones( img.rows / GRIDWIDTH, img.cols / GRIDWIDTH, CV_64F);
    Mat maxMean = Mat::zeros( img.rows / GRIDWIDTH, img.cols / GRIDWIDTH, CV_64F);
    Mat eqImage=Mat(img.rows,img.cols,CV_8U);
    Mat enhanced = Mat::zeros(img.rows,img.cols,CV_8U);
    Mat binary = Mat::zeros(img.rows,img.cols,CV_8U);
    for(int i = 0; i < img.cols / GRIDWIDTH; i++)
    {
        for(int j = 0; j < img.rows / GRIDWIDTH; j++)
        {
            Rect subRect = Rect(i * GRIDWIDTH, j * GRIDWIDTH, GRIDWIDTH, GRIDWIDTH);
            if(sum(mask(subRect))[0] / 255 < GRIDWIDTH * GRIDWIDTH*0.5) continue;
            double angle = getAngleOfSubImg(subRect);
            Mat kernel=getGaborKernel(Size(9,9),9,CV_PI/2-angle,CV_PI*2.5,1,0,CV_64F);
            Mat subImg=img(subRect);
            Mat eqSubImg;
            equalizeHist(~subImg,eqSubImg);
            eqSubImg.copyTo(eqImage(subRect));
            /*imshow("sub image",~eqSubImg);
            waitKey(1);
            imshow("kernel",~kernel);
            waitKey();*/
            
            filter2D(eqSubImg,enhanced(subRect),CV_8U,kernel);
            threshold(enhanced(subRect),binary(subRect),0,255,THRESH_BINARY|THRESH_OTSU);
            eraseThron(binary(subRect));
#ifdef _DEBUG
            Point2d p1 = Point2d(subRect.x + (GRIDWIDTH - 1) / 2 + (double)(GRIDWIDTH - 1) / 2 * cos(angle), subRect.y + (GRIDWIDTH - 1) / 2 - (double)(GRIDWIDTH - 1) / 2 * sin(angle));
            Point2d p2 = Point2d(subRect.x + (GRIDWIDTH - 1) / 2 - (double)(GRIDWIDTH - 1) / 2 * cos(angle), subRect.y + (GRIDWIDTH - 1) / 2 + (double)(GRIDWIDTH - 1) / 2 * sin(angle));
            line(img, p1, p2, Scalar(255), 1, CV_AA);
#endif
        }
    }
    imshow("equalize",eqImage);
    waitKey(1);
    imshow("orientation", img.mul(mask / 255));
    waitKey(1);
    Mat skeleton;
    thin(binary,skeleton,5);
    imshow("enhanced",binary);
    waitKey(1);
    imshow("skeleton",skeleton);
    waitKey(0);
}

double FeatureExtract::getAngleOfSubImg(Rect subRegion)
{
    double Vx = sum(dx(subRegion).mul(dy(subRegion)) * 2)[0];
    double Vy = sum(dy(subRegion).mul(dy(subRegion)) - dx(subRegion).mul(dx(subRegion)))[0];
    double theta = atan2(Vx, Vy) / 2;
    //if(Vy>0) theta+=M_PI/2;
    //theta=M_PI/2-theta;
    //cout<<theta<<endl;
    return theta;
}

FeatureExtract::~FeatureExtract(void)
{
}

void FeatureExtract::gaborFilter( Rect subRegion,double angle,Mat& outputImage )
{
    
    //imshow("kernel",kernel);
    //waitKey(0);
    
}


