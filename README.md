# 一.Armor_Finder_RotatedRect  

## 1.find lightbox  

>cv::findContours(mat,contours, CV_RETR_LIST,CV_CHAIN_APPROX_NONE） [^将二值化后的Mat进行边缘检测]  
>minAreaRect(contours[i])[^取得轮廓的最小旋转矩形]
>screen lightboxes 筛选灯条  
>>cv::Point2f vertices[4]; rect.points(vertices);[^旋转矩形的四个顶点Mat内部]  
>>rotateRectToMat_isok(mat_real, rect);[^确保转正后的旋转矩形在Mat内部]  
>>rotateRectToMat(mat_real, rect);[^将旋转矩形所对应的区域内的图像转正]  
>>>length_width_rate_thresh[^长宽比阈值]  
>>>hsv_isok(mat_imagepart, thresh_binar, thresh_value);[^hsv检测]  
>>>>cv::cvtColor(in, in2, CV_RGB2HSV);RGB图片像HSV颜色空间转变  
>>>>cvGet2D(ipl_in2, rows/2, cols/2);遍历hsv中点像素值：筛选亮度和颜色

## 2.match lightbox_i_j  

>angle_isok(const cv::RotatedRect rect_i, const cv::RotatedRect rect_j)[^角度差匹配]
>center_height_isok(const cv::RotatedRect rect_i, const cv::RotatedRect rect_j)[^中心高度差匹配]
>center_distance_isok(const cv::RotatedRect rect_i, const cv::RotatedRect rect_j)[^中心距离和长度比匹配]
>