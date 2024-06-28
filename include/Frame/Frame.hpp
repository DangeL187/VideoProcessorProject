#ifndef VIDEOPROCESSORPROJECT_FRAME_HPP
#define VIDEOPROCESSORPROJECT_FRAME_HPP

#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

struct Frame {
  py::bytes data;
  unsigned long long timestamp = 0;
  int width = 0;
  int height = 0;

  Frame();
  Frame(const Frame& other);
  Frame& operator=(const Frame& other);
  Frame(py::bytes data_, unsigned long long timestamp_, int width_,
        int height_);
};

#endif  // VIDEOPROCESSORPROJECT_FRAME_HPP
