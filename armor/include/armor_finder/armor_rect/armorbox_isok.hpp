#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>


#ifdef SHOW_DISTANCE
#include "../distance/PNP.hpp"
#endif

#define USE_NEW_CODE


#ifdef USE_NEW_CODE //新代码在下面

namespace sp
{
bool armorbox_isok(const cv::RotatedRect rect_i, const cv::RotatedRect rect_j)
{
	if(sp::angle_isok(const cv::RotatedRect rect_i, const cv::RotatedRect rect_j)
	&& sp::center_height_isok(const cv::RotatedRect rect_i, const cv::RotatedRect rect_j)
	&& sp::center_distance_isok(const cv::RotatedRect rect_i, const cv::RotatedRect rect_j)
	&& sp::length_rate_isok(const cv::RotatedRect rect_i, const cv::RotatedRect rect_j))
	{
		return true;
	}
	else return false;
}

bool angle_isok(const cv::RotatedRect rect_i, const cv::RotatedRect rect_j)
// 判断两个灯条的角度差是否合适
{
	float angle_i = rect_i.size.width > rect_i.size.height ? rect_i.angle :
                    rect_i.angle - 90;//以最大的y值顶点作x轴，判断角度，以防两个颠倒的矩形配对
    float angle_j = rect_j.size.width > rect_j.size.height ? rect_j.angle :
                    rect_j.angle - 90;
	if(abs(angle_i - angle_j) < 20)
	{
		return true;
	}
	else return false;
}
bool center_height_isok(const cv::RotatedRect rect_i, const cv::RotatedRect rect_j)
// 判断两个灯条中心的高度差是否合适
{
    cv::Point2f centers = rect_i.center - rect_j.center;
	if(abs(centers.y) < 30)
	{
		return true;
	}
	else return false;
}
bool center_distance_isok(const cv::RotatedRect rect_i, const cv::RotatedRect rect_j)
// 判断两个灯条中心的距离是否合适
{
	double center_distance;
    cv::Point2f centers = rect_i.center - rect_j.center;
    center_distance = sqrt(centers.ddot(centers));
	if(center_distance / rect_i.size.height < 10 
	&& center_distance / rect_i.size.height > 0.5)
	{
		return true;
	}
	else return false;
}
bool length_rate_isok(const cv::RotatedRect rect_i, const cv::RotatedRect rect_j)
// 判断两个灯条的长宽比是否合适
{
	double length_i = rect_i.size.height > rect_i.size.width ?
    rect_i.size.height : rect_i.size.width;

	double length_j = rect_j.size.height > rect_j.size.width ?
    rect_j.size.height : rect_j.size.width;



	double length_rate = length_i / length_j;

	if(length_rate < 2.5 && length_rate > 0.4)
	{
		return true;
	}
	else return false;
}
}




#else //旧代码在下面

#endif
