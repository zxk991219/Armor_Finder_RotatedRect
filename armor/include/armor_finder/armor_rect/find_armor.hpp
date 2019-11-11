#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include "find_lightbox.hpp"
#include "find_armorbox.hpp"
#include "../image_processing/proportion_thresh.hpp"
#include "../image_processing/classifier.hpp"


#ifdef SHOW_DISTANCE
#include "../distance/PNP.hpp"
#endif

#define USE_NEW_CODE


#ifdef USE_NEW_CODE //新代码在下面

namespace sp
{
void findArmor(cv::Mat& mat, cv::Mat& mat_real) 
//mat是已经经过了RGB通道分离的图像，mat_real是摄像头探测到的原图
{
    // cv::medianBlur(mat, mat, 7); //中值滤波
	double thresh_binar = 0.02; //二值化取thresh_binar最亮部分
	sp::proportion_thresh(mat, mat, 255, thresh_binar); //二值化图像
    //可以用Canny、拉普拉斯等边缘检测算子处理二值图像

    //Canny处理图像
    // double cannyThr = 200;
    // double FACTOR = 2.5;
    // cv::Canny(), cannyThr, cannyThr*FACTOR); //Canny边缘检测
    
	std::vector<cv::RotatedRect> armor_boxes; // 装甲板矩形容器
    // armor_boxes = sp::findArmorBox(mat_real, sp::findLightBox(mat, mat_real));

    std::vector<cv::Rect> armor_boxes_up_right_rects;
    armor_boxes_up_right_rects = sp::findArmorBox(mat_real, sp::findLightBox(mat, mat_real));


}

}




#else //旧代码在下面

#endif
