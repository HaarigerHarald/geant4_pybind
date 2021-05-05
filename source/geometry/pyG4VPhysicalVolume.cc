#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4LogicalVolume.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4VPhysicalVolume(py::module &m)
{
   py::class_<G4VPhysicalVolume, std::unique_ptr<G4VPhysicalVolume, py::nodelete>>(m, "G4VPhysicalVolume",
                                                                                   "physical volume class")

      .def("SetTranslation", &G4VPhysicalVolume::SetTranslation)
      .def("GetTranslation", &G4VPhysicalVolume::GetTranslation)
      .def("GetObjectTranslation", &G4VPhysicalVolume::GetObjectTranslation)
      .def("GetFrameTranslation", &G4VPhysicalVolume::GetObjectTranslation)

      .def("SetRotation", &G4VPhysicalVolume::SetRotation)
      .def("GetRotation", py::overload_cast<>(&G4VPhysicalVolume::GetRotation, py::const_),
           py::return_value_policy::reference_internal)

      .def("GetRotation", py::overload_cast<>(&G4VPhysicalVolume::GetRotation),
           py::return_value_policy::reference_internal)

      .def("GetObjectRotationValue", &G4VPhysicalVolume::GetObjectRotationValue)
      .def("GetFrameRotation", &G4VPhysicalVolume::GetFrameRotation, py::return_value_policy::reference_internal)

      .def("SetLogicalVolume", &G4VPhysicalVolume::SetLogicalVolume)
      .def("SetMotherLogical", &G4VPhysicalVolume::SetMotherLogical)
      .def("GetLogicalVolume", &G4VPhysicalVolume::GetLogicalVolume, py::return_value_policy::reference)
      .def("GetMotherLogical", &G4VPhysicalVolume::GetMotherLogical, py::return_value_policy::reference)

      .def("SetName", &G4VPhysicalVolume::SetName)
      .def("GetName", &G4VPhysicalVolume::GetName)
      .def("SetCopyNo", &G4VPhysicalVolume::SetCopyNo)
      .def("GetCopyNo", &G4VPhysicalVolume::GetCopyNo)

      .def("IsMany", &G4VPhysicalVolume::IsMany)
      .def("IsReplicated", &G4VPhysicalVolume::IsReplicated)
      .def("IsParameterised", &G4VPhysicalVolume::IsParameterised)
      .def("GetMultiplicity", &G4VPhysicalVolume::GetMultiplicity)
      .def("GetParameterisation", &G4VPhysicalVolume::GetParameterisation, py::return_value_policy::reference);
}
