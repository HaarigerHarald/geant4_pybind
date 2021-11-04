#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4LineSection.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4LineSection(py::module &m)
{
   py::class_<G4LineSection>(m, "G4LineSection")

      .def(py::init<const G4ThreeVector &, const G4ThreeVector &>(), py::arg("PntA"), py::arg("PntB"))
      .def("__copy__", [](const G4LineSection &self) { return G4LineSection(self); })
      .def("__deepcopy__", [](const G4LineSection &self, py::dict) { return G4LineSection(self); })
      .def("Dist", &G4LineSection::Dist, py::arg("OtherPnt"))
      .def("GetABdistanceSq", &G4LineSection::GetABdistanceSq)
      .def_static("Distline", &G4LineSection::Distline, py::arg("OtherPnt"), py::arg("LinePntA"), py::arg("LinePntB"));
}
