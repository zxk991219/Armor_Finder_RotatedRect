#pragma once

# include <iostream>
# include <opencv2/opencv.hpp>
# include "armorbox_isok.hpp"


namespace sp
{
void get_armor(cv::Mat& mat_real, const cv::RotatedRect rect_i, const cv::RotatedRect rect_j);
cv::Rect get_armor_up_right_rect(const cv::RotatedRect rect_i, const cv::RotatedRect rect_j);

// std::vector<cv::RotatedRect> findArmorBox(cv::Mat& mat_real, std::vector<cv::RotatedRect> light_boxes)
std::vector<cv::Rect> findArmorBox(cv::Mat& mat_real, std::vector<cv::RotatedRect> light_boxes)
{
	std::vector<cv::RotatedRect> armor_boxes; // 装甲板矩形容器
	std::vector<cv::Rect> armor_boxes_up_right_rects; // 装甲板矩形容器


    for (int i = 0; i < light_boxes.size(); i++)    
    {
		bool skip_light = false;
        for (int j=0;j<light_boxes.size();j++)

			if (skip_light = sp::armorbox_isok(light_boxes[i], light_boxes[j]) && i!=j)// 筛选条件
			{
				// armor_boxes.push_back(sp::get_armor(mat_real, light_boxes[i], light_boxes[j]));
                sp::get_armor(mat_real, light_boxes[i], light_boxes[j]);
                armor_boxes_up_right_rects.push_back(sp::get_armor_up_right_rect(light_boxes[i], light_boxes[j]));
			}
        # ifdef SHOW_ARMOR_UP_RIGHT
        for(int i = 0; i<armor_boxes_up_right_rects.size(); i++)
        {
			cv::rectangle(mat_real, armor_boxes_up_right_rects[i], {0,255,0}, 2);
        }
        # endif

    }
    
    return armor_boxes_up_right_rects;
    // return armor_boxes;
}
//画出装甲板
void get_armor(cv::Mat& mat_real, const cv::RotatedRect rect_i, const cv::RotatedRect rect_j)
{

    

    cv::RotatedRect rect_l = rect_i.center.x < rect_j.center.x ? rect_i : rect_j;
    cv::RotatedRect rect_r = rect_i.center.x > rect_j.center.x ? rect_i : rect_j;

    cv::Point2f vertices_l[4];
    rect_l.points(vertices_l);


    cv::Point2f vertices_r[4];
    rect_r.points(vertices_r);

    if(vertices_l[0].y==vertices_l[1].y)
    {
        cv::Point temp = vertices_l[0];
        vertices_l[0] = vertices_l[1];
        vertices_l[1] = vertices_l[2];
        vertices_l[2] = vertices_l[3];
        vertices_l[3] = temp;
    }

    if(vertices_r[0].y==vertices_r[1].y)
    {
        cv::Point temp = vertices_r[0];
        vertices_r[0] = vertices_r[1];
        vertices_r[1] = vertices_r[2];
        vertices_r[2] = vertices_r[3];
        vertices_r[3] = temp;
    }

    # ifdef DEBUG
    std::cout << "旋转坐标成功" << std::endl;
    # endif

    #ifdef DEBUG
    std::cout << "vertices_l[0] x:" <<vertices_l[0].x << "y:" << vertices_l[0].y <<std::endl;
    std::cout << "vertices_l[1] x:" <<vertices_l[1].x << "y:" << vertices_l[1].y <<std::endl;
    std::cout << "vertices_l[2] x:" <<vertices_l[2].x << "y:" << vertices_l[2].y <<std::endl;
    std::cout << "vertices_l[3] x:" <<vertices_l[3].x << "y:" << vertices_l[3].y <<std::endl;
    std::cout << std::endl;
    #endif

    #ifdef DEBUG
    std::cout << "vertices_r[0] x:" <<vertices_r[0].x << "y:" << vertices_r[0].y <<std::endl;
    std::cout << "vertices_r[1] x:" <<vertices_r[1].x << "y:" << vertices_r[1].y <<std::endl;
    std::cout << "vertices_r[2] x:" <<vertices_r[2].x << "y:" << vertices_r[2].y <<std::endl;
    std::cout << "vertices_r[3] x:" <<vertices_r[3].x << "y:" << vertices_r[3].y <<std::endl;
    std::cout << std::endl;
    #endif

    cv::Point2f vertices_dual_light[4];

    vertices_dual_light[0] = //bottom_left 
    rect_l.size.width < rect_l.size.height ? vertices_l[0] : vertices_l[1];

    #ifdef DEBUG
    std::cout << "vertices_dual_light[0] first x:" <<vertices_dual_light[0].x << "y:" << vertices_dual_light[0].y <<std::endl;
    #endif

    vertices_dual_light[1] = //top_left
    rect_l.size.width < rect_l.size.height ? vertices_l[1] : vertices_l[2];

    #ifdef DEBUG
    std::cout << "vertices_dual_light[1] first x:" <<vertices_dual_light[1].x << "y:" << vertices_dual_light[1].y <<std::endl;
    #endif

    vertices_dual_light[2] = //top_right
    rect_r.size.width < rect_r.size.height ? vertices_r[2] : vertices_r[3];

    vertices_dual_light[3] = // bottom_right
    rect_r.size.width < rect_r.size.height ? vertices_r[3] : vertices_r[0];

    #ifdef DEBUG
    std::cout << std::endl;
    std::cout << "vertices_dual_light[0] x:" <<vertices_dual_light[0].x << "y:" << vertices_dual_light[0].y <<std::endl;
    std::cout << "vertices_dual_light[1] x:" <<vertices_dual_light[1].x << "y:" << vertices_dual_light[1].y <<std::endl;
    std::cout << "vertices_dual_light[2] x:" <<vertices_dual_light[2].x << "y:" << vertices_dual_light[2].y <<std::endl;
    std::cout << "vertices_dual_light[3] x:" <<vertices_dual_light[3].x << "y:" << vertices_dual_light[3].y <<std::endl;
    std::cout << std::endl;
    #endif







    // for()


    // = (vertices_i[0].x < vertices_j[0].x ? vertices_i[0] : vertices_j[0]);


    // = (vertices_i[1].x < vertices_j[1].x ? vertices_i[1] : vertices_j[1]);

    // = (vertices_i[2].x > vertices_j[2].x ? vertices_i[2] : vertices_j[2]);

    // = (vertices_i[3].x > vertices_j[3].x ? vertices_i[3] : vertices_j[3]);



    # ifdef SHOW_ARMOR
    for (int i = 0; i < 4; i++)
    {
        cv::line(mat_real, vertices_dual_light[i], vertices_dual_light[(i + 1) % 4], cv::Scalar(0, 255, 0), 2, 8, 0);
    }
    # endif





    



}

cv::Rect get_armor_up_right_rect(const cv::RotatedRect rect_i, const cv::RotatedRect rect_j)
{
    cv::Rect up_right_rect_i = rect_i.boundingRect();
    cv::Rect up_right_rect_j = rect_j.boundingRect();

	const int egde_i = std::min(up_right_rect_i.x, up_right_rect_j.x);
	const int egde_j = std::max(up_right_rect_i.x+up_right_rect_i.width, up_right_rect_j.x+up_right_rect_j.width);
	// const int egde_d = std::min(up_right_rect_i.y-up_right_rect_i.height, up_right_rect_j.y-up_right_rect_j.height);
	// const int egde_u = std::max(up_right_rect_i.y, up_right_rect_j.y);
	const double egde_u = std::max(up_right_rect_i.y+up_right_rect_i.height, up_right_rect_j.y+up_right_rect_j.height);
	const double egde_d = std::min(up_right_rect_i.y, up_right_rect_j.y);
	
	const int bbox_armor_width = egde_j - egde_i;
	const int bbox_armor_height = egde_u - egde_d;

	cv::Rect armor_up_right_rect(egde_i, egde_d, bbox_armor_width, bbox_armor_height);
	return armor_up_right_rect;
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
