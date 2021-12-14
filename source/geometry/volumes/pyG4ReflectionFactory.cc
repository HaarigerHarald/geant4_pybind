#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ReflectionFactory.hh>
#include <G4VPhysicalVolume.hh>
#include <G4LogicalVolume.hh>
#include <G4VSolid.hh>
#include <G4VPVDivisionFactory.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4ReflectionFactory(py::module &m)
{
   py::class_<G4ReflectionFactory, py::nodelete>(m, "G4ReflectionFactory")

      .def_static("Instance", &G4ReflectionFactory::Instance, py::return_value_policy::reference)
      .def("Place", &G4ReflectionFactory::Place, py::arg("transform3D"), py::arg("name"), py::arg("LV"),
           py::arg("motherLV"), py::arg("isMany"), py::arg("copyNo"), py::arg("surfCheck") = false)

      .def("Replicate", &G4ReflectionFactory::Replicate, py::arg("name"), py::arg("LV"), py::arg("motherLV"),
           py::arg("axis"), py::arg("nofReplicas"), py::arg("width"), py::arg("offset") = 0.)

      .def("Divide",
           py::overload_cast<const G4String &, G4LogicalVolume *, G4LogicalVolume *, EAxis, G4int, G4double, G4double>(
              &G4ReflectionFactory::Divide),
           py::arg("name"), py::arg("LV"), py::arg("motherLV"), py::arg("axis"), py::arg("nofDivisions"),
           py::arg("width"), py::arg("offset"))

      .def("Divide",
           py::overload_cast<const G4String &, G4LogicalVolume *, G4LogicalVolume *, EAxis, G4int, G4double>(
              &G4ReflectionFactory::Divide),
           py::arg("name"), py::arg("LV"), py::arg("motherLV"), py::arg("axis"), py::arg("nofDivisions"),
           py::arg("offset"))

      .def("Divide",
           py::overload_cast<const G4String &, G4LogicalVolume *, G4LogicalVolume *, EAxis, G4double, G4double>(
              &G4ReflectionFactory::Divide),
           py::arg("name"), py::arg("LV"), py::arg("motherLV"), py::arg("axis"), py::arg("width"), py::arg("offset"))

      .def("SetVerboseLevel", &G4ReflectionFactory::SetVerboseLevel, py::arg("verboseLevel"))
      .def("GetVerboseLevel", &G4ReflectionFactory::GetVerboseLevel)
      .def("SetVolumesNameExtension", &G4ReflectionFactory::SetVolumesNameExtension, py::arg("nameExtension"))
      .def("GetVolumesNameExtension", &G4ReflectionFactory::GetVolumesNameExtension)
      .def("SetScalePrecision", &G4ReflectionFactory::SetScalePrecision, py::arg("scaleValue"))
      .def("GetScalePrecision", &G4ReflectionFactory::GetScalePrecision)
      .def("GetConstituentLV", &G4ReflectionFactory::GetConstituentLV, py::arg("reflLV"),
           py::return_value_policy::reference)

      .def("GetReflectedLV", &G4ReflectionFactory::GetReflectedLV, py::arg("lv"), py::return_value_policy::reference)
      .def("IsConstituent", &G4ReflectionFactory::IsConstituent, py::arg("lv"))
      .def("IsReflected", &G4ReflectionFactory::IsReflected, py::arg("lv"))
      .def("GetReflectedVolumesMap", &G4ReflectionFactory::GetReflectedVolumesMap)
      .def("Clean", &G4ReflectionFactory::Clean);
}
