# 2019.10.18更新：
## 只完成了classifier.hpp&.cpp
中德周内课比较多，所以只完成了classifier，但是我还有一些想法去优化我写的classifier.hpp，今天晚上我再改改
我还想改进的是用positive图像集生成一个模板再进行比较，晚些时候再交给你吧

# 2019.10.19更新：
在classifier.hpp中加入对输入图像大小的压缩：压缩至与模板图像一致

## classifier.cpp 输出：

```c++
# hanxuyuan @ hanxuyuan-ThinkPad-T570 in ~/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/build on git:master x [16:26:54] 
$ ./classifier
以下是正样本结果
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/positive/T2.png的gain是2328
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/positive/T3.png的gain是1122
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/positive/T4.png的gain是1065
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/positive/T5.png的gain是1104
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/positive/T6.png的gain是1407
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/positive/T7.png的gain是21
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/positive/T14.png的gain是477
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/positive/T23333.png的gain是186
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/positive/Twtf.png的gain是1044
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/positive/Tx.png的gain是1230
这组图像的最小gain是21
这组图像的最大gain是2328
以下是负样本结果
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/negative/F1.png的gain是654
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/negative/F2.png的gain是486
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/negative/F3.png的gain是9
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/negative/F4.png的gain是141
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/negative/F5.png的gain是123
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/negative/F6.png的gain是384
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/negative/F7.png的gain是183
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/negative/F8.png的gain是282
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/negative/F9.png的gain是0
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/negative/F10.png的gain是1227
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/negative/F11.png的gain是2328
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/negative/F12.png的gain是1218
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/negative/F13.png的gain是0
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/negative/F14.png的gain是2328
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/negative/F15.png的gain是0
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/negative/F16.png的gain是0
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/negative/F17.png的gain是1509
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/negative/F18.png的gain是1236
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/negative/F666.png的gain是588
/home/hanxuyuan/Documents/CS/Computer-Vision/CVcode/SPTraining-VisionGroup/Assignment/assignments_20191013_hanxuyuan/classifier/armor/negative/F886.png的gain是399
这组图像的最小gain是0
这组图像的最大gain是2328
```

