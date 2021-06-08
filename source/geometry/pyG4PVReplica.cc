#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4LogicalVolume.hh>
#include <G4PVReplica.hh>
#include <G4VPVParameterisation.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4PVReplica(py::module &m)
{
   py::class_<G4PVReplica, G4VPhysicalVolume, py::nodelete>(m, "G4PVReplica",
                                                            "physical volume placement with replication")

      .def(py::init<const G4String &, G4LogicalVolume *, G4LogicalVolume *, const EAxis, const G4int, const G4double>())

      .def(py::init<const G4String &, G4LogicalVolume *, G4LogicalVolume *, const EAxis, const G4int, const G4double,
                    const G4double>())

      .def(
         py::init<const G4String &, G4LogicalVolume *, G4VPhysicalVolume *, const EAxis, const G4int, const G4double>())

      .def(py::init<const G4String &, G4LogicalVolume *, G4VPhysicalVolume *, const EAxis, const G4int, const G4double,
                    const G4double>())

      .def("IsMany", &G4PVReplica::IsMany)
      .def("IsReplicated", &G4PVReplica::IsReplicated)
      .def("GetCopyNo", &G4PVReplica::GetCopyNo)
      .def("IsParameterised", &G4PVReplica::IsParameterised)
      .def("GetParameterisation", &G4PVReplica::GetParameterisation)
      .def("GetMultiplicity", &G4PVReplica::GetMultiplicity)

      //.def("GetReplicationData", &G4PVReplica::GetReplicationData)
      .def("SetRegularStructureId", &G4PVReplica::SetRegularStructureId)
      .def("IsRegularStructure", &G4PVReplica::IsRegularStructure)
      .def("GetRegularStructureId", &G4PVReplica::GetRegularStructureId)
      .def("GetInstanceID", &G4PVReplica::GetInstanceID)
      .def_static("GetSubInstanceManager", &G4PVReplica::GetSubInstanceManager)
      .def("InitialiseWorker", &G4PVReplica::InitialiseWorker)
      .def("TerminateWorker", &G4PVReplica::TerminateWorker);
}
