#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4TessellatedGeometryAlgorithms.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4TessellatedGeometryAlgorithms(py::module &m)
{
   py::class_<G4TessellatedGeometryAlgorithms>(m, "G4TessellatedGeometryAlgorithms")

      .def(py::init<>())
      .def("__copy__",
           [](const G4TessellatedGeometryAlgorithms &self) { return G4TessellatedGeometryAlgorithms(self); })

      .def("__deepcopy__",
           [](const G4TessellatedGeometryAlgorithms &self, py::dict) { return G4TessellatedGeometryAlgorithms(self); })

      .def_static("IntersectLineAndTriangle2D", &G4TessellatedGeometryAlgorithms::IntersectLineAndTriangle2D,
                  py::arg("p"), py::arg("v"), py::arg("p0"), py::arg("e0"), py::arg("e1"), py::arg("location"))

      .def_static("IntersectLineAndLineSegment2D", &G4TessellatedGeometryAlgorithms::IntersectLineAndLineSegment2D,
                  py::arg("p0"), py::arg("d0"), py::arg("p1"), py::arg("d1"), py::arg("location"))

      .def_static("cross", &G4TessellatedGeometryAlgorithms::cross, py::arg("v1"), py::arg("v2"));
}
