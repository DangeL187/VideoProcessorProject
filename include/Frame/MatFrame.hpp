#ifndef VIDEOPROCESSORPROJECT_MATFRAME_HPP
#define VIDEOPROCESSORPROJECT_MATFRAME_HPP

#include <opencv2/opencv.hpp>

struct MatFrame {
  cv::Mat data;
  unsigned long long timestamp = 0;

  MatFrame();
  MatFrame(const cv::Mat& data_, unsigned long long timestamp_);
};

#endif  // VIDEOPROCESSORPROJECT_MATFRAME_HPP
