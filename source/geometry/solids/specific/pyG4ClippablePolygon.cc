#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ClippablePolygon.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4ClippablePolygon(py::module &m)
{
   py::class_<G4ClippablePolygon>(m, "G4ClippablePolygon")

      .def(py::init<>())
      .def("__copy__", [](const G4ClippablePolygon &self) { return G4ClippablePolygon(self); })
      .def("__deepcopy__", [](const G4ClippablePolygon &self, py::dict) { return G4ClippablePolygon(self); })
      .def("AddVertexInOrder", &G4ClippablePolygon::AddVertexInOrder, py::arg("vertex"))
      .def("ClearAllVertices", &G4ClippablePolygon::ClearAllVertices)
      .def("SetNormal", &G4ClippablePolygon::SetNormal, py::arg("newNormal"))
      .def("GetNormal", &G4ClippablePolygon::GetNormal)
      .def("Clip", &G4ClippablePolygon::Clip, py::arg("voxelLimit"))
      .def("PartialClip", &G4ClippablePolygon::PartialClip, py::arg("voxelLimit"), py::arg("IgnoreMe"))
      .def("ClipAlongOneAxis", &G4ClippablePolygon::ClipAlongOneAxis, py::arg("voxelLimit"), py::arg("axis"))
      .def("GetExtent", &G4ClippablePolygon::GetExtent, py::arg("axis"), py::arg("min"), py::arg("max"))
      .def("GetMinPoint", &G4ClippablePolygon::GetMinPoint, py::arg("axis"), py::return_value_policy::reference)
      .def("GetMaxPoint", &G4ClippablePolygon::GetMaxPoint, py::arg("axis"), py::return_value_policy::reference)
      .def("GetNumVertices", &G4ClippablePolygon::GetNumVertices)
      .def("Empty", &G4ClippablePolygon::Empty)
      .def("InFrontOf", &G4ClippablePolygon::InFrontOf, py::arg("other"), py::arg("axis"))
      .def("BehindOf", &G4ClippablePolygon::BehindOf, py::arg("other"), py::arg("axis"))
      .def("GetPlanerExtent", &G4ClippablePolygon::GetPlanerExtent, py::arg("pointOnPlane"), py::arg("planeNormal"),
           py::arg("min"), py::arg("max"));
}
