#ifndef VIDEOPROCESSORPROJECT_MATTOBYTES_HPP
#define VIDEOPROCESSORPROJECT_MATTOBYTES_HPP

#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include <opencv2/opencv.hpp>

namespace py = pybind11;

py::bytes matToBytes(const cv::Mat& image);

#endif  // VIDEOPROCESSORPROJECT_MATTOBYTES_HPP
