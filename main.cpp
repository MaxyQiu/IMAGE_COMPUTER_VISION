//
//  main.cpp
//  Assigment2
//
//  Created by MaxyQiu on 2019-01-25.
//  Copyright © 2019 MaxyQiu. All rights reserved.
//
#include<opencv2/opencv.hpp>
#include "feature.hpp"
#include"Descriptor.hpp"
#include"match.hpp"
#include"Ransack.hpp"
#include<fstream>
using namespace std;
using namespace cv;
const float inlier_threshold = 2.5f; // Distance threshold to identify inliers
const float nn_match_ratio = 0.8f;

int main() {
    
    Mat img1 = imread("/Users/maxyqiu/Desktop/Computer_Vision/project_images/Rainier1.png", IMREAD_GRAYSCALE);
    // you need to change the path here
    Mat img2=imread("/Users/maxyqiu/Desktop/Computer_Vision/project_images/Rainier2.png", IMREAD_GRAYSCALE);
 
    Mat P5=imread("/Users/maxyqiu/Desktop/Computer_Vision/project_images/Rainier5.png",IMREAD_COLOR);
    Mat P6=imread("/Users/maxyqiu/Desktop/Computer_Vision/project_images/Rainier6.png",IMREAD_COLOR);
    Mat P1=imread("/Users/maxyqiu/Desktop/Computer_Vision/project_images/Rainier1.png",IMREAD_COLOR);
    
    Mat P2=imread("/Users/maxyqiu/Desktop/Computer_Vision/project_images/Rainier2.png",IMREAD_COLOR);
    
    Mat P3=imread("/Users/maxyqiu/Desktop/Computer_Vision/project_images/Rainier3.png",IMREAD_COLOR);
    Mat P4=imread("/Users/maxyqiu/Desktop/Computer_Vision/project_images/Rainier4.png",IMREAD_COLOR);
    Mat D1=imread ("/Users/maxyqiu/Desktop/Computer_Vision/project_images/1.jpg",IMREAD_COLOR);
    Mat D2=imread ("/Users/maxyqiu/Desktop/Computer_Vision/project_images/2.jpg",IMREAD_COLOR);
    Mat D3=imread ("/Users/maxyqiu/Desktop/Computer_Vision/project_images/3.jpg",IMREAD_COLOR);
    resize(D1, D1, Size(540,720),0,0,INTER_AREA);
     resize(D2, D2, Size(540,720),0,0,INTER_AREA);
     resize(D3, D3, Size(540,720),0,0,INTER_AREA);
    vector<KeyPoint> K1, K2;
    Mat desc1, desc2;

    Ptr<AKAZE> akaze = AKAZE::create();
    Ptr<BFMatcher> matches= BFMatcher::create();
    akaze->detectAndCompute(P1, noArray(), K1, desc1);
    akaze->detectAndCompute(P2, noArray(), K2, desc2);

    vector<vector<DMatch>> raw_matches;
    vector <DMatch> good_matches;
    matches->knnMatch(desc1, desc2, raw_matches,2);
    for(int i=0;i<raw_matches.size();i++){
        if (raw_matches[i][0].distance<nn_match_ratio*raw_matches[i][1].distance)

        {
            good_matches.push_back(raw_matches[i][0]);
        }


    }
//
//
//
//
//
//    // do the ratio
//
////      match Match;
////       restpairs=Match.goodpairs(0.0018, desc1, desc2, K1, K2);
//    Point2f test1,test2;
//    test1.x=200;
//    test1.y=200;
////
//
    Mat output;
    drawMatches(P1, K1, P2, K2, good_matches, output);
    imshow("matches", output);
////
////
////
////
////
   Ransack Step3;
Step3.ExtractKeypoints(good_matches, K1, K2);
//
//
//
   Step3.ransac_loop(100,25);
    Step3.draw_result();
    vector<KeyPoint> ransc_K1;
    vector<KeyPoint> ransc_K2;
    vector<DMatch>  ransc_match;
    Mat ransac_output;
    ransc_K1=Step3.K1;
    ransc_K2=Step3.K2;
    ransc_match=Step3.matches;
    drawMatches(P1, ransc_K1, P2, ransc_K2, ransc_match, ransac_output);
   imshow("ransac_matches", ransac_output);

    Mat stitch12=Step3.Stitch(P1, P2);
    imshow("stitched2", stitch12);
//    //
////
//
//test 6pic
//    vector<Mat> picturelist;
//
  vector<Mat> list1,list2,list3,list4,list5;
    list1.push_back(P1);
    list1.push_back(P2);
    list1.push_back(P3);
    list1.push_back(P4);
    list2.push_back(P5);
    list2.push_back(P6);


 //  Mat stitch1= Step3.Stitch6pic(list1);
    
    
list3.push_back(D1);
  list3.push_back(D2);
    list3.push_back(D3);
     Mat stitch2= Step3.Stitch6pic(list3);
    imshow("personalimage", stitch2) ;
    imwrite("/Users/maxyqiu/Desktop/Computer_Vision/project_images/church_lib.jpg", stitch2);//list3.push_back(stitch2);
  //  imshow("stitch1", stitch1);
  //  imshow("1", D1);
 //Mat stitch3= Step3.Stitch6pic(list3);
//
//    list4.push_back(P5);
//    list4.push_back(P6);
//
//    Mat stitch4= Step3.Stitch6pic(list4);
//    list5.push_back(stitch3);
//    list5.push_back(stitch4);
//
//    Mat stitch5=Step3.Stitch6pic(list5);
  //  list4.push_back(stitch1);
    //list4.push_back(stitch2);
  // list4.push_back(stitch3);
  //  Mat mult=Step3.Stitch6pic(list4);

    waitKey();



    
    
    return 0;
}
