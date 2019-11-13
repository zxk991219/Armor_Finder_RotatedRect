// #ifdef USE_NEW_CODE
// #undef USE_NEW_CODE
// #endif

// #ifndef USE_NEW_CODE
// #define USE_NEW_CODE //如果保留这一行,则使用新代码; 如果注释掉这一行,则使用旧代码
// #endif

// #ifdef DEBUG
// #undef DEBUG
// #endif

// #ifndef DEBUG
// #define DEBUG //在程序中用 #ifdef DEBUG 与 #endif 将debug代码块框起来,实现debug输出 
// #endif

#pragma once


# include <opencv2/opencv.hpp>
# include <iostream>
namespace sp
{

    void capture_set(cv::VideoCapture& capture, const double WIDTH,
     const double HEIGHT, const double FPS, const double BRIGHTNESS,
     const double CONTRAST, const double SATURATION, const double HUE, const double EXPOSURE)
    {
    capture.set(CV_CAP_PROP_FRAME_WIDTH, WIDTH);//宽度 
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, HEIGHT);//高度
    capture.set(CV_CAP_PROP_FPS, FPS);//帧数
    capture.set(CV_CAP_PROP_BRIGHTNESS, BRIGHTNESS);//亮度
    capture.set(CV_CAP_PROP_CONTRAST,CONTRAST);//对比度
    capture.set(CV_CAP_PROP_SATURATION, SATURATION);//饱和度 50
    capture.set(CV_CAP_PROP_HUE, HUE);//色调
    capture.set(CV_CAP_PROP_EXPOSURE, EXPOSURE);//曝光

    // #ifdef DEBUG
    std::cout << capture.get(CV_CAP_PROP_FRAME_WIDTH) << std::endl;//宽度 
    std::cout << capture.get(CV_CAP_PROP_FRAME_HEIGHT) << std::endl;//高度
    std::cout << capture.get(CV_CAP_PROP_FPS) << std::endl;//帧数
    std::cout << capture.get(CV_CAP_PROP_BRIGHTNESS) << std::endl;//亮度
    std::cout << capture.get(CV_CAP_PROP_CONTRAST) << std::endl;//对比度
    std::cout << capture.get(CV_CAP_PROP_SATURATION) << std::endl;//饱和度 50
    std::cout << capture.get(CV_CAP_PROP_HUE) << std::endl;//色调
    std::cout << capture.get(CV_CAP_PROP_EXPOSURE) << std::endl;//曝光
    // #endif

    }
}
