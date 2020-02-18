//
//  Ransack.cpp
//  Assigment2
//
//  Created by MaxyQiu on 2019-03-15.
//  Copyright © 2019 MaxyQiu. All rights reserved.
//
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include "Ransack.hpp"
#include<opencv2/opencv.hpp>

#include<algorithm>
using namespace std;
using namespace cv;
const float nn_match_ratio = 0.8f;

void  Ransack::ExtractKeypoints( vector <DMatch> match,vector <KeyPoint> K1,vector <KeyPoint> K2){
    Mat H;
    vector<DMatch>::iterator it;
   
    for (it=match.begin(); it!=match.end(); it++) {
        float index1=(*it).queryIdx;
        float index2=(*it).trainIdx;
        points1.push_back(K1[index1].pt);
        points2.push_back(K2[index2].pt);
    }
 //   H=findHomography(points1, points2);
//    for(int i=0;i<9;i++)
//    {
//        cout<<H.at<float>(i/3,i%3)<<" ";
//

};
vector<Point2f> Ransack::Project(vector<Point2f> a,Mat H){
   vector<Point2f> b;
//    float temp[9];
//    for (int i=0; i<9; i++) {
//        temp[i]=H.at<float>(i/3,i%3);
//    }
    for (int i=0; i<a.size(); i++) {
        
   
    float X=a[i].x;
    float Y=a[i].y;
    cout<<"x="<<X<<"y="<<Y<<endl;
        Point2f temp;
   X=(float)((H.at<float>(0,0)*X+H.at<float>(0,1)*Y+H.at<float>(0,2)))/(float)(H.at<float>(2,0)*X+H.at<float>(2,1)*Y+H.at<float>(2,2));
    Y=(float)((H.at<float>(1,0)*X+H.at<float>(1,1)*Y+H.at<float>(1,2)))/(float)(H.at<float>(2,0)*X+H.at<float>(2,1)*Y+H.at<float>(2,2));
//        b.push_back(temp);
//    if(b.x>0&&b.y>0)
    {cout<<X<<","<<Y<<endl;}
    }
    return b;
    
    
    
};
int Ransack::computInliner(Mat H,float threshold)
{
    int inliers=0;
    vector <Point2f> temp;
    inliers_computed1.clear();
    inliers_computed2.clear();
    perspectiveTransform(points1, temp, H);
    for (int i=0; i<points1.size();i++)
    {
        float distance= (temp[i].x-points2[i].x)*(temp[i].x-points2[i].x)+(temp[i].y-points2[i].y)*(temp[i].y-points2[i].y);
        if(distance<threshold)
        {
            inliers++;
           // cout<<i<<"has been added"<<endl;
            inliers_computed1.push_back(points1[i]);
            inliers_computed2.push_back(points2[i]);
        }
    }
    
    
    
    
    
    return inliers;
    
    
};

void Ransack::ransac_loop( int iteration, float inlierThreshold){
    //
   // cout<<"points1.size="<<points1.size()<<endl;
    srand(time(NULL));
    int temp=0;
    int index1,index2,index3,index4;
    int inliers=0;
    Mat tempHomo;
   for (int i=0;i<iteration;i++)
    {
   // while (temp<50){
        
    
        vector<Point2f> temp1;
        vector<Point2f> temp2;
        //generate random number and new
       //
        index1=rand()%10+points1.size()-10;
         index2=rand()%10+points1.size()-10;
        
         index3=rand()%10+points1.size()-10;
         index4=rand()%10+points1.size()-10;
    
        temp1.push_back(points1[index1]);
        temp1.push_back(points1[index2]);
        temp1.push_back(points1[index3]);
        temp1.push_back(points1[index4]);
        temp2.push_back(points2[index1]);
        temp2.push_back(points2[index2]);
        temp2.push_back(points2[index3]);
        temp2.push_back(points2[index4]);
        tempHomo=findHomography(temp1, temp2);
//            for(int i=0;i<9;i++)
//            {
//                cout<<tempHomo.at<float>(i/3,i%3)<<" ";
//
//            }
      //  cout<<"next"<<endl;
        
        inliers= computInliner(tempHomo, inlierThreshold);
//        cout<<"inliers:"<<inliers<<endl;
//        cout<<"inlier_vector1"<<inliers_computed1<<endl;
//        cout<<"inlier_vector2"<<inliers_computed2<<endl;
        if (temp<inliers)
        {
            temp=inliers;
            hom=tempHomo;
            highest_inliers1=inliers_computed1;
            highest_inliers2=inliers_computed2;
          
            
        }
//        temp1.clear();
//        temp2.clear();
        
   }
    
    //hom as the best scoring H and temp as inliers
    
    //
    hom=findHomography(highest_inliers1, highest_inliers2);
        for(int i=0;i<9;i++)
        {
            cout<<hom.at<float>(i/3,i%3)<<" ";
    
        }
//

    homInv=hom.inv();
    
};
void Ransack::draw_result()
{

    for (int i=0; i<highest_inliers2.size(); i++) {
        KeyPoint k1(highest_inliers1[i].x,highest_inliers1[i].y,3);
        
        KeyPoint k2(highest_inliers2[i].x,highest_inliers2[i].y,3);
        K1.push_back(k1);
        K2.push_back(k2);
        float dis=(k1.pt.x-k2.pt.x)*(k1.pt.x-k2.pt.x)+(k1.pt.y-k2.pt.y)*(k1.pt.y-k2.pt.y);
        dis=sqrt(dis);
        DMatch match(i,i,dis);
        matches.push_back(match);
    }
    
   
    
    
    
};
Mat Ransack::Stitch(Mat img1, Mat img2){
    int height1=img1.size().height;
    int width1=img1.size().width;
    int height2=img2.size().height;
    int width2=img2.size().width;
    vector<Point2f> corners2,corners1;
    vector<Point2f> stitched_size;
    Point2f p21,p22,p23,p24,p11,p12,p13,p14;
    p21.x=0;
    p21.y=0;
    p22.x=0;
    p22.y=height2-1;
    p23.x=width2-1;
    p23.y=0;
    p24.x=width2-1;
    p24.y=height2-1;
    p11.x=0;
    p11.y=0;
    p12.x=0;
    p12.y=height1-1;
    p13.x=width1-1;
    p13.y=0;
    p14.x=width1-1;
    p14.y=height1-1;
    corners1.push_back(p11);
    corners1.push_back(p12);
    corners1.push_back(p13);
    corners1.push_back(p14);

    corners2.push_back(p21);
    corners2.push_back(p22);
    corners2.push_back(p23);
    corners2.push_back(p24);

    perspectiveTransform(corners2, stitched_size, homInv);
    int s_height,s_width;
    //height=maxX-minX width=maxY-minY
    float tempx[8],tempy[8];
    for (int i=0; i<4; i++) {
        tempx[i]=stitched_size[i].x;
tempy[i]=stitched_size[i].y;
        
    }
    for (int i=4; i<8; i++) {
        tempx[i]=corners1[i-4].x;
        tempy[i]=corners1[i-4].y;
        
    }
    
    
    s_width=ceil((*max_element(tempx, tempx+8))-(*min_element(tempx, tempx+8)));
      s_height=ceil((*max_element(tempy, tempy+8))-(*min_element(tempy, tempy+8)));
    
    
    
    //copy the image1
    
    cout<<s_width<<","<<s_height<<endl;
    
    Mat Stitched = Mat:: zeros(s_height, s_width, CV_8UC3);
    int intialy=ceil((*min_element(tempy, tempy+4)));
    int intialx=ceil((*min_element(tempx, tempx+4)));
    if(intialy>0)
    {
        intialy = 0;
    }
    if(intialx>0)
    {
        intialx = 0;
    }
    
    img1.copyTo(Stitched(Rect(-intialx, -intialy, width1, height1)));
    
    cout<<"copy good"<<endl;
    //project to img2
    vector<Point2f> stitched_points;
    vector<Point2f> judge_points;
    int count=0;
    for (int i=0; i<s_width; i++) {
        for (int j=0;j<s_height;j++){
            Point2f temp;
        temp.x=i+intialx;
        temp.y=j+intialy;
            stitched_points.push_back(temp);
        }
        
    }
    perspectiveTransform(stitched_points, judge_points,hom);
  //  filter the points out of bounder
    for(int i=0;i<judge_points.size();i++)
    {
        if(judge_points[i].x>0&&judge_points[i].x<width2&&judge_points[i].y>0&&judge_points[i].y<height2)
        {  Mat temp;
            getRectSubPix(img2, Size(1,1), judge_points[i], temp);
            temp.copyTo(Stitched(Rect((stitched_points[i].x-intialx),(stitched_points[i].y-intialy),1,1)));
//            Stitched.at<Vec3b>(stitched_points[i].y,stitched_points[i].x)=temp.at<Vec3b>(0,0);
    }
    
    }
      //  imshow("stitched", Stitched);
    return Stitched;
    
    
};
Mat Ransack::Stitch6pic(vector<Mat> list){
    Mat img1=list[0];
    Mat img2;
    for (int i=0; i<list.size()-1; i++) {
        img2=list[i+1];
       
        vector<KeyPoint> K1, K2;
        Mat desc1, desc2;
        
        Ptr<AKAZE> akaze = AKAZE::create();
        Ptr<BFMatcher> matches= BFMatcher::create();
        akaze->detectAndCompute(img1, noArray(), K1, desc1);
        akaze->detectAndCompute(img2, noArray(), K2, desc2);
        
        vector<vector<DMatch>> raw_matches;
        vector <DMatch> good_matches;
        matches->knnMatch(desc1, desc2, raw_matches,2);
        for(int i=0;i<raw_matches.size();i++){
            if (raw_matches[i][0].distance<nn_match_ratio*raw_matches[i][1].distance)
                
            {
                good_matches.push_back(raw_matches[i][0]);
            }
            
            
        }
        points1.clear();
        points2.clear();
       ExtractKeypoints(good_matches, K1, K2);
        cout<<"the number of keypoints:"<<points1.size()<<endl;
        ransac_loop(30,25);
        
        
        
        
        
        
        
        
        img1=Stitch(img1,img2);
        cout<<"done!"<<endl;
        
    }
    IMG=img1;
    
    imshow("multi_stitch", stitched);
    
    
    return img1;
    
};
