#pragma once

# include <iostream>
# include <opencv2/opencv.hpp>

# define BLOB_RED 1
# define BLOB_BLUE 0


namespace sp
{
    // 判断两个灯条的角度差
static bool angelJudge(const cv::RotatedRect &light_blob_i, const cv::RotatedRect &light_blob_j) {
    float angle_i = light_blob_i.size.width > light_blob_i.size.height ? light_blob_i.angle :
                    light_blob_i.angle - 90;//以最大的y值顶点作x轴，判断角度，以防两个颠倒的矩形配对
    float angle_j = light_blob_j.size.width > light_blob_j.size.height ? light_blob_j.angle :
                    light_blob_j.angle - 90;
    return abs(angle_i - angle_j) < 20;
}
// 判断两个灯条的高度差
static bool heightJudge(const cv::RotatedRect &light_blob_i, const cv::RotatedRect &light_blob_j) {
    cv::Point2f centers = light_blob_i.center - light_blob_j.center;
    return abs(centers.y) < 30;//
}
// 判断两个灯条的间距
static bool heightJudge(const cv::RotatedRect &light_blob_i, const cv::RotatedRect &light_blob_j) {
    double side_height;
    cv::Point2f centers = light_blob_i.center - light_blob_j.center;
    side_height = sqrt(centers.ddot(centers));
    return (side_height / light_blob_i.size.height < 10 && side_height / light_blob_i.size.height > 0.5);
}
// 判断两个灯条的长度比
static bool lengthRatioJudge(const cv::RotatedRect &light_blob_i, const cv::RotatedRect &light_blob_j) {
    return (light_blob_i.size.height / light_blob_j.size.height < 2.5
            && light_blob_i.size.height / light_blob_j.size.height > 0.4);//旋转矩形的长宽不定
}

// 判断装甲板方向
static bool boxAngleJudge(const cv::RotatedRect &light_blob_i, const cv::RotatedRect &light_blob_j) {
    float angle_i = light_blob_i.size.width > light_blob_i.size.height ? light_blob_i.angle :
                    light_blob_i.angle - 90;
    float angle_j = light_blob_j.size.width > light_blob_j.size.height ? light_blob_j.angle :
                    light_blob_j.angle - 90;
    float angle = (angle_i + angle_j) / 2.0;
    if (abs(angle_i - angle_j) > 90) {
        angle += 90.0;
    }
    return (-120.0 < angle && angle < -60.0) || (60.0 < angle && angle < 120.0);
}
}