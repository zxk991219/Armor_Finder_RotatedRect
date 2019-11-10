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

    void capture_set(cv::VideoCapture& capture, const int WIDTH,
     const int HEIGHT, const int FPS, const int BRIGHTNESS,
     const int CONTRAST, const int SATURATION, const int HUE, const int EXPOSURE)
    {
    capture.set(3, WIDTH);//宽度 
    capture.set(4, HEIGHT);//高度
    capture.set(5, FPS);//帧数
    capture.set(10, BRIGHTNESS);//亮度 1
    capture.set(11,CONTRAST);//对比度 40
    capture.set(12, SATURATION);//饱和度 50
    capture.set(13, HUE);//色调 50
    capture.set(15, EXPOSURE);//曝光 50
    }
}
