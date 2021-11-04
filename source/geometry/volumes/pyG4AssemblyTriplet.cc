#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4AssemblyTriplet.hh>
#include <G4LogicalVolume.hh>
#include <G4AssemblyVolume.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4AssemblyTriplet(py::module &m)
{
   py::class_<G4AssemblyTriplet>(m, "G4AssemblyTriplet")

      .def(py::init<>())
      .def(py::init<G4LogicalVolume *, G4ThreeVector &, G4RotationMatrix *, G4bool>(), py::arg("pVolume"),
           py::arg("translation"), py::arg("pRotation"), py::arg("isReflection") = false)

      .def(py::init<G4AssemblyVolume *, G4ThreeVector &, G4RotationMatrix *, G4bool>(), py::arg("pAssembly"),
           py::arg("translation"), py::arg("pRotation"), py::arg("isReflection") = false)

      .def("__copy__", [](const G4AssemblyTriplet &self) { return G4AssemblyTriplet(self); })
      .def("__deepcopy__", [](const G4AssemblyTriplet &self, py::dict) { return G4AssemblyTriplet(self); })
      .def("GetVolume", &G4AssemblyTriplet::GetVolume, py::return_value_policy::reference)
      .def("SetVolume", &G4AssemblyTriplet::SetVolume, py::arg("pVolume"))
      .def("GetAssembly", &G4AssemblyTriplet::GetAssembly, py::return_value_policy::reference)
      .def("SetAssembly", &G4AssemblyTriplet::SetAssembly, py::arg("pAssembly"))
      .def("GetTranslation", &G4AssemblyTriplet::GetTranslation)
      .def("SetTranslation", &G4AssemblyTriplet::SetTranslation, py::arg("pVolume"))
      .def("GetRotation", &G4AssemblyTriplet::GetRotation, py::return_value_policy::reference)
      .def("SetRotation", &G4AssemblyTriplet::SetRotation, py::arg("pVolume"))
      .def("IsReflection", &G4AssemblyTriplet::IsReflection);
}
