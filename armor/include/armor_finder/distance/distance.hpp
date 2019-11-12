# pragma once

# include <iostream>
# include <opencv2/opencv.hpp>
# include <string>
# define KNOWN_WIDTH 6.0236 //占位数据
# define FOCI 0.1693 //占位数据

#ifdef USE_NEW_CODE //新代码在下面

namespace sp
{
void getBoxDistance(cv::Mat& frame , std::vector<cv::Rect> bboxes_armor)
{
    std::vector<int> P_WIDTH;
    int i;
    cv::Rect rect;
    for(i=0;i<bboxes_armor.size();++i);
     {   
         rect=bboxes_armor[i];
         int p_width=rect.width;
         P_WIDTH.push_back(p_width);
         double distance=FOCI * KNOWN_WIDTH / p_width;

         cv::Point origin;
         origin.x = rect.tl().x+rect.width;
	     origin.y = rect.br().y+rect.height;
         double fontScale=2;
         double data= distance *30.48/ 12;//转化为厘米为单位
         std::string text= std::to_string( data);
         cv::putText( frame,//每一帧的图像
                      text,//文本内容
                      origin,//文本框左下角
                      cv::FONT_HERSHEY_SIMPLEX,//字体
                      fontScale,//字体尺寸（大小）
                      cv::Scalar(0,0,255),//字体颜色
                      4,//字体粗细
                      8,//线型
                      0);
     }
}
}


#else //旧代码在下面

int main()
{

    return 0;
}

#endif
