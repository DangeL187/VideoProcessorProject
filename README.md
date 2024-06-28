# VideoProcessorProject
C++ class for rendering video and sending frames to a python program

# Before building
Download [pybind11](https://github.com/swansontec/map-macro)
```
git clone https://github.com/pybind/pybind11.git
```
Download [OpenCV](https://github.com/opencv/opencv)
> Linux:
```
sudo apt install libopencv-dev python3-opencv
```

# How to build
```
mkdir build
cd build
cmake ..
make
```

# How to use
1. Copy the generated `.so` file to the same folder as the `.py` file that you want to use
2. Run your python script or [cpp.py](https://github.com/DangeL187/VideoProcessorProject/blob/main/python/cpp.py)

# Quick docs
> General
- The `VideoProcessor` class runs two threads: a video processing thread (`VideoProcessor::processVideo`) and a frame conversion thread(`VideoProcessor::convertFrames`).
- `VideoProcessor` has two main queues: `std::queue<Frame> _frames` and `std::queue<MatFrame> _mat_frames` for storing frames.
- `VideoProcessor::processVideo` is loading video frames to the `_mat_frames` queue.
- `VideoProcessor::convertFrames` is converting [MatFrame](https://github.com/DangeL187/VideoProcessorProject/blob/main/include/Frame/MatFrame.hpp) objects to [Frame](https://github.com/DangeL187/VideoProcessorProject/blob/main/include/Frame/Frame.hpp) objects by removing elements from `_mat_frames` and adding them to the `_frames`.
- `VideoProcessor::getFrame` method is used for getting the first element of the `_frames` queue.
> Data safety
- `VideoProcessor` has two mutexes (`_frame_mutex` and `_mat_frame_mutex`) for safety data transferring.
> Efficiency
- During the operation of the program, the queues do not become overloaded and often have only 0-1 items in them at all times.
- The time it takes to get a frame from C++ to Python is about 0.0005 seconds on average, which is equivalent to 2,000 frames per second (FPS). If you only transmit the frame data in py::bytes, you can achieve better performance. In this case, getting the frame would take about 0.000002 seconds, which is approximately 300,000 to 500,000 FPS.
