//
//  Ransack.hpp
//  Assigment2
//
//  Created by MaxyQiu on 2019-03-15.
//  Copyright © 2019 MaxyQiu. All rights reserved.
//

#ifndef Ransack_hpp
#define Ransack_hpp

#include <stdio.h>
#include<opencv2/opencv.hpp>

#include<algorithm>
using namespace std;
using namespace cv;
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
class Ransack{
    
    
public:
    
    vector<Point2f> points1;
    vector<Point2f> points2;
    Mat hom,homInv;
    vector<Point2f> highest_inliers1;
    vector<Point2f> highest_inliers2;
    vector <Point2f> inliers_computed1;
    vector <Point2f> inliers_computed2;
    Mat stitched =imread("/Users/maxyqiu/Desktop/Computer_Vision/project_images/s.png",IMREAD_COLOR);
    Mat IMG;
    vector<KeyPoint> K1;
    vector<KeyPoint> K2;
    vector<DMatch>  matches;
   void ExtractKeypoints( vector <DMatch> match,vector <KeyPoint> K1,vector <KeyPoint> K2);
    
  vector<Point2f> Project(vector<Point2f> a,Mat H);
    int computInliner(Mat H,float threshold);
    void ransac_loop( int iteration, float inlierThreshold);
    void draw_result();
    Mat Stitch(Mat img1, Mat img2);
    Mat Stitch6pic(vector<Mat> list);
};
#endif /* Ransack_hpp */
