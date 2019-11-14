#pragma once

# include <opencv2/opencv.hpp>

namespace sp
{
cv::Mat rotateRectToMat(cv::Mat& mat_real, cv::RotatedRect rect)
{
	cv::Point2f center = rect.center;//外接矩形中心点坐标
	cv::Mat rot_mat = getRotationMatrix2D(center, rect.angle, 1.0);//求旋转矩阵
	cv::Mat rot_image; //原图旋转后Mat
	cv::Size dst_sz(mat_real.size()); //初始化原图旋转后rot_image
	cv::warpAffine(mat_real, rot_image, rot_mat, dst_sz);//原图像旋转
	cv::Mat mat_imagepart = rot_image(cv::Rect(center.x - (rect.size.width / 2), center.y - (rect.size.height/2), rect.size.width, rect.size.height));//提取ROI
	
	#ifdef SHOW_IMAGEPART_LIGHT
	cv::imshow("SHOW_IMAGEPART_LIGHT", mat_imagepart);
	#endif
	
	return mat_imagepart;
}

bool rotateRectToMat_isok(cv::Mat& mat_real, cv::RotatedRect rect)
{
	cv::Point2f center = rect.center;//外接矩形中心点坐标
	cv::Rect rect_imagepart = cv::Rect(center.x - (rect.size.width / 2), center.y - (rect.size.height/2), rect.size.width, rect.size.height);
	if(
		(0<rect_imagepart.tl().y && rect_imagepart.tl().y<mat_real.rows //左上
		&&0<rect_imagepart.tl().x && rect_imagepart.tl().x<mat_real.cols 
		&&0<rect_imagepart.tl().y+rect_imagepart.height 
		&& rect_imagepart.tl().y+rect_imagepart.height<mat_real.rows //左下

		&&0<rect_imagepart.br().y && rect_imagepart.br().y<mat_real.rows //右下
		&&0<rect_imagepart.br().x && rect_imagepart.br().x<mat_real.cols
		&&0<rect_imagepart.br().y-rect_imagepart.height
		&& rect_imagepart.br().y-rect_imagepart.height<mat_real.rows //右上
		)
    )return true;
	else return false;
}
}
