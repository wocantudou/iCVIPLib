#include "iCVIPLibApi.h"
#include <iostream>
#include <stdlib.h>

#define CHECK_IMAGE_EMPTY(img)                                                 \
    if (img.empty()) {                                                         \
        std::cerr << "Opencv's Mat is empty." << std::endl;                    \
        return EXIT_FAILURE;                                                   \
    }
#define CHECK_RETURN_BOOL(flag)                                                \
    if (!flag) {                                                               \
        std::cerr << "Bool : The function failed to be executed."              \
                  << std::endl;                                                \
        return EXIT_FAILURE;                                                   \
    }
#define CHECK_RETURN_INT(ret)                                                  \
    if (ret) {                                                                 \
        std::cerr << "Integer : The function failed to be executed."           \
                  << std::endl;                                                \
        return EXIT_FAILURE;                                                   \
    }
int main(int argc, char *argv[]) {
    int ret = EXIT_SUCCESS;
    // 检查参数个数是否正确
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>"
                  << std::endl;
        return EXIT_FAILURE;
    }
    // 读取文件路径和保存文件路径
    std::string input_file = argv[1];
    std::string output_file = argv[2];
    std::cout << "Hello World" << std::endl;
    cv::Mat img = iCVimread(input_file);
    CHECK_IMAGE_EMPTY(img);
    cv::Mat img_rsz;
    iCVresize(img, img_rsz, cv::Size(100, 100));
    CHECK_IMAGE_EMPTY(img_rsz);
    bool flag = iCVimwrite(output_file, img_rsz);
    CHECK_RETURN_BOOL(flag);
    return ret;
}