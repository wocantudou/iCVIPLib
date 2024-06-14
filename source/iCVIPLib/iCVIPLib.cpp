#include "iCVIPLib.h"
#include <fstream>

namespace ICV_SAFE_OPENCV {
bool is_file_exist(const std::string &filename) {
    std::ifstream file(filename);
    return file.good();
}
cv::Mat safe_imread(const std::string &filename, int flags) {
    // Check if file exists
    if (!is_file_exist(filename)) {
        std::cerr << "Error: The file '" << filename << "' does not exist."
                  << std::endl;
        return cv::Mat();
    }

    // Read image
    cv::Mat image = cv::imread(filename, flags);
    if (image.empty()) {
        std::cerr << "Error: The file '" << filename
                  << "' could not be read as an image." << std::endl;
    }
    return image;
}

bool safe_imwrite(const std::string &filename, const cv::Mat &img,
                  const std::vector<int> &params) {
    // Check if directory exists
    std::string directory = filename.substr(0, filename.find_last_of('/'));
    if (!directory.empty() && !is_file_exist(directory)) {
        std::cerr << "Error: The directory '" << directory
                  << "' does not exist." << std::endl;
        return false;
    }

    // Check if image is empty
    if (img.empty()) {
        std::cerr << "Error: The image to be saved is empty." << std::endl;
        return false;
    }

    // Write image
    try {
        bool success = cv::imwrite(filename, img, params);
        if (!success) {
            std::cerr << "Error: The image could not be saved to '" << filename
                      << "'." << std::endl;
        }
        return success;
    } catch (cv::Exception &e) {
        std::cerr << "Exception occurred while writing the image: " << e.msg
                  << std::endl;
        return false;
    }
}
cv::Mat safe_resize(const cv::Mat &src, const cv::Size &dsize, double fx,
                    double fy, int interpolation) {
    // Check if source image is empty
    if (src.empty()) {
        std::cerr << "Error: The source image is empty." << std::endl;
        return cv::Mat();
    }

    // Check if destination size is valid
    if (dsize.width <= 0 || dsize.height <= 0) {
        std::cerr << "Error: Invalid destination size." << std::endl;
        return cv::Mat();
    }

    // Resize image
    try {
        cv::Mat resized_image;
        cv::resize(src, resized_image, dsize, fx, fy, interpolation);
        return resized_image;
    } catch (cv::Exception &e) {
        std::cerr << "Exception occurred while resizing the image: " << e.msg
                  << std::endl;
        return cv::Mat();
    }
}

cv::Mat safe_cvtColor(const cv::Mat &src, int code) {
    // Check if source image is empty
    if (src.empty()) {
        std::cerr << "Error: The source image is empty." << std::endl;
        return cv::Mat();
    }

    // Convert color
    try {
        cv::Mat converted_image;
        cv::cvtColor(src, converted_image, code);
        return converted_image;
    } catch (cv::Exception &e) {
        std::cerr
            << "Exception occurred while converting the image color space: "
            << e.msg << std::endl;
        return cv::Mat();
    }
}

cv::Mat safe_crop(const cv::Mat &src, const cv::Rect &roi, bool adaptive) {
    // Check if source image is empty
    if (src.empty()) {
        std::cerr << "Error: The source image is empty." << std::endl;
        return cv::Mat();
    }
    cv::Rect adaptive_roi;
    adaptive_roi = roi;
    if (!adaptive) {
        // Check if the region of interest (ROI) is within the bounds of the
        // source
        // image
        if (roi.x < 0 || roi.y < 0 || roi.x + roi.width > src.cols ||
            roi.y + roi.height > src.rows) {
            std::cerr
                << "Error: The region of interest is out of the image bounds."
                << std::endl;
            return cv::Mat();
        }
    } else {
        if (roi.x < 0) {
            adaptive_roi.x = 0;
        }
        if (roi.y < 0) {
            adaptive_roi.y = 0;
        }
        if (roi.x + roi.width > src.cols) {
            adaptive_roi.width = src.cols - 1 - adaptive_roi.x;
        }

        if (roi.y + roi.height > src.rows) {
            adaptive_roi.height = src.rows - 1 - adaptive_roi.y;
        }
        if (adaptive_roi.width <= 1 || adaptive_roi.height <= 1) {
            std::cerr << "Error: The region of interest is only one pixel."
                      << std::endl;
            return cv::Mat();
        }
    }

    // Crop image
    try {
        cv::Mat cropped_image = src(roi);
        return cropped_image;
    } catch (cv::Exception &e) {
        std::cerr << "Exception occurred while cropping the image: " << e.msg
                  << std::endl;
        return cv::Mat();
    }
}

int sub_mean_and_divide_std(const CHANNEL_SEPARATION_TYPE chl_sepr_type,
                            const cv::Mat &img, const float *mean_data,
                            const float *std_data, float *forward_data) {

    if (img.empty()) {
        std::cerr << "empty image." << std::endl;
        return EXIT_FAILURE;
    }
    int channel_size = img.channels();
    int hw_size = img.rows * img.cols;
    float mean_b = 0, mean_g = 0, mean_r = 0;
    if (mean_data) {
        if (channel_size > 1) {
            mean_r = mean_data[0];
            mean_g = mean_data[1];
        }
        mean_b = mean_data[2];
    }

    float std_b = 1, std_g = 1, std_r = 1;
    if (std_data) {
        if (channel_size > 1) {
            if (0 == std_data[0]) {
                std::cerr << "std_data[0] is zero" << std::endl;
                return EXIT_FAILURE;
            }
            std_r = std_data[0];
            if (0 == std_data[1]) {
                std::cerr << "std_data[1] is zero" << std::endl;
                return EXIT_FAILURE;
            }
            std_g = std_data[1];
        }
        if (0 == std_data[2]) {
            std::cerr << "std_data[2] is zero" << std::endl;
            return EXIT_FAILURE;
        }
        std_b = std_data[2];
    }
    // HWC2HWC
    if (BGRBGRBGRTORGBRGBRGB == chl_sepr_type) {
        float *ptr_slide = forward_data;
        unsigned char *src_data = (unsigned char *)img.data;
        for (int i = 0; i < hw_size; i++) {
            unsigned char *each_channel_data = src_data + i * channel_size;
            unsigned char *p_r = each_channel_data + 2; // r
            unsigned char *p_g = each_channel_data + 1; // g
            unsigned char *p_b = each_channel_data + 0; // b

            *ptr_slide++ = (static_cast<float>(*p_r) - mean_r) / std_r;
            *ptr_slide++ = (static_cast<float>(*p_g) - mean_g) / std_g;
            *ptr_slide++ = (static_cast<float>(*p_b) - mean_b) / std_b;
        }
        return EXIT_SUCCESS;
    }
    // HWC2CHW
    float *ptr_image_r = forward_data;
    float *ptr_image_g = forward_data + hw_size;
    float *ptr_image_b = forward_data + hw_size * 2;
    if (BGRBGRBGRTORRRGGGBBB == chl_sepr_type ||
        RGBRGBRGBTORRRGGGBBB == chl_sepr_type) {
        float *ptr_image_r = forward_data;
        float *ptr_image_g = forward_data + hw_size;
        float *ptr_image_b = forward_data + hw_size * 2;
    } else if (BGRBGRBGRTOBBBGGGRRR == chl_sepr_type ||
               RGBRGBRGBTOBBBGGGRRR == chl_sepr_type) {
        ptr_image_b = forward_data;
        ptr_image_g = forward_data + hw_size;
        ptr_image_r = forward_data + hw_size * 2;
    } else {
        std::cerr << "Unsupport ChlSeprType : " << chl_sepr_type << std::endl;
        return EXIT_FAILURE;
    }

    for (int i = 0; i < img.rows; i++) {
        unsigned char *data =
            const_cast<unsigned char *>(img.ptr<unsigned char>(i));
        for (int j = 0; j < img.cols; j++) {
            if (BGRBGRBGRTORRRGGGBBB == chl_sepr_type ||
                BGRBGRBGRTOBBBGGGRRR == chl_sepr_type) {
                if (channel_size > 1) {
                    *ptr_image_b++ =
                        (static_cast<float>(*data++) - mean_b) / std_b;
                    *ptr_image_g++ =
                        (static_cast<float>(*data++) - mean_g) / std_g;
                }
                *ptr_image_r++ = (static_cast<float>(*data++) - mean_r) / std_r;
            } else {
                if (channel_size > 1) {
                    *ptr_image_r++ =
                        (static_cast<float>(*data++) - mean_r) / std_r;
                    *ptr_image_g++ =
                        (static_cast<float>(*data++) - mean_g) / std_g;
                }
                *ptr_image_b++ = (static_cast<float>(*data++) - mean_b) / std_b;
            }
        }
    }
    return EXIT_SUCCESS;
}

} // namespace ICV_SAFE_OPENCV
