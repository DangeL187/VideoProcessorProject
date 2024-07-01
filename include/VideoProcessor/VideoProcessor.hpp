#ifndef VIDEOPROCESSORPROJECT_VIDEOPROCESSOR_HPP
#define VIDEOPROCESSORPROJECT_VIDEOPROCESSOR_HPP

#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include <chrono>
#include <mutex>
#include <opencv2/opencv.hpp>
#include <queue>
#include <thread>
#include <utility>

namespace py = pybind11;

class Frame;
class MatFrame;

class VideoProcessor {
 public:
  explicit VideoProcessor(const std::string& file_path);
  ~VideoProcessor();

  void convertFrames();
  Frame getFrame();
  void stop();

 private:
  void dropFrames(auto& queue, unsigned short frames_limit, unsigned short frames_to_drop = 2);
  void processVideo();

  cv::VideoCapture _cap;
  std::thread _converting_thread;
  unsigned int _delay = 1;
  std::string _file_path;
  std::mutex _frame_mutex;
  std::queue<Frame> _frames;
  std::mutex _mat_frame_mutex;
  std::queue<MatFrame> _mat_frames;
  std::thread _processing_thread;
  bool _stop_processing;
};

#endif  // VIDEOPROCESSORPROJECT_VIDEOPROCESSOR_HPP
