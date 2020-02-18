//
//  feature.cpp
//  Assigment2
//
//  Created by MaxyQiu on 2019-01-28.
//  Copyright © 2019 MaxyQiu. All rights reserved.
//

#include "feature.hpp"
#include <opencv2/opencv.hpp>
#include <map>
using namespace cv;
using namespace std;

Harris_corner::Harris_corner(){
    

    
};
void Harris_corner::Harris_Matrix_c_computed(Mat image){
    img=image;
    width= img.size().width;
    height=img.size().height;
    computed_c=Mat::zeros(height-2, width-2, CV_32F);
    Mat derivate_x_r,derivate_x_l,derivate_y_r,derivate_y_l;
    filter2D(img, derivate_x_r, -1, kernel_x_r);
    filter2D(img, derivate_x_l, -1, kernel_x_l);
    filter2D(img, derivate_y_r, -1, kernel_y_r);
    filter2D(img, derivate_y_l, -1, kernel_y_l);
    derivate_X=derivate_x_l+derivate_x_r;
    derivate_Y=derivate_y_l+derivate_y_r;
    derivate_XY=derivate_X.mul(derivate_Y);
    
    imshow("derivate_X",derivate_X);
    imshow("derivate_Y",derivate_Y);
    imshow("derivate_XY",derivate_XY);
    derivate_X.convertTo(derivate_X, CV_32F);
    derivate_XY.convertTo(derivate_XY, CV_32F);
    derivate_Y.convertTo(derivate_Y, CV_32F);
    
    
    //matrix for each pixel
   
  
  
     GaussianBlur(derivate_X, derivate_X, Size(5,5),0,0);
     GaussianBlur(derivate_Y, derivate_Y, Size(5,5),0,0);
    GaussianBlur(derivate_XY, derivate_XY, Size(5,5),0,0);
    derivate_X.convertTo(derivate_X, CV_32F);
    //normalize
    //convertScaleAbs(<#InputArray src#>, <#OutputArray dst#>)
    derivate_Y.convertTo(derivate_Y, CV_32F);
    
    //for each pixel compute harris_matrix
    for (int i=1;i<height-2;i++)
        for (int j=1;j<width-2;j++)
        {
            float Ix=derivate_X.at<float>(i,j);
            float Iy=derivate_Y.at<float>(i,j);
            float IxIy=derivate_XY.at<float>(i,j);
            float a=Ix*Ix;
            float b=IxIy;
            float c=IxIy;
            float d=Iy*Iy;
         
           
           
           
            //compute the c for each
            
            if(a+d==0)
            computed_c.at<float>(i,j)=0;
            else
            computed_c.at<float>(i,j)=(float)(a*d-b*c)/(float)(a+d);

            computed_c.convertTo(computed_c, CV_32F);

            
        }
    
    
};
vector<KeyPoint> Harris_corner::draw_corner(){
    vector<KeyPoint> keypoints;
    int count=0;
    multimap<int , int >::iterator it;
    vector<KeyPoint>::iterator k;
//    KeyPoint mark;
    for (it=location.begin();it!=location.end();it++)
    {
        
        int j=(*it).first;
        int i=(*it).second;
        if((*it).second!=-1)
        {
        KeyPoint temp(i,j,3);
        temp.response=100;
        keypoints.push_back(temp);
        }
    }
    cout<<"keypoints in total is "<<keypoints.size()<<endl;

    drawKeypoints(img, keypoints, img);
   

    imshow("keypoints", img);
 
    return keypoints;
};
void Harris_corner::Threshold_c(float c)
{
     for(int i=0;i<computed_c.size().height;i++)
        for(int j=0;j<computed_c.size().width;j++)
    {
            
    if (computed_c.at<float>(i,j)>c)
     {
         location.insert(pair<int,int>(i,j));
         }
    }

   
    
    
    
};

void Harris_corner::Local_maximum()
{
    
     multimap<int , int >::iterator it;
    for (it=location.begin();it!=location.end();it++)
            {
             //   cout<<"access"<<endl;
                int i=(*it).first;
                int j=(*it).second;
                vector<float> compare(9);
                //            //create an array to store the value of the 3*3 neighbour
                    for(int m=0;m<9;m++)
                    {
                    compare[m]=computed_c.at<float>(i+(m/3-1),j+(m%3-1));
                    }
                for(int m=0;m<9;m++)
                {
                    if(compare[m]>computed_c.at<float>(i,j))
                    {
                       
                        
                        
                        (*it).second=-1;
                        
                        break;
                    }
                }
                
                }
    
};
