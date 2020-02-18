//
//  match.hpp
//  Assigment2
//
//  Created by MaxyQiu on 2019-02-11.
//  Copyright © 2019 MaxyQiu. All rights reserved.
//

#ifndef match_hpp
#define match_hpp

#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <map>
using namespace std;
using namespace cv;
class match{
private:

public:
    
    
 
    vector<DMatch> matches;
    Mat img1,img2,output;
    
    match();
    float computed_ssd(int k1,int k2,Mat descriptor1,Mat descriptor2);
    vector<DMatch> goodpairs(float threshold,Mat descriptor1,Mat descriptor2,vector<KeyPoint> K1,vector<KeyPoint> K2);
    void ratio_test(vector<KeyPoint> K1,vector<KeyPoint> K2,Mat descriptor1,Mat descriptor2);
    void result_show(float threshold,Mat descriptor1,Mat descriptor2,vector<KeyPoint> K1,vector<KeyPoint> K2);
    
    
    
    

};
#endif /* match_hpp */
