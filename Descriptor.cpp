//
//  Descriptor.cpp
//  Assigment2
//
//  Created by MaxyQiu on 2019-02-09.
//  Copyright © 2019 MaxyQiu. All rights reserved.
//

#include "Descriptor.hpp"
#define PI 3.14159265
descriptor::descriptor(){
    
    
};
Mat descriptor::orientation_histgram(Mat img, CV_OUT CV_IN_OUT vector<KeyPoint> &keypoints)
{
    
    float cols=img.size().width;
    float rows=img.size().height;
    vector<KeyPoint>::iterator k;
    filter2D(img, derivate_x_r, -1, kernel_x_r);
    filter2D(img, derivate_x_l, -1, kernel_x_l);
    filter2D(img, derivate_y_r, -1, kernel_y_r);
    filter2D(img, derivate_y_l, -1, kernel_y_l);
    derivate_X=derivate_x_l+derivate_x_r;
    derivate_Y=derivate_y_l+derivate_y_r;
    derivate_X.convertTo(derivate_X, CV_32F);
    derivate_Y.convertTo(derivate_Y, CV_32F);
//    delete the end
    KeyPoint temp=keypoints.back();
    int left=temp.pt.x-8;
    int right=left + 16;
    int up=temp.pt.y-8;
    int down=up+16;
    while (left<0||up<0||down>rows||right>cols) {
        keypoints.pop_back();
        KeyPoint temp=keypoints.back();
         left=temp.pt.x-8;
         right=left + 16;
         up=temp.pt.y-8;
         down=up+16;
    };
    //delete the middle
    for (k=keypoints.begin(); k!=keypoints.end(); k++) {
        temp=(*k);
        left=temp.pt.x-8;
        right=left + 16;
        up=temp.pt.y-8;
        down=up+16;
        if(left<0||up<0||down>rows||right>cols)
        {
            keypoints.erase(k);
        }
    }

    Mat Des= Mat::zeros(keypoints.size(), 128, CV_32F);
    //compute magnitude
//    for(int i=0;i<magnitude.size().height;i++)
//        for(int j=0;j<magnitude.size().width;j++)
//        {
//            magnitude.at<float>(i,j)=(derivate_X.at<float>(i,j))*(derivate_X.at<float>(i,j))+(derivate_Y.at<float>(i,j))*(derivate_Y.at<float>(i,j));
//            magnitude.at<float>(i,j)=sqrt(magnitude.at<float>(i,j));
//            cout<<magnitude.at<float>(i,j)<<endl;
//        }
//    for(int i=0;i<angle.size().height;i++)
//        for(int j=0;j<angle.size().width;j++)
//        {
//           if(derivate_X.at<float>(i,j)==0)
//           {
//               angle.at<float>(i,j)=90;
//           } angle.at<float>(i,j)=atan(derivate_Y.at<float>(i,j)/derivate_X.at<float>(i,j))*360/PI;
//        }
    cartToPolar(derivate_X, derivate_Y, magnitude, angle,1);
    
    
    //test angle
   
    
    
    
    
  //  imshow("mag", magnitude);
   // imshow("ang", angle);
    for(int i=0; i<keypoints.size();i++)
    {
        left=keypoints[i].pt.x-8;
        right=left+16;
        up=keypoints[i].pt.y-8;
        down=up+16;
        for (int cellrow=0;cellrow<4;cellrow++)
            
            for (int cellcol=0; cellcol<4;cellcol++ ) {
                int origin_col=cellcol*4+left;
                int origin_row=cellrow*4+up;
                for(int rows=0;rows<4;rows++)
                    for (int cols=0; cols<4; cols++) {
                        int location=angle.at<float>(origin_row+rows,origin_col+cols)/45;
                        
                        
                        Des.at<float>(i,location+cellrow*8*4+cellcol*8)+=magnitude.at<float>(origin_row+rows,origin_col+cols);
                    }
                
            }
        
        
    }
    
    
    
    normalize(Des, Des, 0,0.2,NORM_MINMAX, CV_32F);
    return Des;
};
