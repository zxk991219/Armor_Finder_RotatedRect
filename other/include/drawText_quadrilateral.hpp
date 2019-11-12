#pragma once

# include <chrono>
# include <opencv2/opencv.hpp>


#ifdef USE_NEW_CODE //新代码在下面

namespace sp
{
    void drawText_quadrilateral(cv::Mat& mat_real, const cv::Point2f point_pre, const std::string str)
{
    cv::Point2f point = cv::Point2f(point_pre.x, point_pre.y-5);

    cv::putText(mat_real, str,
    point,
    CV_FONT_HERSHEY_COMPLEX_SMALL, 1,
    
    #ifdef USE_RED
    cv::Scalar(0,0,255), 0.5,
    #endif

    #ifdef USE_BLUE
    cv::Scalar(255,0,0), 1,
    #endif

    LINE_MAX);
}
}

#else //旧代码在下面



#endif
