nclude "cv.h";
 2 #include "cxcore.h"
 3 #include "highgui.h"
 4 #include <iostream>
 5 
 6 using namespace std;
 7 int main()
 8 {
 9    CvCapture* capture=cvCaptureFromCAM(-1);
10    CvVideoWriter* video=NULL;
11    IplImage* frame=NULL;
12    int n;
13    if(!capture) //如果不能打开摄像头给出警告
14    {
15       cout<<"Can not open the camera."<<endl;
16       return -1;
17    }
18    else
19    {
20       frame=cvQueryFrame(capture); //首先取得摄像头中的一帧
21       video=cvCreateVideoWriter("camera.avi", CV_FOURCC('X', 'V', 'I', 'D'), 25,
22       cvSize(frame->width,frame->height)); //创建CvVideoWriter对象并分配空间
23 //保存的文件名为camera.avi，编码要在运行程序时选择，大小就是摄像头视频的大小，帧频率是32
24       if(video) //如果能创建CvVideoWriter对象则表明成功
25       {
26          cout<<"VideoWriter has created."<<endl;
27       }
28 
29       cvNamedWindow("Camera Video",1); //新建一个窗口
30       int i = 0;
31       while(i <= 200) // 让它循环200次自动停止录取
32       {
33          frame=cvQueryFrame(capture); //从CvCapture中获得一帧
34          if(!frame)
35          {
36             cout<<"Can not get frame from the capture."<<endl;
37             break;
38          }
39          n=cvWriteFrame(video,frame); //判断是否写入成功，如果返回的是1，表示写入成功
40          cout<<n<<endl;
41          cvShowImage("Camera Video",frame); //显示视频内容的图片
42          i++;
43          if(cvWaitKey(2)>0) 
44             break; //有其他键盘响应，则退出
45       }
46 
47       cvReleaseVideoWriter(&video);
48       cvReleaseCapture(&capture);
49       cvDestroyWindow("Camera Video");
50    }
51    return 0;
52 }
