#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4PVParameterised.hh>
#include <G4LogicalVolume.hh>
#include <G4VPVParameterisation.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4PVParameterised(py::module &m)
{
   py::class_<G4PVParameterised, G4PVReplica, std::unique_ptr<G4PVParameterised, py::nodelete>>(m, "G4PVParameterised")

      .def(py::init<const G4String &, G4LogicalVolume *, G4LogicalVolume *, const EAxis, const G4int,
                    G4VPVParameterisation *, G4bool>(),
           py::arg("pName"), py::arg("pLogical"), py::arg("pMotherLogical"), py::arg("pAxis"), py::arg("nReplicas"),
           py::arg("pParam"), py::arg("pSurfChk") = false, py::keep_alive<1, 3>(), py::keep_alive<4, 1>(),
           py::keep_alive<1, 7>())

      .def(py::init<const G4String &, G4LogicalVolume *, G4VPhysicalVolume *, const EAxis, const G4int,
                    G4VPVParameterisation *, G4bool>(),
           py::arg("pName"), py::arg("pLogical"), py::arg("pMother"), py::arg("pAxis"), py::arg("nReplicas"),
           py::arg("pParam"), py::arg("pSurfChk") = false, py::keep_alive<1, 3>(), py::keep_alive<4, 1>(),
           py::keep_alive<1, 7>())

      .def("IsParameterised", &G4PVParameterised::IsParameterised)
      .def("VolumeType", &G4PVParameterised::VolumeType)
      .def("GetParameterisation", &G4PVParameterised::GetParameterisation, py::return_value_policy::reference_internal)
      //.def("GetReplicationData", &G4PVParameterised::GetReplicationData)
      .def("SetRegularStructureId", &G4PVParameterised::SetRegularStructureId)
      .def("CheckOverlaps", &G4PVParameterised::CheckOverlaps, py::arg("res") = 1000, py::arg("tol") = 0.,
           py::arg("verbose") = true, py::arg("maxErr") = 1);
}
