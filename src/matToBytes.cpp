#include "matToBytes.hpp"

py::bytes matToBytes(const cv::Mat& image) {
  if (image.empty()) {
    return {};
  }

  std::vector<unsigned char> bytes;
  cv::imencode(".png", image, bytes);

  return {reinterpret_cast<char*>(bytes.data()), bytes.size()};
}