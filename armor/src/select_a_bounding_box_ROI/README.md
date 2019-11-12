# bounding box

## 框选图像

- 读入待框选图像`cv::Mat im = cv::imread("./image/Mojave.jpg");`
- 声明类cv::Rect2d的对象r
- 用cv::selectROI()给r进行赋值`cv::selecetROI("image", im, false)` 其中`false`变量指的是去除选框中心十字
- 将选取的图像储存在Mat imCrop中`cv::Mat imCrop = im(r);`
- 将选取的图像显示出来`cv::imshow("Image", imCrop)`
