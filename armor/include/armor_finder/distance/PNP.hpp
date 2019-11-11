#pragma once

# include <iostream>
# include <opencv2/opencv.hpp>
# include <opencv2/calib3d.hpp>
//# include "../../../other/include/drawText.hpp"


# define HALF_WIDTH 7.10
# define HALF_HEIGHT 6.25
# define PI 3.14

#ifdef USE_NEW_CODE //新代码在下面

namespace sp
{

    void get_distance(cv::Mat& frame, cv::Point2f& pts[4])
{   
    double m[3][3] = {{1056.641597953005, 0, 958.1078670170519}, { 0, 1055.821668018513, 558.7308899751256}, {0, 0, 1}};
    cv::Mat cam= cv::Mat(3, 3, CV_64F, m);//相机内参
    double n[5]={-0.4101674487087525,0.2060326419033235, 0.0007446583829303401, -0.0009071701383907473, -0.05685326030318479};
    cv::Mat dis=cv::Mat(1,5, CV_64F, n);//畸变参数
    // cv::FileStorage fs("../out_camera_data.xml", cv::FileStorage::READ);
    // fs["camera_matrix"] >> cam;
    // fs["distortion_coefficients"] >> dis;//传入相机的内参和外参


    std::vector<cv::Point2f> pnts=std::vector<cv::Point2f>{
        cv::Point2f(pts[1]),
        cv::Point2f(pts[2]),
        cv::Point2f(pts[3]),
        cv::Point2f(pts[0])
    };//设置像素坐标
    std::vector<cv::Point3f> obj=std::vector<cv::Point3f>{
            cv::Point3f(-HALF_WIDTH, -HALF_HEIGHT, 0),	//tl
            cv::Point3f(HALF_WIDTH, -HALF_HEIGHT, 0),	//tr
            cv::Point3f(HALF_WIDTH, HALF_HEIGHT, 0),	//br
            cv::Point3f(-HALF_WIDTH, HALF_HEIGHT, 0)	//bl
    };//设置世界坐标系中的坐标
    cv::Mat rVec= cv::Mat::zeros(3, 1, CV_64FC1);//init rvec
    cv::Mat tVec= cv::Mat::zeros(3, 1, CV_64FC1);//init tvec
    //初始化    
    cv::solvePnP(obj,pnts,cam,dis,rVec,tVec,false,cv::SOLVEPNP_ITERATIVE);
     //利用solvepnp解算出平移向量和旋转向量

    // double rm[3][3];
    // cv::Mat rotM=cv::Mat::zeros(3,3,CV_64FC1);//共享数据
     cv::Mat rotM= cv::Mat::zeros(3, 3, CV_64FC1);
     cv::Rodrigues(rVec, rotM);  //将旋转向量变换成旋转矩阵


    //根据旋转矩阵求出坐标旋转角
    double theta_x = atan2(rotM.at<double>(2, 1), rotM.at<double>(2, 2));
    double theta_y = atan2(-rotM.at<double>(2, 0),
    sqrt(rotM.at<double>(2, 1)*rotM.at<double>(2, 1) + rotM.at<double>(2, 2)*rotM.at<double>(2, 2)));
    double theta_z = atan2(rotM.at<double>(1, 0), rotM.at<double>(0, 0));
 
    //将弧度转化为角度
    theta_x = theta_x * (180 / PI);
    theta_y = theta_y * (180 / PI);
    theta_z = theta_z * (180 / PI);

    std::cout<<"Roll:"<<theta_z<<"Yaw:"<<theta_y<<"Pitch:"<<theta_x<<std::endl;

    // std::vector<uchar>  buff;//将mat型转换为string
    // cv::imencode(".bmp", tVec, buff);
    // std::string text(reinterpret_cast<char*>(&buff[0]), buff.size());
    
    double data= tVec.at<double>(2,0);//提出z轴坐标
    std::string text= std::to_string( data);

    cv::Point origin=pts[2];
    cv::putText( frame,//每一帧的图像
                      text,//文本内容
                      origin,//文本框左下角
                      cv::FONT_HERSHEY_SIMPLEX,//字体
                      1,//字体尺寸（大小）
                      cv::Scalar(0,0,255),//字体颜色
                      4,//字体粗细
                      8,//线型
                      0);

 }
}
//         void calAngle(cv::Mat cam,cv::Mat dis,int x,int y)
//     {
//     double fx=cam.at<double>(0,0);
//     double fy=cam.at<double>(1,1);
//     double cx=cam.at<double>(0,2);
//     double cy=cam.at<double>(1,2);
//     cv::Point2f pnt;
//     std::vector<cv::Point2f> in;
//     std::vector<cv::Point2f> out;
//     in.push_back(cv::Point2f(x,y));
//     //对像素点去畸变
//     undistortPoints(in,out,cam,dis,cv::noArray(),cam);
//     pnt=out.front();
//     //没有去畸变时的比值
//     double rx=(x-cx)/fx;
//     double ry=(y-cy)/fy;
//     //去畸变后的比值
//     double rxNew=(pnt.x-cx)/fx;
//     double ryNew=(pnt.y-cy)/fy;
//     //输出原来点的坐标和去畸变后点的坐标
//     std::cout<< "x: "<<x<<" xNew:"<<pnt.x<<std::endl;
//     std::cout<< "y: "<<y<<" yNew:"<<pnt.y<<std::endl;
//     //输出未去畸变时测得的角度和去畸变后测得的角度
//     std::cout<< "angx: "<<atan(rx)/CV_PI*180<<" angleNew:"<<atan(rxNew)/CV_PI*180<<std::endl;
//     std::cout<< "angy: "<<atan(ry)/CV_PI*180<<" angleNew:"<<atan(ryNew)/CV_PI*180<<std::endl;
//   }



#else //旧代码在下面

int main()
{

    return 0;
}

#endif
