#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4GeomTestVolume.hh>
#include <G4VPhysicalVolume.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4GeomTestVolume(py::module &m)
{
   py::class_<G4GeomTestVolume>(m, "G4GeomTestVolume")

      .def(py::init<G4VPhysicalVolume *, G4double, G4int, G4bool>(), py::arg("theTarget"), py::arg("theTolerance") = 0.,
           py::arg("numberOfPoints") = 10000, py::arg("theVerbosity") = true)

      .def("__copy__", [](const G4GeomTestVolume &self) { return G4GeomTestVolume(self); })
      .def("__deepcopy__", [](const G4GeomTestVolume &self, py::dict) { return G4GeomTestVolume(self); })
      .def("GetTolerance", &G4GeomTestVolume::GetTolerance)
      .def("SetTolerance", &G4GeomTestVolume::SetTolerance, py::arg("tolerance"))
      .def("GetResolution", &G4GeomTestVolume::GetResolution)
      .def("SetResolution", &G4GeomTestVolume::SetResolution, py::arg("points"))
      .def("GetVerbosity", &G4GeomTestVolume::GetVerbosity)
      .def("SetVerbosity", &G4GeomTestVolume::SetVerbosity, py::arg("verbosity"))
      .def("GetErrorsThreshold", &G4GeomTestVolume::GetErrorsThreshold)
      .def("SetErrorsThreshold", &G4GeomTestVolume::SetErrorsThreshold, py::arg("max"))
      .def("TestOverlapInTree", &G4GeomTestVolume::TestOverlapInTree)
      .def("TestRecursiveOverlap", &G4GeomTestVolume::TestRecursiveOverlap, py::arg("sLevel") = 0,
           py::arg("depth") = -1);
}
