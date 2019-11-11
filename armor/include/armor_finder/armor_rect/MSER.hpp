#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include "proportion_thresh.hpp"
#include <algorithm>
// #include "distance.hpp"
#include "classifier.hpp"

#ifdef SHOW_DISTANCE
#include "PNP.hpp"
#endif



#ifdef USE_NEW_CODE //新代码在下面

namespace sp
{
	
float iou(const cv::Rect& lhs, const cv::Rect& rhs)
{
	const int lt_x = std::max(lhs.x, rhs.x);
	const int lt_y = std::max(lhs.y, rhs.y);
	const int rd_x = std::min(lhs.x + lhs.width, rhs.x + rhs.width);
	const int rd_y = std::min(lhs.y + lhs.height, rhs.y + rhs.height);
	
	const int inner_w = std::max(0, rd_x - lt_x + 1);
	const int inner_h = std::max(0, rd_y - lt_y + 1);
	const int inner_area = inner_h * inner_w;
	
	return static_cast<float>(inner_area) / (lhs.area() + rhs.area() - inner_area);
}

bool bboxes_armor_isok(const cv::Rect& rect_l, const cv::Rect& rect_r)
{
	const double egde_l = std::min(rect_l.x, rect_r.x);
	const double egde_r = std::max(rect_l.x+rect_l.width, rect_r.x+rect_r.width);
	// const double egde_d = std::min(rect_l.y-rect_l.height, rect_r.y-rect_r.height);
	// const double egde_u = std::max(rect_l.y, rect_r.y);
	const double egde_u = std::max(rect_l.y+rect_l.height, rect_r.y+rect_r.height);
	const double egde_d = std::min(rect_l.y, rect_r.y);
	const double bbox_light_width = std::max(rect_l.width, rect_r.width);
	const double bbox_light_height = std::max(rect_l.height, rect_r.height);
	
	const double bbox_armor_width = egde_r - egde_l;
	const double bbox_armor_height = egde_u - egde_d;

	// 判断是否为装甲板
	
	// 添加装甲板和灯条框的高度相比：<1.2 && >0.9

	if
	(bbox_armor_height/bbox_armor_width<0.5
	&& bbox_armor_height/bbox_armor_width>0.2
	&& bbox_armor_height/bbox_light_height>0.9
	&& bbox_armor_height/bbox_light_height<1.5
	&& (std::abs(rect_l.y-rect_r.y)<(bbox_light_height/6.0))
	// && rect_r.width/rect_l.width>0.7
	// && rect_r.width/rect_l.width<1.3
	)
	{
		return true;
	}
	// else if (bbox_armor_width/bbox_armor_height<1.2 
	// && bbox_armor_width/bbox_armor_height>0.3)
	// {
	// 	return true;
	// }
	else return false;
}

cv::Rect get_armor(const cv::Rect& rect_l, const cv::Rect& rect_r)
{
	const int egde_l = std::min(rect_l.x, rect_r.x);
	const int egde_r = std::max(rect_l.x+rect_l.width, rect_r.x+rect_r.width);
	// const int egde_d = std::min(rect_l.y-rect_l.height, rect_r.y-rect_r.height);
	// const int egde_u = std::max(rect_l.y, rect_r.y);
	const double egde_u = std::max(rect_l.y+rect_l.height, rect_r.y+rect_r.height);
	const double egde_d = std::min(rect_l.y, rect_r.y);
	
	const int bbox_armor_width = egde_r - egde_l;
	const int bbox_armor_height = egde_u - egde_d;

	cv::Rect armor(egde_l, egde_d, bbox_armor_width, bbox_armor_height);
	return armor;
}

cv::Mat& mser(cv::Mat& mat, cv::Mat& mat_real)
{	



	auto mser = cv::MSER::create(	1, // _delta 灰度值的变化量
									30, //_min_area 检测到的组块⾯积的范围
									14400, //_max_area 检测到的组块⾯积的范围
									0.00025, //_max_variation 最⼤的变化率
									0.7, // _min_diversity 稳定区域的最⼩变换量
									200, //  _max_evolution 对彩⾊图像的MSER检测
									1.01, // _area_threshold 
									0.003, // _min_margin 
									5 // _edge_blur_size 
									); 



	mser->detectRegions(mat, contours, bboxes); // 检测边缘

	#ifdef DEBUG
	std::cout << "All: " << bboxes.size() << " bboxes" << '\n';
	#endif

	std::vector<int> drawed_rects;
	drawed_rects.reserve(bboxes.size() / 4);
	bboxes_light.reserve(drawed_rects.size());

	// 筛选bbox并将bbox画在图像上

	int cnt = 0;
	if (!bboxes.empty())
	{
		++cnt;

		//筛选bboxes
		if(bboxes.front().width/bboxes.front().height > bbox_proportion_thresh_max)
		{
			#ifdef DEBUG
			std::cout << "bboxes out1" << std::endl;
			#endif
		}
		else if(bboxes.front().width/bboxes.front().height < bbox_proportion_thresh_min)
		{
			#ifdef DEBUG
			std::cout << "bboxes out2" << std::endl;
			#endif
		}
		else
		{
			// 画灯条矩形
			#ifdef SHOW_LIGHT

			#ifdef SHOW_MONO_COLOR
			cv::rectangle(mat, bboxes.front(), {255}, 2);
			#endif

			cv::rectangle(mat_real, bboxes.front(), {0,255,0}, 2);
			#endif

			drawed_rects.push_back(0);
		}	
	}

	for (int i = 1; i < bboxes.size(); ++i)
	{
		bool skip = false;
		for (auto&& index : drawed_rects)
			if (skip = (sp::iou(bboxes[i], bboxes[index]) > thresh_iou))
				break;
		if (skip)
			continue;
		
		//筛选bboxes
		if(bboxes[i].width/bboxes[i].height > bbox_proportion_thresh_max)
		{
			#ifdef DEBUG
			std::cout << "bboxes out3" << std::endl;
			#endif
		}
		else if(bboxes[i].width/bboxes[i].height < bbox_proportion_thresh_min)
		{
			#ifdef DEBUG
			std::cout << "bboxes out4" << std::endl;
			#endif
		}
		else
		{
			cv::Mat imagePart=mat_real(bboxes[i]); //抠图

			if(bboxes_light_is_ok(imagePart, 255, thresh_binar, thresh_value))
			{
				#ifdef SHOW_IMAGEPART_LIGHT
				cv::imshow("imagePart",imagePart);
				#endif

				// 画灯条矩形
				#ifdef SHOW_LIGHT

				#ifdef SHOW_MONO_COLOR				
				cv::rectangle(mat, bboxes[i], {255}, 2);
				#endif

				cv::rectangle(mat_real, bboxes[i], {0,255,0}, 2);
				#endif
				
				drawed_rects.push_back(i);
				++cnt;
				bboxes_light.push_back(bboxes[i]);
			}
		}		
	}

	for (int k = 0; k < bboxes_light.size(); k++)
	{
		bool skip_light = false;
		for (int l=0;l<bboxes_light.size();l++)
			if (skip_light = sp::bboxes_armor_isok(bboxes_light[k], bboxes_light[l]) && l!=k)// 筛选条件
			{
				bboxes_armor.push_back(sp::get_armor(bboxes_light[k], bboxes_light[l]));
			}
	}

	// bboxes_armor去重
	for (int m = 0; m < bboxes_armor.size(); m++)
	{
		bool skip = false;
		for (int n=m;n<bboxes_armor.size();n++)
			if (skip = (sp::iou(bboxes_armor[m], bboxes_armor[n]) > thresh_iou) && m!=n)
				break;
		if (skip)
			continue;
		bboxes_armor_selected.push_back(bboxes_armor[m]);

		#ifdef DEBUG
		std::cout<<"pushed"<<std::endl;
		#endif
	}

	for (int p=0;p<bboxes_armor_selected.size();p++)
	{
		// 画装甲板矩形
		#ifdef SHOW_ARMOR

		#ifdef SHOW_MONO_COLOR
		cv::rectangle(mat, bboxes_armor_selected[p], {255}, 2);
		#endif

		cv::rectangle(mat_real, bboxes_armor_selected[p], {0,0,255}, 2);
		#endif
	}

	for (int i = 0; i < bboxes_armor_selected.size(); i++)
	{
		int rect_armor_width = bboxes_armor_selected[i].width;
		int rect_armor_height = bboxes_armor_selected[i].width*0.6;
		int rect_armor_x = bboxes_armor_selected[i].x;
		int rect_armor_y = (bboxes_armor_selected[i].y+bboxes_armor_selected[i].height/2.0)-rect_armor_height/2.0;
		cv::Rect rect_armor(rect_armor_x, rect_armor_y, rect_armor_width, rect_armor_height);


		if(rect_armor.x>0 && rect_armor.y>0 && (rect_armor.x+rect_armor.width)<640 && (rect_armor.y+rect_armor.height)<480)
		{
		// 放入分类器进行比较并得出相应装甲板编号
		cv::Mat image_rect_armor=mat_real(rect_armor); //抠图

		#ifdef DEBUG
		std::cout << "截取装甲板图像成功" << std::endl;
		#endif

		// 分类器获取装甲板编号
		int num_armor = sp::classifier(image_rect_armor, "../Video/image/src/armor/image_positive_list.txt");

		if(num_armor!=0)
		{
			// 显示完整装甲板框
			#ifdef SHOW_ARMOR_WHOLE

			#ifdef SHOW_MONO_COLOR
			cv::rectangle(mat, rect_armor, {255}, 2);
			#endif

			#ifdef USE_RED
			cv::rectangle(mat_real, rect_armor, {0,0,255}, 2);
			#endif

			#ifdef USE_BLUE
			cv::rectangle(mat_real, rect_armor, {255,0,0}, 2);
			#endif

			#endif

			// 在原图上显示装甲板编号
			std::string num_armor_str = std::to_string(num_armor);
			sp::drawText(mat_real, rect_armor, "#"+num_armor_str);

			// 显示距离
			#ifdef SHOW_DISTANCE
			//sp::getBoxDistance(mat_real, bboxes_armor_selected);
			sp::get_distance(mat_real, rect_armor);
			#endif
		}
		else {}
		}

		
	}
	

	#ifdef DEBUG
	std::string cnt_str = std::to_string(cnt);	
	std::cout << "筛选得: "+cnt_str+" bboxes" << '\n';
	#endif

	return mat;
}

}













#else //旧代码在下面

#endif
