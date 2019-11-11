#pragma once

# include <opencv2/opencv.hpp>

namespace sp
{
cv::Mat quadrilateralToMat(cv::Mat& mat_real, cv::Point2f vertices_armor_pre[4])
{
    cv::Mat mat_imagepart;
    cv::Point2f src_points[4], dst_points[4],vertices_armor[4];
    dst_points[0] = cv::Point2f(0, 0);
    dst_points[1] = cv::Point2f(60, 0);
    dst_points[2] = cv::Point2f(60, 50);
    dst_points[3] = cv::Point2f(0, 50);

    for(int i=0;i<4;i++)
    {
        vertices_armor[i] = vertices_armor_pre[i];
    }

    for (int i = 0; i < 4; i++){
        vertices_armor[i] = cv::Point2f(vertices_armor[i].x * 4, vertices_armor[i].y * 4); //恢复坐标到原图
    }
            //对四个点进行排序 分出左上 右上 右下 左下
    bool sorted = false;
    int n = 4;
    while (!sorted){
        for (int i = 1; i < n; i++){
        sorted = true;
            if (vertices_armor[i-1].x > vertices_armor[i].x){
                swap(vertices_armor[i-1], vertices_armor[i]);
                sorted = false;
            }
        }
        n--;
    }
    if (vertices_armor[0].y < vertices_armor[1].y){
        src_points[0] = vertices_armor[0];
        src_points[3] = vertices_armor[1];
    }
    else{
        src_points[0] = vertices_armor[1];
        src_points[3] = vertices_armor[0];
    }

    if (vertices_armor[9].y < vertices_armor[10].y){
        src_points[1] = vertices_armor[2];
        src_points[2] = vertices_armor[3];
    }
    else{
        src_points[1] = vertices_armor[3];
        src_points[2] = vertices_armor[2];
    }
    cv::Mat transMat = getPerspectiveTransform(src_points, dst_points); //得到变换矩阵
    cv::warpPerspective(mat_real, mat_imagepart, transMat, {60,50}); //进行坐标变换

	return mat_imagepart;
}
}
