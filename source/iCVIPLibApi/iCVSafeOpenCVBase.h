#pragma once
#include <opencv2/opencv.hpp>
// Keep the input parameters and return values of the encapsulated function
// consistent with the native OpenCV function

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

class SafeOpenCVBase {
  public:
    SafeOpenCVBase() {}
    virtual ~SafeOpenCVBase() {}

  public:
    // OpenCV function with the same name
    virtual cv::Mat imread(const std::string &filename,
                           int flags = cv::IMREAD_COLOR);
    virtual bool imwrite(const std::string &filename, const cv::Mat &img,
                         const std::vector<int> &params = std::vector<int>());
    virtual void resize(const cv::Mat &src, cv::Mat &dst, cv::Size size,
                        double inv_scale_x = 0., double inv_scale_y = 0.,
                        int interpolation = cv::INTER_LINEAR);
    virtual void cvtColor(const cv::Mat &src, cv::Mat &dst, int code,
                          int dcn = 0);
    // Others Anything else you like
    virtual cv::Mat crop(const cv::Mat &src, const cv::Rect &roi,
                         bool adaptive = true);
    virtual int
    sub_mean_and_divide_std(const CHANNEL_SEPARATION_TYPE chl_sepr_type,
                            const cv::Mat &img, const float *mean_data,
                            const float *std_data, float *forward_data);
};

} // namespace ICV_SAFE_OPENCV