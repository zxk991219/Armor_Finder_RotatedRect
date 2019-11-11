#ifdef USE_NEW_CODE
#undef USE_NEW_CODE
#endif

#ifdef DEBUG

#undef DEBUG
#endif

#define USE_VIDEO
// #define USE_CAMERA

#define USE_RED
// #define USE_BLUE

// #define USE_HSV_FILTER
#define USE_RGB_FILTER

#define DEBUG
#define USE_NEW_CODE

// #define SHOW_MONO_COLOR //显示RGB通道分离结果
// #define SHOW_IMAGEPART_LIGHT //显示灯条矩形截图
// #define SHOW_ARMOR_IMAGE //显示装甲板矩形截图
// #define SHOW_LIGHT //显示灯条矩形
#define SHOW_ARMOR //显示灯条匹配的装甲板不规则四边形
#define SHOW_ARMOR_UP_RIGHT //显示灯条匹配的装甲板矩形
// #define SHOW_ARMOR_WHOLE //显示完整装甲板矩形
#define SHOW_DISTANCE //显示距离
// #define CLASSIFIER_OUTPUT //输出分类器结果到"Video/image/dst/negative/和positive"


# include <iostream>
# include <opencv2/opencv.hpp>
# include "other/include/timer.hpp"
# include "other/include/drawText.hpp"
# include "armor/include/show_images/show_images.hpp"
# include "armor/include/armor_finder/armor_rect/find_armor.hpp"
# include "armor/include/armor_finder/image_processing/color_filter.hpp"
// # include "armor/include/armor_finder/distance/PNP.hpp"
// # include "armor/include/armor_finder/image_processing/C-color.hpp"
// # include "armor/include/armor_finder/distance/distance.hpp"

# ifdef USE_NEW_CODE //新代码在下面

int main()
{
    sp::timer timer; //建立计时器

    cv::VideoCapture capture;

    #ifdef USE_CAMERA //使用摄像头
    capture.open("/dev/v4l/by-path/pci-0000:00:14.0-usb-0:1:1.0-video-index0",CV_CAP_V4L);
    sp::capture_set(capture, 640,//WIDTH
                              480,//HEIGHT
                              30,//FPS
                             -64,//BRIGHTNESS,
                              64,//CONTRAST, 
                              128,//SATURATION
                              40,//HUE, const int 
                              70//EXPOSURE
                    );
    //capture.open(1)
    cv::Mat src;
    cv::Mat src_real;
    capture >> src_real; 
    #endif


    #ifdef USE_VIDEO //使用录像
    // capture.open("../Video/2019-10-28-222635.webm");
    capture.open("../Video/2019-10-28-223802.webm");
    // capture.open("../Video/2019-10-28-223826.webm");
    // capture.open("../Video/2019-10-28-223848.webm");
    cv::Mat src;
    cv::Mat src_real;

    capture >> src_real; 

    #endif

    if(capture.isOpened())
    {
        for(;;) //读取视频循环
        {
            timer.reset(); // 开始计时

            capture >> src_real;

            #ifdef USE_VIDEO
            cv::resize(src_real,src_real,cv::Size(640,480),(0,0), (0,0), CV_INTER_AREA);
            #endif

            #ifdef USE_RGB_FILTER
            sp::rgbColorFilter(src_real, src);
            #endif

            #ifdef USE_HSV_FILTER
            sp::hsvColorFilter(src_real, src);
            #endif

            if(src.empty())
                break;

            sp::findArmor(src, src_real);
            
            #ifdef SHOW_MONO_COLOR
            cv::imshow("image", src);
            #endif

            cv::imshow("Armor_Target", src_real);

            std::cout << "程序运行时间：" << timer.get() << "ms" << std::endl; //结束计时

            if(cv::waitKey(10) >= 10)
                break;
        }
    }


    
    else
    {
        std::cout << "No capture" << std::endl;
        src = cv::Mat::zeros(480,640,CV_8UC1);
        cv::imshow("image", src);
        cv::waitKey(0);

    }

    return 0;
}


#else

#endif
