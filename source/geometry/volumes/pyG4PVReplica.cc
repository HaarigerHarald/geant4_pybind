#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4PVReplica.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4LogicalVolume.hh>
#include <G4VPVParameterisation.hh>

#include "typecast.hh"
#include "opaques.hh"

#include "../management/pyG4VPhysicalVolume.hh"

namespace py = pybind11;

class G4PVReplicaRotationShared : public G4PVReplica, public SharedPhysicalVolumeRotation {
public:
   using G4PVReplica::G4PVReplica;
};

class PyG4PVReplica : public G4PVReplica, public py::trampoline_self_life_support, public SharedPhysicalVolumeRotation {
public:
   using G4PVReplica::G4PVReplica;

   EVolume VolumeType() const override { PYBIND11_OVERRIDE(EVolume, G4PVReplica, VolumeType, ); }

   G4bool IsMany() const override { PYBIND11_OVERRIDE(G4bool, G4PVReplica, IsMany, ); }

   G4bool IsReplicated() const override { PYBIND11_OVERRIDE(G4bool, G4PVReplica, IsReplicated, ); }

   G4int GetCopyNo() const override { PYBIND11_OVERRIDE(G4int, G4PVReplica, GetCopyNo, ); }

   void SetCopyNo(G4int CopyNo) override { PYBIND11_OVERRIDE(void, G4PVReplica, SetCopyNo, CopyNo); }

   G4bool IsParameterised() const override { PYBIND11_OVERRIDE(G4bool, G4PVReplica, IsParameterised, ); }

   G4VPVParameterisation *GetParameterisation() const override
   {
      PYBIND11_OVERRIDE(G4VPVParameterisation *, G4PVReplica, GetParameterisation, );
   }

   G4int GetMultiplicity() const override { PYBIND11_OVERRIDE(G4int, G4PVReplica, GetMultiplicity, ); }

   void GetReplicationData(EAxis &axis, G4int &nReplicas, G4double &width, G4double &offset,
                           G4bool &consuming) const override
   {
      PYBIND11_OVERRIDE(void, G4PVReplica, GetReplicationData, axis, nReplicas, width, offset, consuming);
   }

   void SetRegularStructureId(G4int code) override
   {
      PYBIND11_OVERRIDE(void, G4PVReplica, SetRegularStructureId, code);
   }

   G4bool IsRegularStructure() const override { PYBIND11_OVERRIDE(G4bool, G4PVReplica, IsRegularStructure, ); }

   G4int GetRegularStructureId() const override { PYBIND11_OVERRIDE(G4int, G4PVReplica, GetRegularStructureId, ); }

   G4bool CheckOverlaps(G4int res, G4double tol, G4bool verbose, G4int errMax) override
   {
      PYBIND11_OVERRIDE(G4bool, G4PVReplica, CheckOverlaps, res, tol, verbose, errMax);
   }
};

void export_G4PVReplica(py::module &m)
{
   py::class_<G4ReplicaData>(m, "G4ReplicaData")

      .def(py::init<>())
      .def("__copy__", [](const G4ReplicaData &self) { return G4ReplicaData(self); })
      .def("__deepcopy__", [](const G4ReplicaData &self, py::dict) { return G4ReplicaData(self); })
      .def("initialize", &G4ReplicaData::initialize)
      .def_readwrite("fcopyNo", &G4ReplicaData::fcopyNo);

   py::class_<G4PVReplica, PyG4PVReplica, G4VPhysicalVolume, py::nodelete>(m, "G4PVReplica")

      .def(py::init<>(
              [](const G4String &pName, G4LogicalVolume *pLogical, G4LogicalVolume *pMother, const EAxis pAxis,
                 const G4int nReplicas, const G4double width, const G4double offset = 0.) {
                 return new G4PVReplicaRotationShared(pName, pLogical, pMother, pAxis, nReplicas, width, offset);
              },
              [](const G4String &pName, G4LogicalVolume *pLogical, G4LogicalVolume *pMother, const EAxis pAxis,
                 const G4int nReplicas, const G4double width, const G4double offset = 0.) {
                 return new PyG4PVReplica(pName, pLogical, pMother, pAxis, nReplicas, width, offset);
              }),
           py::arg("pName"), py::arg("pLogical"), py::arg("pMother"), py::arg("pAxis"), py::arg("nReplicas"),
           py::arg("width"), py::arg("offset") = 0.)

      .def("VolumeType", &G4PVReplica::VolumeType)
      .def("IsMany", &G4PVReplica::IsMany)
      .def("IsReplicated", &G4PVReplica::IsReplicated)
      .def("GetCopyNo", &G4PVReplica::GetCopyNo)
      .def("SetCopyNo", &G4PVReplica::SetCopyNo, py::arg("CopyNo"))
      .def("IsParameterised", &G4PVReplica::IsParameterised)
      .def("GetParameterisation", &G4PVReplica::GetParameterisation, py::return_value_policy::reference)
      .def("GetMultiplicity", &G4PVReplica::GetMultiplicity)
      .def("GetReplicationData", &G4PVReplica::GetReplicationData, py::arg("axis"), py::arg("nReplicas"),
           py::arg("width"), py::arg("offset"), py::arg("consuming"))

      .def("SetRegularStructureId", &G4PVReplica::SetRegularStructureId, py::arg("code"))
      .def("IsRegularStructure", &G4PVReplica::IsRegularStructure)
      .def("GetRegularStructureId", &G4PVReplica::GetRegularStructureId)
      .def("GetInstanceID", &G4PVReplica::GetInstanceID)
      .def_static("GetSubInstanceManager", &G4PVReplica::GetSubInstanceManager)
      .def("InitialiseWorker", &G4PVReplica::InitialiseWorker, py::arg("pMasterObject"))
      .def("TerminateWorker", &G4PVReplica::TerminateWorker, py::arg("pMasterObject"));
}
