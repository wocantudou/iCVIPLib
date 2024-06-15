#pragma once
#include <opencv2/opencv.hpp>
// Keep the input parameters and return values of the encapsulated function
// consistent with the native OpenCV function

#define iCVimread ICV_SAFE_OPENCV::safe_imread
#define iCVimwrite ICV_SAFE_OPENCV::safe_imwrite
#define iCVresize ICV_SAFE_OPENCV::safe_resize
#define iCVcvtColor ICV_SAFE_OPENCV::safe_cvtColor
#define iCVcrop ICV_SAFE_OPENCV::safe_crop
#define iCVsub_mean_and_divide_std ICV_SAFE_OPENCV::sub_mean_and_divide_std

namespace ICV_SAFE_OPENCV {
enum CHANNEL_SEPARATION_TYPE {
    CHANNEL_SEPARATION_TYPE_NONE,
    BGRBGRBGRTORRRGGGBBB = 1,
    BGRBGRBGRTOBBBGGGRRR,
    RGBRGBRGBTORRRGGGBBB,
    RGBRGBRGBTOBBBGGGRRR,
    BGRBGRBGRTORGBRGBRGB,
    CHANNEL_SEPARATION_TYPE_COUNT,
};
cv::Mat safe_imread(const std::string &filename, int flags = cv::IMREAD_COLOR);

bool safe_imwrite(const std::string &filename, const cv::Mat &img,
                  const std::vector<int> &params = std::vector<int>());
cv::Mat safe_resize(const cv::Mat &src, const cv::Size &dsize, double fx = 0,
                    double fy = 0, int interpolation = cv::INTER_LINEAR);
cv::Mat safe_cvtColor(const cv::Mat &src, int code);

cv::Mat safe_crop(const cv::Mat &src, const cv::Rect &roi,
                  bool adaptive = true);
int sub_mean_and_divide_std(const CHANNEL_SEPARATION_TYPE chl_sepr_type,
                            const cv::Mat &img, const float *mean_data,
                            const float *std_data, float *forward_data);
} // namespace ICV_SAFE_OPENCV