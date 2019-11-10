#pragma once

#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <opencv2/opencv.hpp>


namespace sp //使用命名空间sp
{
	class template_classifier; //声明类：template_classifier
   	class template_classifier //定义类：template_classifier
	{
		public:
			void classifier(std::string template_filename, std::string compare_filename) //主要函数classifier,形参：模板文件名文件（.txt)，需要进行比较的文件名文件（.txt）
			{				
				//读入模板图像
				std::ifstream template_image_file(template_filename); // 读入模板文件名文件
				std::string template_file;
				std::getline(template_image_file, template_file); // 读入模板文件名
				cv::Mat template_image = cv::imread(template_file); //读入模板图像
				

				//二值化模板图像
				cv::Mat template_image_gray;
				cv::cvtColor(template_image, template_image_gray, CV_RGB2GRAY); //转化模板图像为灰度
				int template_threshold = get_threshold_(template_image_gray); //获得模板图像像素值二值化需要的阈值
				cv::Mat template_image_gray_threshold; 
				cv::threshold(template_image_gray, template_image_gray_threshold, template_threshold, 255, CV_THRESH_BINARY); //将模板图像二值化
				
				//显示模板图像
				// cv::imshow(template_file, template_image_gray_threshold);
				// cv::waitKey(0);
				// cv::destroyWindow(template_file);

				//读入图像尺寸
				int rows = template_image_gray_threshold.rows;
				int cols = template_image_gray_threshold.cols;
				if(template_image_gray_threshold.isContinuous())
				{
					cols *= rows;
					rows = 1;
				}
				
				
				//读入比较图像
				std::ifstream image_in(compare_filename); //读入比较图像文件名文件
				std::string read_filename;

				int gain = 0; //初始化gain
				std::vector<int> gain_list; //声明容器gain_list来放置每个图像的gain
				int count = 0;

				//获取gain
				while(getline(image_in, read_filename))
				{
					//读入比较图像并灰度
					cv::Mat read_image = cv::imread(read_filename); //读入比较图像
					cv::Mat read_image_gray;		
					cv::cvtColor(read_image, read_image_gray, CV_RGB2GRAY); //灰度比较图像
					

					int read_threshold = get_threshold_(read_image_gray); //获得比较图像像素值二值化需要的阈值
					cv::Mat read_image_gray_threshold;
					cv::threshold(read_image_gray, read_image_gray_threshold, read_threshold, 255, CV_THRESH_BINARY); //二值化比较图像
					
					// 将读入图像大小调节到与模板图像一样
					cv::resize(read_image_gray_threshold, read_image_gray_threshold, cv::Size(template_image_gray_threshold.cols, template_image_gray_threshold.rows), (0,0), (0,0), CV_INTER_AREA);
					
					
					//逐像素获取每个像素的gain并累积
					for(int i=0; i<rows; i++)
					{
						for(int j=0; j<cols; j++)
						{
							if(template_image_gray_threshold.at<uchar>(i,j)==255 && read_image_gray_threshold.at<uchar>(i,j)==255)
							{
								gain += 3;
							}
							else if(template_image_gray_threshold.at<uchar>(i,j) != read_image_gray_threshold.at<uchar>(i,j))
							{
								gain += 0;
							}
							else{}
						}
					}
					gain_list.push_back(gain); //将gain加入gain_list
					std::cout << read_filename << "的gain是" << gain << std::endl; //显示gain
					
					//显示压缩大小后的读入图像
					// cv::imshow(read_filename, read_image_gray_threshold);
					// cv::waitKey(0);
					// cv::destroyWindow(read_filename);
					
					gain = 0; //重置gain
				}
				auto min = std::min_element(gain_list.begin(), gain_list.end());
				std::cout << "这组图像的最小gain是" << *min << std::endl;
				auto max = std::max_element(gain_list.begin(), gain_list.end());
				std::cout << "这组图像的最大gain是" << *max << std::endl;
			};
		public:
			double      thre_proportion = 0.25; // 比例阈值，取直方图中thre_proportion位置亮的像素作为thre
			int         low_bound       = 1000;
		public:
			inline int get_threshold_(cv::Mat& mat) ////获得模板图像像素值二值化需要的阈值
			{
				uint32_t iter_rows = mat.rows;
				uint32_t iter_cols = mat.cols;
				auto sum_pixel = iter_rows * iter_cols;
				if(mat.isContinuous())
				{
					iter_cols = sum_pixel;
					iter_rows = 1;
				}
				int histogram[256];
				memset(histogram, 0, sizeof(histogram));
				for (uint32_t i = 0; i < iter_rows; ++i)
				{
					const uchar* lhs = mat.ptr<uchar>(i);
					for (uint32_t j = 0; j < iter_cols; ++j)
						++histogram[*lhs++];
				}
				auto left = thre_proportion * sum_pixel;
				int i = 255;
				while((left -= histogram[i--]) > 0);
				return std::max(i, 0);
			}
	};
}
