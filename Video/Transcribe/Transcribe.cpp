#include <stdafx.h/stdafx.cpp>
#include <iostream>
#include "cv.h"
#include <highgui.h>
#include "cxcore.h"
 
int _tmain(int argc, _TCHAR* argv[])
{
	IplImage* frame = NULL;
	CvCapture* capture = cvCreateCameraCapture(0);
	CvVideoWriter* video=NULL;
 
	if(!capture)
	{
		cout<<"Camera does not work correctly!\n"<<endl;
	}
	else
	{
		frame=cvQueryFrame(capture); //首先取得摄像头中的一帧
		video=cvCreateVideoWriter("D:\\XXX.avi", CV_FOURCC('X', 'V', 'I', 'D'), 25, cvSize(frame->width,frame->height)); 
							//创建CvVideoWriter对象并分配空间
							//保存的文件名为camera.avi，编码要在运行程序时选择，大小就是摄像头视频的大小，帧频率是32
		if(video) //如果能创建CvVideoWriter对象则表明成功
		{
			cout<<"VideoWriter has created."<<endl; 
		}
		cvNamedWindow("Camera Video",1); //新建一个窗口
		while(1)
		{
			if(!cvQueryFrame(capture) )
			{	cout<<"do not receive any picture!";
				break;
			}
			else
			{
				cout<<cvWriteFrame(video,frame)<<endl;
				cvShowImage("Camera Video",frame);
				if(cvWaitKey(2)>0)
					break;
			}
		}
	
	}
	
	
	
	cvReleaseCapture(&capture);
	cvDestroyWindow("avi");
 
	return 0;
}