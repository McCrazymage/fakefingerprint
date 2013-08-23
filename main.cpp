#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>
#include <io.h>
#include <direct.h>
#include <string>
#include <iomanip>
#include <Windows.h>
#include "build/FeatureExtract.h"


using namespace std;
using namespace cv;

void getFiles( string path, vector<string>& files ) {
    //文件句柄  
    long   hFile   =   0;  
    //文件信息  
    struct _finddata_t fileinfo;  

    string p;

    if   ((hFile   =   _findfirst(p.assign(path).append("/*").c_str(),&fileinfo))   !=   -1)  {  

        do  {  
            //如果是目录,迭代之
            //如果不是,加入列表
            if   ((fileinfo.attrib   &   _A_SUBDIR)) {  
                if   (strcmp(fileinfo.name,".")   !=   0   &&   strcmp(fileinfo.name,"..")   !=   0)  
                    getFiles(   p.assign(path).append("/").append(fileinfo.name), files   );  
            }  else  {  
                if(strstr(fileinfo.name,"png")!=NULL||strstr(fileinfo.name,"bmp")!=NULL||strstr(fileinfo.name,"jpg")!=NULL||strstr(fileinfo.name,"tif")!=NULL)
                    files.push_back( p.assign(path).append("\\").append(fileinfo.name) );
            }  
        }   while   (_findnext(   hFile,   &fileinfo   )   ==   0);  

        _findclose(hFile);  
    }
}


int main(int, char** argv)
{

    
    vector<double> feature;
    Mat Prior;

    Mat testImage=imread("D:\\livdet\\Training\\Training Biometrika Live\\Live_4_1_Biometrika.png");
    if(testImage.channels()==3)
        cvtColor(testImage,testImage,CV_BGR2GRAY);
    FeatureExtract fe(testImage,feature);

    string folder="D:\\livdet\\Training\\Training Biometrika Live\\";
    ofstream outfeature(folder+"feature.m");
    vector<string> files;
    getFiles(folder,files);
    int fileSize=files.size();
    Mat features=Mat::zeros(1000,128,CV_64F);
    for(int i=0;i<fileSize;i++)
    {
        cout<<i+1<<"/"<<fileSize<<" "<<files[i]<<endl;
        Mat testImage=imread(files[i]);
        if(testImage.channels()==3)
            cvtColor(testImage,testImage,CV_BGR2GRAY);
        try
        {
            FeatureExtract fe(testImage,feature);
            features.row(i)=Mat(feature).t();
        }
        catch(Exception e)
        {
            features.row(i)=0;
        }
        
        //outfeature<<Mat(feature)<<endl;
    }
    //for(int i=1;i<=200;i++)
    //{
    //    for(int j=1;j<=5;j++)
    //    {
    //        char filename[50];
    //        //sprintf(filename,"D:\\livdet\\Testing\\Testing Biometrika Live\\%d_%d.png",i,j);
    //        sprintf(filename,"D:\\livdet\\Testing\\Testing Biometrika Spoof\\all\\%d.png",(i-1)*5+j);
    //        cout<<filename<<endl;
    //        
    //    }
    //    cout<<i<<endl;
    //}
    outfeature<<features<<endl;
    ofstream outf("Prior.txt");
    outf<<Prior<<endl;
    //vector<meanstd> meanStds;
    //fe.getMeanStdOfLines(testImage(Rect(100,100,16,16)),30/M_PI*180,meanStds);
    outf.close();
    outfeature.close();
    system("pause");
    return 0;
}