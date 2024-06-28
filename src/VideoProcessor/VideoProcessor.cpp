#include "VideoProcessor/VideoProcessor.hpp"

#include "Frame/Frame.hpp"
#include "Frame/MatFrame.hpp"
#include "matToBytes.hpp"

VideoProcessor::VideoProcessor(const std::string& file_path)
    : _cap(file_path), _stop_processing(false) {
  if (!_cap.isOpened()) {
    throw std::runtime_error("Error opening video file");
  }

  _file_path = file_path;
  _delay = 1000 / _cap.get(cv::CAP_PROP_FPS);

  _processing_thread = std::thread(&VideoProcessor::processVideo, this);
  _processing_thread.detach();
  _converting_thread = std::thread(&VideoProcessor::convertFrames, this);
  _converting_thread.detach();
}

VideoProcessor::~VideoProcessor() { stop(); }

void VideoProcessor::convertFrames() {
  while (!_stop_processing) {
    py::gil_scoped_acquire acquire;

    if (_mat_frames.empty()) continue;

    std::lock_guard<std::mutex> lock_mat_frame(_mat_frame_mutex);
    std::lock_guard<std::mutex> lock_frame(_frame_mutex);

    MatFrame mat = _mat_frames.front();
    _mat_frames.pop();
    _frames.emplace(matToBytes(mat.data), mat.timestamp, mat.data.cols,
                    mat.data.rows);
  }
}

Frame VideoProcessor::getFrame() {
  if (_frames.empty()) return {};

  std::lock_guard<std::mutex> lock_frame(_frame_mutex);

  Frame frame = _frames.front();
  _frames.pop();

  return frame;
}

void VideoProcessor::processVideo() {
  cv::Mat frame;
  while (!_stop_processing) {
    if (!_cap.read(frame)) {
      _cap = cv::VideoCapture(_file_path);
    }
    {
      std::lock_guard<std::mutex> lock_mat_frame(_mat_frame_mutex);
      _mat_frames.emplace(frame, _cap.get(cv::CAP_PROP_POS_MSEC));
    }
    cv::waitKey(_delay);
  }
}

void VideoProcessor::stop() { _stop_processing = true; }
