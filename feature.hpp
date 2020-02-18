//
//  feature.hpp
//  Assigment2
//
//  Created by MaxyQiu on 2019-01-28.
//  Copyright © 2019 MaxyQiu. All rights reserved.
//

#ifndef feature_hpp
#define feature_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <map>
using namespace std;
using namespace cv;
class Harris_corner{
private:
    float width;
    float height;
    float c;// set by user
    float kernel_data_xr[9]={0.125,0,-0.125, 0.25,0,-0.25,0.125,0,-0.125};
    float kernel_data_xl[9]={-0.125,0,0.125,-0.25,0,0.25,-0.125,0,0.125};
    float kernel_data_yr[9]={0.125,0.25,0.125, 0,0,0,-0.125,-0.25,-0.125};
    float kernel_data_yl[9]={-0.125,-0.25,-0.125, 0,0,0,0.125,0.25,0.125};
    Mat kernel_x_r= Mat(3, 3, CV_32F, kernel_data_xr);
    Mat kernel_x_l=Mat(3, 3, CV_32F, kernel_data_xl);
    Mat kernel_y_r= Mat(3, 3, CV_32F, kernel_data_yr);
    Mat kernel_y_l= Mat(3, 3, CV_32F, kernel_data_yl);
  
    
public:
    vector<KeyPoint> keypoints;
    multimap<int , int> location;
    Mat computed_c;
    Mat img,derivate_X=Mat::zeros(height, width, CV_32F),
            derivate_Y=Mat::zeros(height, width, CV_32F),
            derivate_XY=Mat::zeros(height, width, CV_32F);
    
    Harris_corner();    
    void Harris_Matrix_c_computed(Mat image);
    void Local_maximum();
    void Threshold_c(float threshold);
    vector<KeyPoint> draw_corner();
    
    
};



#endif /* feature_hpp */
