#pragma once

#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include "proportion_thresh.hpp"
#include <chrono>


# ifdef USE_NEW_CODE

namespace sp //使用命名空间sp
{
int classifier(const cv::Mat& src, std::string template_filename_list) 
//src是从原图中截取mat，template_filename_list是储存模板文件文件名文件
{
	// 预处理截取图像
	#ifdef DEBUG
	std::cout << " " << std::endl;
	std::cout << "开始分类" << std::endl;
	#endif

	double thresh_binar = 0.2; //二值化取thresh_binar最亮部分

	#ifdef DEBUG
	std::cout << " " << std::endl;
	std::cout << "设定二值化阈值成功" << std::endl;
	#endif

	cv::Mat src_grey;
	cv::cvtColor(src, src_grey, CV_RGB2GRAY); //转化截取图像为灰度


	#ifdef DEBUG
	std::cout << " " << std::endl;
	std::cout << "灰度截取图像成功" << std::endl;
	#endif

	sp::proportion_thresh(src_grey, src_grey, 255, thresh_binar); //二值化截取图像

	#ifdef DEBUG
	std::cout << " " << std::endl;
	std::cout << "二值化截取图像成功" << std::endl;
	#endif

	#ifdef SHOW_ARMOR_IMAGE
	cv::imshow("src_grey",src_grey);
	#endif
	
	int rows = src_grey.rows;
	int cols = src_grey.cols;

	// if(src_grey.isContinuous())
	// {
	// 	cols *= rows;
	// 	rows = 1;
	// }

	rows = 50;
	cols = 60;

	cv::resize(src_grey, src_grey, cv::Size(cols, rows), (0,0), (0,0), CV_INTER_AREA);

	// 读入模板图像文件
	std::ifstream template_filename_in(template_filename_list); //读入模板图像文件名文件
	std::string template_filename;
	
	int gain = 0; //初始化gain
	std::vector<int> gain_list; //声明容器gain_list来放置每个图像的gain
	int count_armor = 1;

	while(getline(template_filename_in, template_filename))
	{
		// 模板图像预处理
		cv::Mat template_image = cv::imread(template_filename); //读入模板图像

		cv::Mat template_image_grey;
		cv::cvtColor(template_image, template_image_grey, CV_RGB2GRAY); //灰度模板图像
		sp::proportion_thresh(template_image_grey, template_image_grey, 255, thresh_binar); //二值化模板图像

		// 将模板图像的大小变成60*50
		cv::resize(template_image_grey, template_image_grey, cv::Size(cols, rows), (0,0), (0,0), CV_INTER_AREA);
		
		#ifdef DEBUG
		std::cout << "读入" << count_armor << "号装甲板模板" << std::endl;
		#endif

		// 逐像素获取每个像素的gain并累积
		for(int i=0; i<rows; i++)
		{
			for(int j=0; j<cols; j++)
			{
				if(template_image_grey.at<uchar>(i,j)==255 && src_grey.at<uchar>(i,j)==255)
				{
					gain += 3;
				}
				else if(template_image_grey.at<uchar>(i,j) != src_grey.at<uchar>(i,j))
				{
					gain += 0;
				}
				else{}
			}
		}
		gain_list.push_back(gain); //将gain加入gain_list

		#ifdef DEBUG
		std::cout << count_armor << "号装甲板的gain是" << gain << std::endl; //显示gain
		#endif

		gain = 0; //重置gain
		count_armor++;
	}

	auto min = std::min_element(gain_list.begin(), gain_list.end());
	auto max = std::max_element(gain_list.begin(), gain_list.end());

	#ifdef DEBUG
	std::cout << "这组图像的最小gain是" << *min << std::endl;
	std::cout << "这组图像的最大gain是" << *max << std::endl;
	#endif

	std::string filePath;
	filePath.clear();

	sp::timer timer_now;
	long long int count_classifier_int(timer_now.getTimeStamp());
	std::string count_classifier_str = std::to_string(count_classifier_int);

	if(*max<800)
	{
		#ifdef DEBUG
		std::cout << "舍弃" << std::endl;
		#endif

		#ifdef CLASSIFIER_OUTPUT
		filePath = "../Video/image/dst/negative/negative_"+count_classifier_str+".jpg";
		cv::imwrite(filePath, src_grey);

		#ifdef DEBUG
		std::cout << "输出negative图片成功" << std::endl;
		#endif

		#endif

		return 0;
	}
	else
	{
		int maxGainArmor = (max_element(gain_list.begin(),gain_list.end()) - gain_list.begin()) + 1;

		#ifdef DEBUG
		std::cout << "对应编号为" << maxGainArmor << "的装甲板" << std::endl;
		#endif

		#ifdef CLASSIFIER_OUTPUT
		filePath = "../Video/image/dst/positive/positive_"+count_classifier_str+".jpg";
		cv::imwrite(filePath, src_grey);

		#ifdef DEBUG
		std::cout << "输出positive图片成功" << std::endl;
		#endif

		#endif

		return maxGainArmor;
	}

}
}










# else

# endif
