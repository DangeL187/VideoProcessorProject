#include "Frame/Frame.hpp"

Frame::Frame() = default;

Frame::Frame(const Frame& other) {
  py::gil_scoped_acquire acquire;
  data = other.data;
  timestamp = other.timestamp;
  width = other.width;
  height = other.height;
}

Frame& Frame::operator=(const Frame& other) {
  py::gil_scoped_acquire acquire;
  data = other.data;
  timestamp = other.timestamp;
  width = other.width;
  height = other.height;
  return *this;
}

Frame::Frame(py::bytes data_, unsigned long long timestamp_, int width_,
             int height_) {
  py::gil_scoped_acquire acquire;
  data = std::move(data_);
  timestamp = timestamp_;
  width = width_;
  height = height_;
}
