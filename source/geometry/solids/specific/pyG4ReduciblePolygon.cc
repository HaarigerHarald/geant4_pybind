#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ReduciblePolygon.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4ReduciblePolygon(py::module &m)
{
   py::class_<G4ReduciblePolygon>(m, "G4ReduciblePolygon")

      .def(py::init<const G4double *, const G4double *, G4int>(), py::arg("a"), py::arg("b"), py::arg("n"))
      .def(py::init<const G4double *, const G4double *, const G4double *, G4int>(), py::arg("rmin"), py::arg("rmax"),
           py::arg("z"), py::arg("n"))

      .def("NumVertices", &G4ReduciblePolygon::NumVertices)
      .def("Amin", &G4ReduciblePolygon::Amin)
      .def("Amax", &G4ReduciblePolygon::Amax)
      .def("Bmin", &G4ReduciblePolygon::Bmin)
      .def("Bmax", &G4ReduciblePolygon::Bmax)
      .def("CopyVertices", &G4ReduciblePolygon::CopyVertices, py::arg("a"), py::arg("b"))
      .def("ScaleA", &G4ReduciblePolygon::ScaleA, py::arg("scale"))
      .def("ScaleB", &G4ReduciblePolygon::ScaleB, py::arg("scale"))
      .def("RemoveDuplicateVertices", &G4ReduciblePolygon::RemoveDuplicateVertices, py::arg("tolerance"))

      .def("RemoveRedundantVertices", &G4ReduciblePolygon::RemoveRedundantVertices, py::arg("tolerance"))

      .def("ReverseOrder", &G4ReduciblePolygon::ReverseOrder)
      .def("StartWithZMin", &G4ReduciblePolygon::StartWithZMin)
      .def("Area", &G4ReduciblePolygon::Area)
      .def("CrossesItself", &G4ReduciblePolygon::CrossesItself, py::arg("tolerance"))
      .def("BisectedBy", &G4ReduciblePolygon::BisectedBy, py::arg("a1"), py::arg("b1"), py::arg("a2"), py::arg("b2"),
           py::arg("tolerance"))

      .def("Print", &G4ReduciblePolygon::Print);

   py::class_<G4ReduciblePolygonIterator>(m, "G4ReduciblePolygonIterator")

      .def(py::init<const G4ReduciblePolygon *>(), py::arg("theSubject"))
      .def("__copy__", [](const G4ReduciblePolygonIterator &self) { return G4ReduciblePolygonIterator(self); })
      .def("__deepcopy__",
           [](const G4ReduciblePolygonIterator &self, py::dict) { return G4ReduciblePolygonIterator(self); })

      .def("Begin", &G4ReduciblePolygonIterator::Begin)
      .def("Next", &G4ReduciblePolygonIterator::Next)
      .def("Valid", &G4ReduciblePolygonIterator::Valid)
      .def("GetA", &G4ReduciblePolygonIterator::GetA)
      .def("GetB", &G4ReduciblePolygonIterator::GetB);
}
