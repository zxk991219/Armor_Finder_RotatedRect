// #ifdef USE_NEW_CODE
// #undef USE_NEW_CODE
// #endif

// #ifdef USE_CAMERA
// #undef USE_CAMERA
// #endif

// #ifdef USE_VIDEO
// #define USE_VIDEO
// #endif

// #ifdef DEBUG
// #undef DEBUG
// #endif

#ifndef DEBUG
#define DEBUG //在程序中用 #ifdef DEBUG 与 #endif 将debug代码块框起来,实现debug输出 
#endif

#ifndef USE_NEW_CODE
#define USE_NEW_CODE //如果保留这一行,则使用新代码; 如果注释掉这一行,则使用旧代码
#endif


# include <iostream>
# include <opencv2/opencv.hpp>
# define KNOWN_DISTANCE 10//占位数据
# define KNOWN_WIDTH 10//占位数据

#ifdef USE_NEW_CODE //新代码在下面

int main()
{

 cv::Mat image=cv::imread("/Armor_Finder/Video/image/src/test_image.jpg",cv::IMREAD_GRAYSCALE);
 cv::Mat gray;
 cv::GaussianBlur(image,gray, cv::Size(5, 5),0, 0);
 cv::Mat edged;        
 cv::Canny(gray,edged,35, 125,3) ;
 cv::findContours(edged, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
 c = max(cnts, key = cv2.contourArea);
 cv::Rect rect=cv::minAreaRect(c);
 double focalLength = (rect[1][0] * KNOWN_DISTANCE) / KNOWN_WIDTH ;


return focalLength




}





#else //旧代码在下面

int main()
{

    return 0;
}

#endif