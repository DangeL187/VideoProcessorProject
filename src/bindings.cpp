#include "Frame/Frame.hpp"
#include "VideoProcessor/VideoProcessor.hpp"

PYBIND11_MODULE(VideoProcessorProject, m) {
  py::class_<Frame>(m, "Frame")
      .def(py::init<>())
      .def("data", [](Frame& self) { return self.data; })
      .def("height", [](Frame& self) { return py::cast(self.height); })
      .def("timestamp", [](Frame& self) { return self.timestamp; })
      .def("width", [](Frame& self) { return py::cast(self.width); });

  py::class_<VideoProcessor>(m, "VideoProcessor")
      .def(py::init<std::string>())
      .def("getFrame", [](VideoProcessor& self) { return self.getFrame(); })
      .def("stop", [](VideoProcessor& self) { self.stop(); });
}
