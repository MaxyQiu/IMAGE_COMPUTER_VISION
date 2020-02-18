//
//  Descriptor.hpp
//  Assigment2
//
//  Created by MaxyQiu on 2019-02-09.
//  Copyright © 2019 MaxyQiu. All rights reserved.
//

#ifndef Descriptor_hpp
#define Descriptor_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <map>
using namespace std;
using namespace cv;
class descriptor{
private:
    float width;
    float height;
    
    float kernel_data_r[3]={1,0,-1};
    float kernel_data_l[3]={-1,0,1};
    Mat kernel_x_r= Mat(1, 3, CV_32F, kernel_data_r);
    Mat kernel_x_l=Mat(1, 3, CV_32F, kernel_data_l);
    Mat kernel_y_r= Mat(3, 1, CV_32F, kernel_data_r);
    Mat kernel_y_l= Mat(3, 1, CV_32F, kernel_data_l);
    
public:
    descriptor();
    Mat img,
    derivate_x_r,
    derivate_x_l,
    derivate_y_r,
    derivate_y_l,
    derivate_X=Mat::zeros(height, width, CV_32F),
    derivate_Y=Mat::zeros(height, width, CV_32F);
    Mat orientation_histgram(Mat img,CV_OUT CV_IN_OUT vector<KeyPoint> &keypoints);
    Mat magnitude=Mat::zeros(height, width, CV_32F),angle=Mat::zeros(height, width, CV_32F);
    
    
    
    
    
    
};
#endif /* Descriptor_hpp */
