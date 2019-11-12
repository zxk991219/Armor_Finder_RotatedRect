#include "classifier.hpp"
#include "other/include/timer.hpp"

int main()
{
    sp::timer timer;
    timer.reset();
    sp::template_classifier test;
    std::cout << "以下是正样本结果" << std::endl;
    test.classifier("../image_files/template_file.txt", "../image_files/image_positive_list.txt");
    std::cout << "以下是负样本结果" << std::endl;
    test.classifier("../image_files/template_file.txt", "../image_files/image_negative_list.txt");
    std::cout << "程序运行时间：" << timer.get() << std::endl;
    return 0;
}

