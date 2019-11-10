# include <opencv2/opencv.hpp>
# include <vector>
# include <iostream>
int main()
{
    cv::Mat src, gray, thr, canny_output;
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;

    src = cv::imread("../image/multiple-blob.png");
    
    cv::imshow("src", src);
    cv::waitKey(0);

    //灰度图像以及二值化
    cv::cvtColor(src, gray, CV_RGB2GRAY);
    // cv::threshold(gray, thr, 100, 255, CV_THRESH_BINARY);

    cv::imshow("gray", gray);
    cv::waitKey(0);

    //找出图像轮廓
    cv::Canny(gray, canny_output, 50, 150, 3);
    cv::findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0,0));

    cv::imshow("Contours", canny_output);
    cv::waitKey(0);

    std::cout<<"轮廓数："<<contours.size()<< std::endl;

    //计算轮廓的moment
    std::vector<cv::Moments> mu(contours.size());
    for(int i=0; i<contours.size(); i++)
    {mu[i]=cv::moments(contours[i], false);}

    //计算轮廓的质心
    std::vector<cv::Point2f> mc(contours.size());
    for(int i=0; i<contours.size();i++)
    {mc[i] = cv::Point2f(mu[i].m10/mu[i].m00, mu[i].m01/mu[i].m00);}

    //输出轮廓与质心图像
    cv::Mat drawing(canny_output.size(), CV_8UC3, cv::Scalar(255,255,255));
    for(int i=0;i<contours.size();i++)
    {
        cv::Scalar color = cv::Scalar(167,155,0);
        cv::Scalar color_point = cv::Scalar(0,0,0);
        cv::drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, cv::Point());
        cv::circle(drawing, mc[i], 4, color_point, -1, 8, 0);        
    }
    cv::imshow("Contours_p", drawing);
    cv::waitKey(0);

}
