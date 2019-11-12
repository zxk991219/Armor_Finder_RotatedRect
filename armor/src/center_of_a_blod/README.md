# Find the Center of a Blob

## 一些问题

- 为什么blob center会出来很多轮廓(273个)?
- 不太懂`std::vector<cv::Vec4i> hierarchy`有什么作用
---

## 笔记

> Blob是具有连续性的一些像素
>
> Blob的质心指的是构成该Blob的像素值的算数平均值

## 图像的矩 Moment

> 从图像中计算出来的矩通常描述了图像不同种类的几何特征如：大小、灰度、方向、形状等，图像矩广泛应用于模式识别、目标分类、目标识别与防伪估计、图像编码与重构等领域。

## 图像的质心

> Cx = M10/M00
>
> Cy = M01/M00

## 查找Blob质心的算法

- 灰度图像
- 对图像二值化
- 使用cv::Canny()找出图像轮廓
- 计算轮廓的moment
- 计算轮廓的质心
- 输出轮廓与质心图像

## 代码写法要点

- 用`std::vector<std::vector<cv::Point> > contours`将轮廓的点云储存在二维容器contours里
- 用`std::vector<cv::Moments> mu(contours.size())`初始化一个储存图像矩的容器
- 用`std::vector<cv::Point2f> mc(contours.size()`储存质心位置
- 用`cv::Mat drawing(canny_output.size(), CV_8UC3, cv::Scalar(255,255,255))`来初始化一个canny_output大小相同的Mat
- 用`cv::Scalar color = cv:: Scalar(167,155,0)`来设置一个颜色值
- 用`cv::drawContours()`来画出轮廓图像
- 用`cv::circle()`来画出一个圆的图像
