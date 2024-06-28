#include "Frame/MatFrame.hpp"

MatFrame::MatFrame() = default;

MatFrame::MatFrame(const cv::Mat& data_, unsigned long long timestamp_) {
  data = data_;
  timestamp = timestamp_;
}