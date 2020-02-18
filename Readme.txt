All the project functions has been included in class Ransack and it is built on Assignment2,So I didnt change the name of the project file.
void ExtractKeypoints( vector <DMatch> match,vector <KeyPoint> K1,vector <KeyPoint> K2): after we get the matches and keypoints of two images,I use this funtion to transfer the keypoints 
                                                                                        to two point2f vector.   
vector<Point2f> Project(vector<Point2f> a,Mat H): Use the formular in the slides and Project a vector of points
int computInliner(Mat H,float threshold):use the homography matrix we have computed, and record the projected points with the difference under threshold.
void ransac_loop( int iteration, float inlierThreshold): choose four pairs of points in the matches randomly , compute the H, project the points in the first image and compute the inliers, repeat the process iteration times and 
                                                         Choose the 
                                         
void draw_result(): draw the matches after doing ransac
Mat Stitch(Mat img1, Mat img2): project  image2 corners to get the size of stitched image,project the points in image1 and check if the projected points in the second image. If in,then copy the corresponding points in image2 to the stitched image.
Mat Stitch6pic(vector<Mat> list):stitch the image in the Mat list. stitch them in a loop. Each loop is doing Mat Stitch function.



the project picture has been named with P1 P2 P3 P4 P5 P6 
My own pictures are D1 D2 D3