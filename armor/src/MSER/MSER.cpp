#ifdef USE_NEW_CODE
#undef USE_NEW_CODE
#endif

#ifndef USE_NEW_CODE
#define USE_NEW_CODE //如果保留这一行,则使用新代码; 如果注释掉这一行,则使用旧代码
#endif

#ifdef DEBUG
#undef DEBUG
#endif

#ifndef DEBUG
// #define DEBUG //在程序中用 #ifdef DEBUG 与 #endif 将debug代码块框起来,实现debug输出 
#endif

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include "proportion_thresh.hpp"
#include "other/include/timer.hpp"

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
	
	const double bbox_armor_width = egde_r - egde_l;
	const double bbox_armor_height = egde_u - egde_d;

	// 判断是否为装甲板
	if(bbox_armor_height<100 && bbox_armor_width<100)
	{
		if(bbox_armor_height/bbox_armor_width<1.2 
		&& bbox_armor_height/bbox_armor_width>0.3)
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

}

int main()
{   
	sp::timer timer;
	timer.reset();

	auto mat = cv::imread("../image/test_image.jpg", cv::IMREAD_GRAYSCALE);
	cv::resize(mat, mat, {1280, 720});
	sp::proportion_thresh(mat, mat, 255, 0.014); //二值化图像

	auto mser = cv::MSER::create();
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Rect>               bboxes;
	std::vector<cv::Rect>               bboxes_light;
	std::vector<cv::Rect>               bboxes_armor;

	mser->detectRegions(mat, contours, bboxes);
	std::cout << "All: " << bboxes.size() << " bboxes" << '\n';

	//重新读入彩色图像
	auto mat_multicolor = cv::imread("../image/test_image.jpg");
	cv::resize(mat_multicolor, mat_multicolor, {1280, 720});

	std::vector<int> drawed_rects;
	drawed_rects.reserve(bboxes.size() / 4);
	bboxes_light.reserve(drawed_rects.size());

	double bbox_proportion_thresh_max = 5.0; //设定bbox的高宽比上阈值
	double bbox_proportion_thresh_min = 1.0; //设定bbox的高宽比下阈值
	
	//画矩形	
	int cnt = 0;
	if (!bboxes.empty())
	{
		++cnt;

		//筛选bboxes
		if(bboxes.front().width/bboxes.front().height > bbox_proportion_thresh_max);
		// else if(bboxes.front().height/bboxes.front().width > bbox_proportion_thresh_max);
		// else if(bboxes.front().width/bboxes.front().height < bbox_proportion_thresh_min);
		else if(bboxes.front().height/bboxes.front().width < bbox_proportion_thresh_min);
		else
		{
			cv::rectangle(mat_multicolor, bboxes.front(), {0, 0, 255}, 2);
			drawed_rects.push_back(0);
		}	
	}

	constexpr float thresh = 0.0001; //IOU的阈值

	for (int i = 1; i < bboxes.size(); ++i)
	{
		bool skip = false;
		for (auto&& index : drawed_rects)
			if (skip = (sp::iou(bboxes[i], bboxes[index]) > thresh))
				break;
		if (skip)
			continue;
		
		//筛选bboxes
		if(bboxes[i].width/bboxes[i].height > bbox_proportion_thresh_max);
		// else if(bboxes[i].height/bboxes[i].width > bbox_proportion_thresh_max);
		// else if(bboxes[i].width/bboxes[i].height < bbox_proportion_thresh_min);
		else if(bboxes[i].height/bboxes[i].width < bbox_proportion_thresh_min);
		else
		{
			// 画灯条矩形
			cv::rectangle(mat_multicolor, bboxes[i], {0, 0, 255}, 2);
			drawed_rects.push_back(i);
			++cnt;
			bboxes_light.push_back(bboxes[i]);
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

for (int m=0;m<bboxes_armor.size();m++)
{
	// 画装甲板矩形
	cv::rectangle(mat_multicolor, bboxes_armor[m], {0, 255, 0}, 2);
}
			

	std::string cnt_str = std::to_string(cnt);	
	std::cout << "Answer: "+cnt_str+" bboxes" << '\n';

	// std::cin.get();
	cv::imwrite("../image/ans.jpg", mat_multicolor);

	std::cout << "程序运行时间：" << timer.get() << std::endl;
}

#else //旧代码在下面

int main()
{

    return 0;
}

#endif
