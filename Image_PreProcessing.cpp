#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables

Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold = 50;
int const highThreshold = 100;
int ratio = 3;
int kernel_size = 3;
char* window_name = "Edge Map";

/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
Mat CannyThreshold()
{
  /// Reduce noise with a kernel 3x3
  blur( src_gray, detected_edges, Size(3,3) );
  imshow("Detected_Edges_1", detected_edges);
  /// Canny detector
  Canny( detected_edges, detected_edges, lowThreshold, highThreshold, kernel_size );
  imshow("Detected_Edges_2", detected_edges);
  /// Using Canny's output as a mask, we display our result
  dst = Scalar::all(0);

  // detected_edges are copied to src.
  src.copyTo( dst, detected_edges);
  //imshow( window_name, detected_edges );
  return detected_edges;
 }


/** @function main */
int main( int argc, char** argv )
{

  /// Load an image
  src = imread( argv[1] );

  if( !src.data )
  {
	printf("Format of execution is executable 'filename of the image' \n"); 
	return -1; 
  }	

  /// Create a matrix of the same type and size as src (for dst)
  dst.create( src.size(), src.type() );

  /// Convert the image to grayscale
  cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Perform cannyThreshold operation

  Mat Matrix = CannyThreshold();

  imshow( window_name, Matrix );

  /// Wait until user exit program by pressing a key
  waitKey(0);

  return 0;
}
