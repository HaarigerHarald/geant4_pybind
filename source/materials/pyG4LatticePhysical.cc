#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4LatticePhysical.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4LatticePhysical(py::module &m)
{
   py::class_<G4LatticePhysical>(m, "G4LatticePhysical")

      .def("__copy__", [](const G4LatticePhysical &self) { return new G4LatticePhysical(self); })
      .def("__deepcopy__", [](const G4LatticePhysical &self, py::dict) { return new G4LatticePhysical(self); })
      .def(py::init<const G4LatticeLogical *, const G4RotationMatrix *>(),
           py::arg("Lat") = static_cast<const G4LatticeLogical *>(nullptr),
           py::arg("Rot") = static_cast<const G4RotationMatrix *>(nullptr))

      .def("GetAnhDecConstant", &G4LatticePhysical::GetAnhDecConstant)
      .def("GetBeta", &G4LatticePhysical::GetBeta)
      .def("GetFTDOS", &G4LatticePhysical::GetFTDOS)
      .def("GetGamma", &G4LatticePhysical::GetGamma)
      .def("GetLDOS", &G4LatticePhysical::GetLDOS)
      .def("GetLambda", &G4LatticePhysical::GetLambda)
      .def("GetLattice", &G4LatticePhysical::GetLattice, py::return_value_policy::reference)
      .def("GetMu", &G4LatticePhysical::GetMu)
      .def("GetSTDOS", &G4LatticePhysical::GetSTDOS)
      .def("GetScatteringConstant", &G4LatticePhysical::GetScatteringConstant)
      .def("MapKtoV", &G4LatticePhysical::MapKtoV)
      .def("MapKtoVDir", &G4LatticePhysical::MapKtoVDir)
      .def("RotateToGlobal", &G4LatticePhysical::RotateToGlobal, py::arg("dir"))
      .def("RotateToLocal", &G4LatticePhysical::RotateToLocal, py::arg("dir"))
      .def("SetLatticeLogical", &G4LatticePhysical::SetLatticeLogical, py::arg("Lat"))
      .def("SetLatticeOrientation", &G4LatticePhysical::SetLatticeOrientation)
      .def("SetMillerOrientation", &G4LatticePhysical::SetMillerOrientation)
      .def("SetPhysicalOrientation", &G4LatticePhysical::SetPhysicalOrientation, py::arg("Rot"))
      .def("SetVerboseLevel", &G4LatticePhysical::SetVerboseLevel, py::arg("vb"));
}
