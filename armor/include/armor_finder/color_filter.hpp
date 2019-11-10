#pragma once

# include <opencv2/opencv.hpp>

namespace sp
{

void rgbColorFilter(cv::Mat& src_real, cv::Mat& src)
{
	std::vector<cv::Mat> channels;//定义Mat类型的向量
	cv::split(src_real, channels);//通道分离
	cv::Mat blue = channels.at(0);
	cv::Mat green = channels.at(1);
	cv::Mat red = channels.at(2);

	#ifdef USE_RED
	src = red;
	#endif

	#ifdef USE_BLUE
	src = blue;
	#endif

}
void hsvColorFilter(cv::Mat& inputImage, cv::Mat& outputImage)
{
	int i, j;

	int rows = inputImage.rows;
	int cols = inputImage.cols;

	cv::Mat hsv_mat;
	
	if(inputImage.isContinuous())
	{
		cols *= rows;
		rows = 1;
	}

	
	
    // cvCvtColor(image,hsv,CV_BGR2HSV);
    cv::cvtColor(inputImage, hsv_mat, CV_RGB2HSV);

	// IplImage* image = cvCreateImage(cvSize(rows,cols), IPL_DEPTH_8U, 3);
	// *image = IplImage(inputImage);
    IplImage* hsv = cvCreateImage(cvSize(rows,cols), IPL_DEPTH_8U, 3);  
	*hsv = IplImage(hsv_mat);

	int width = hsv->width;
	int height = hsv->height;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
		{
			CvScalar s_hsv = cvGet2D(hsv, i, j);//获取像素点为（j, i）点的HSV的值 
			
			CvScalar s;

            # ifdef USE_RED
			if (!(
                // (((s_hsv.val[0]>0)&&(s_hsv.val[0]<10)) || (s_hsv.val[0]>156)&&(s_hsv.val[0]<180))
                // && ((s_hsv.val[1]>43)&&(s_hsv.val[1]<255))
                // && ((s_hsv.val[2]>46)&&(s_hsv.val[2]<221))
                (s_hsv.val[2]>250)
                ))
			{
				s.val[0]=0;
				s.val[1]=0;
				s.val[2]=0;
				cvSet2D(hsv, i ,j, s);
			}
            # endif

            # ifdef USE_blue
			if (!(
                   ((s_hsv.val[0]>100)&&(s_hsv.val[0]<124))
                && ((s_hsv.val[1]>43)&&(s_hsv.val[1]<255))
                && ((s_hsv.val[2]>46)&&(s_hsv.val[2]<221))
                ))
			{
				s.val[0]=0;
				s.val[1]=0;
				s.val[2]=0;
				cvSet2D(hsv, i ,j, s);
			}
            # endif

		}
    outputImage=cv::cvarrToMat(hsv);

	cv::cvtColor(outputImage, outputImage, CV_RGB2GRAY);

    #ifdef DEBUG
	cvNamedWindow("filter");
	cvShowImage("filter", hsv);
    #endif

	// cvReleaseImage(&hsv);

}
}
