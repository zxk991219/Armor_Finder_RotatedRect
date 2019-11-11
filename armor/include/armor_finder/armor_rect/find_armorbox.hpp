#pragma once

# include <iostream>
# include <opencv2/opencv.hpp>
# include "armorbox_isok.hpp"

# define BLOB_RED 1
# define BLOB_BLUE 0


namespace sp
{
std::vector<cv::RotatedRect> findArmorBox(std::vector<cv::RotatedRect> light_boxes)
{
	std::vector<cv::RotatedRect> armor_boxes; // 装甲板矩形容器

    for (int i = 0; i < light_boxes.size(); i++)    
    {
		bool skip_light = false;
        for (int j=0;j<light_boxes.size();j++)

			if (skip_light = sp::armorbox_isok(light_boxes[i], light_boxes[j]) && i!=j)// 筛选条件
			{
				armor_boxes.push_back(sp::get_armor(light_boxes[i], light_boxes[j]));
			}
    }
    






    return armor_boxes;
}
cv::RotatedRect get_armor(const cv::RotatedRect rect_i, const cv::RotatedRect rect_j)
{

}




// 判断装甲板方向
// static bool boxAngleJudge(const cv::RotatedRect &light_blob_i, const cv::RotatedRect &light_blob_j) {
//     float angle_i = light_blob_i.size.width > light_blob_i.size.height ? light_blob_i.angle :
//                     light_blob_i.angle - 90;
//     float angle_j = light_blob_j.size.width > light_blob_j.size.height ? light_blob_j.angle :
//                     light_blob_j.angle - 90;
//     float angle = (angle_i + angle_j) / 2.0;
//     if (abs(angle_i - angle_j) > 90) {
//         angle += 90.0;
//     }
//     return (-120.0 < angle && angle < -60.0) || (60.0 < angle && angle < 120.0);
// }
}
