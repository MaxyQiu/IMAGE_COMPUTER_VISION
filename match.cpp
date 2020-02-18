//
//  match.cpp
//  Assigment2
//
//  Created by MaxyQiu on 2019-02-11.
//  Copyright © 2019 MaxyQiu. All rights reserved.
//

#include "match.hpp"
#include "Descriptor.hpp"
#include "feature.hpp"
match::match(){
    
    Mat img1 = imread(" /Users/maxyqiu/Desktop/Xcode\ C++/Assigment2/Assigment2/Yosemite1.jpg ", IMREAD_GRAYSCALE);
    // you need to change the path here
    Mat img2=imread(" /Users/maxyqiu/Desktop/Xcode\ C++/Assigment2/Assigment2/Yosemite2.jpg ", IMREAD_GRAYSCALE);
    
    

}

float match::computed_ssd(int k1,int k2,Mat descriptor1,Mat descriptor2){
    float ssd=0;
    for(int i=0;i<descriptor1.size().width;i++)
    {
        ssd+=(descriptor1.at<float>(k1,i)-descriptor2.at<float>(k2,i))*(descriptor1.at<float>(k1,i)-descriptor2.at<float>(k2,i));
        
    }
    return ssd;
};

vector<DMatch> match::goodpairs(float threshold,Mat descriptor1,Mat descriptor2,vector<KeyPoint> K1,vector<KeyPoint> K2){

    
    
    float ssd;
    vector<DMatch> betterones;
    
    for (int i=0;i<K1.size();i++)
        
        for (int j=0;j<K2.size();j++)
        {
            ssd=computed_ssd(i, j,descriptor1,descriptor2);
            if(ssd<threshold)
            {
                DMatch goodpairs(i,j,ssd);
                
                betterones.push_back(goodpairs);
            }
        }
    
    
    return betterones;
};
void match:: ratio_test(vector<KeyPoint> K1,vector<KeyPoint> K2,Mat descriptor1,Mat descriptor2){
    float ssd1=10000000;
    float ssd2=10000000;
    fstream file;
    file.open("/Users/maxyqiu/Desktop/Computer_Vision/ratio.txt");
    
    for (int i=0;i<K1.size();i++)
    {
        ssd1=1000000;
        ssd2=1000000;
        for (int j=0;j<K2.size();j++)
        {
            if(computed_ssd(i, j,descriptor1,descriptor2)<ssd1)
            {
                ssd1=computed_ssd(i, j,descriptor1,descriptor2);
                
            }
           else if(computed_ssd(i, j,descriptor1,descriptor2)>ssd1&&computed_ssd(i, j,descriptor1,descriptor2)<ssd2)
            {
                ssd2=computed_ssd(i, j,descriptor1,descriptor2);
            }
           
        }
       file<<ssd1/ssd2<<endl;
    }
    file.close();
};

void match::result_show(float threshold,Mat descriptor1,Mat descriptor2,vector<KeyPoint> K1,vector<KeyPoint> K2){
    vector<DMatch> matches=goodpairs(threshold,descriptor1,descriptor2,K1,K2);
    for(int i=0;i<matches.size();i++)
    {
        matches[i].distance*=10000;
    }
    drawMatches(img1, K1, img2, K2, matches, output);
    
    
    imshow("matches", output);
    
};
