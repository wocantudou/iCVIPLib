#pragma once
#include "iCVSafeOpenCVBase.h"
#include "utils/Singleton.hpp"

namespace ICV_SAFE_OPENCV {
class SafeOpenCVReal : public SafeOpenCVBase {
  public:
    SafeOpenCVReal() {}
    ~SafeOpenCVReal() {}
    /*************************************************************************/
    // If you have a better way to do it, you can uncomment and rewrite the
    // methods of the subclass.
    /*************************************************************************/
    // cv::Mat imread(const std::string &filename,
    //                int flags = cv::IMREAD_COLOR) override {}

    // bool imwrite(const std::string &filename, const cv::Mat &img,
    //              const std::vector<int> &params = std::vector<int>())
    //              override {
    // }
    // virtual void resize(const cv::Mat &src, cv::Mat &dst, cv::Size &dsize,
    //                     double inv_scale_x = 0., double inv_scale_y = 0.,
    //                     int interpolation = cv::INTER_LINEAR) {}
    // virtual void cvtColor(const cv::Mat &src, cv::Mat &dst, int code,
    //                       int dcn = 0) {}

    // cv::Mat crop(const cv::Mat &src, const cv::Rect &roi,
    //              bool adaptive = true) override {}
    // int sub_mean_and_divide_std(const CHANNEL_SEPARATION_TYPE chl_sepr_type,
    //                             const cv::Mat &img, const float *mean_data,
    //                             const float *std_data,
    //                             float *forward_data) override {}
};
} // namespace ICV_SAFE_OPENCV
#define SafeOpenCVRealClass ICV_SAFE_OPENCV::SafeOpenCVReal
#define SafeOpenCVRealInst ICVSingletonClass<SafeOpenCVRealClass>::get_inst