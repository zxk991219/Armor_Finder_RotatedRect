# include <opencv2/opencv.hpp>

int main()
{
    cv::Mat im = cv::imread("../image/Mojave.jpg");
    cv::resize(im, im, cv::Size(960,540), (0,0), (0,0));
    cv::Rect2d r = cv::selectROI("image", im, false);
    cv::Mat imCrop = im(r);

    cv::imshow("Image", imCrop);
    cv::waitKey(0);
}
