#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4PrimaryVertex.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4PrimaryVertex(py::module &m)
{
   py::class_<G4PrimaryVertex>(m, "G4PrimaryVertex", "primary vertex")
      .def(py::init<>())
      .def(py::init<G4double, G4double, G4double, G4double>())
      .def(py::init<G4ThreeVector, G4double>())

      .def_property_readonly("X0", &G4PrimaryVertex::GetX0)
      .def_property_readonly("Y0", &G4PrimaryVertex::GetY0)
      .def_property_readonly("Z0", &G4PrimaryVertex::GetZ0)
      .def_property_readonly("T0", &G4PrimaryVertex::GetT0)

      .def("GetPosition", &G4PrimaryVertex::GetPosition)
      .def("GetX0", &G4PrimaryVertex::GetX0)
      .def("GetY0", &G4PrimaryVertex::GetY0)
      .def("GetZ0", &G4PrimaryVertex::GetZ0)
      .def("GetT0", &G4PrimaryVertex::GetT0)
      .def("GetNumberOfParticle", &G4PrimaryVertex::GetNumberOfParticle)
      .def("GetPrimary", &G4PrimaryVertex::GetPrimary, py::arg("i") = 0, py::return_value_policy::reference_internal)
      .def("SetPrimary", &G4PrimaryVertex::SetPrimary)
      .def("GetWeight", &G4PrimaryVertex::GetWeight)
      .def("SetWeight", &G4PrimaryVertex::SetWeight)
      .def("Print", &G4PrimaryVertex::Print);
}
