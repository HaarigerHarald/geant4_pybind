#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VPhysicalVolume.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4LogicalVolume.hh>
#include <G4VPVParameterisation.hh>

#include "typecast.hh"
#include "opaques.hh"

#include "pyG4VPhysicalVolume.hh"

namespace py = pybind11;

class PyG4VPhysicalVolume : public G4VPhysicalVolume,
                            public py::trampoline_self_life_support,
                            public SharedPhysicalVolumeRotation {
public:
   using G4VPhysicalVolume::G4VPhysicalVolume;

   EVolume VolumeType() const override { PYBIND11_OVERRIDE_PURE(EVolume, G4VPhysicalVolume, VolumeType, ); }

   G4bool IsMany() const override { PYBIND11_OVERRIDE_PURE(G4bool, G4VPhysicalVolume, IsMany, ); }

   G4int GetCopyNo() const override { PYBIND11_OVERRIDE_PURE(G4int, G4VPhysicalVolume, GetCopyNo, ); }

   void SetCopyNo(G4int CopyNo) override { PYBIND11_OVERRIDE_PURE(void, G4VPhysicalVolume, SetCopyNo, CopyNo); }

   G4bool IsReplicated() const override { PYBIND11_OVERRIDE_PURE(G4bool, G4VPhysicalVolume, IsReplicated, ); }

   G4bool IsParameterised() const override { PYBIND11_OVERRIDE_PURE(G4bool, G4VPhysicalVolume, IsParameterised, ); }

   G4VPVParameterisation *GetParameterisation() const override
   {
      PYBIND11_OVERRIDE_PURE(G4VPVParameterisation *, G4VPhysicalVolume, GetParameterisation, );
   }

   void GetReplicationData(EAxis &axis, G4int &nReplicas, G4double &width, G4double &offset,
                           G4bool &consuming) const override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VPhysicalVolume, GetReplicationData, axis, nReplicas, width, offset, consuming);
   }

   G4bool IsRegularStructure() const override
   {
      PYBIND11_OVERRIDE_PURE(G4bool, G4VPhysicalVolume, IsRegularStructure, );
   }

   G4int GetRegularStructureId() const override
   {
      PYBIND11_OVERRIDE_PURE(G4int, G4VPhysicalVolume, GetRegularStructureId, );
   }

   G4int GetMultiplicity() const override { PYBIND11_OVERRIDE(G4int, G4VPhysicalVolume, GetMultiplicity, ); }

   G4bool CheckOverlaps(G4int res, G4double tol, G4bool verbose, G4int errMax) override
   {
      PYBIND11_OVERRIDE(G4bool, G4VPhysicalVolume, CheckOverlaps, res, tol, verbose, errMax);
   }
};

void export_G4VPhysicalVolume(py::module &m)
{
   py::class_<G4PVData>(m, "G4PVData")

      .def(py::init<>())
      .def("__copy__", [](const G4PVData &self) { return G4PVData(self); })
      .def("__deepcopy__", [](const G4PVData &self, py::dict) { return G4PVData(self); })
      .def("initialize", &G4PVData::initialize)
      .def_readwrite("frot", &G4PVData::frot)
      .def_readwrite("tx", &G4PVData::tx)
      .def_readwrite("ty", &G4PVData::ty)
      .def_readwrite("tz", &G4PVData::tz);

   py::class_<G4VPhysicalVolume, PyG4VPhysicalVolume, py::nodelete>(m, "G4VPhysicalVolume")

      .def(py::init<>([](std::shared_ptr<G4RotationMatrix> pRot, const G4ThreeVector &tlate, const G4String &pName,
                         G4LogicalVolume *pLogical, G4VPhysicalVolume *pMother) {
              PyG4VPhysicalVolume *physicalVolume =
                 new PyG4VPhysicalVolume(pRot.get(), tlate, pName, pLogical, pMother);
              physicalVolume->sharedRotation = pRot;
              return physicalVolume;
           }),
           py::arg("pRot"), py::arg("tlate"), py::arg("pName"), py::arg("pLogical"), py::arg("pMother"))

      .def("GetObjectRotation", &G4VPhysicalVolume::GetObjectRotation, py::return_value_policy::reference)
      .def("GetObjectRotationValue", &G4VPhysicalVolume::GetObjectRotationValue)
      .def("GetObjectTranslation", &G4VPhysicalVolume::GetObjectTranslation)
      .def("GetFrameRotation", &G4VPhysicalVolume::GetFrameRotation, py::return_value_policy::reference)
      .def("GetFrameTranslation", &G4VPhysicalVolume::GetFrameTranslation)
      .def("GetTranslation", &G4VPhysicalVolume::GetTranslation)
      .def("GetRotation", py::overload_cast<>(&G4VPhysicalVolume::GetRotation, py::const_),
           py::return_value_policy::reference)

      .def("SetTranslation", &G4VPhysicalVolume::SetTranslation, py::arg("v"))
      .def("GetRotation", py::overload_cast<>(&G4VPhysicalVolume::GetRotation), py::return_value_policy::reference)
      .def("SetRotation",
           [](G4VPhysicalVolume &self, std::shared_ptr<G4RotationMatrix> rotation) {
              SharedPhysicalVolumeRotation *sharedRotation = dynamic_cast<SharedPhysicalVolumeRotation *>(&self);

              if (sharedRotation != nullptr) {
                 sharedRotation->sharedRotation = rotation;
              }

              self.SetRotation(rotation.get());
           })

      .def("GetLogicalVolume", &G4VPhysicalVolume::GetLogicalVolume, py::return_value_policy::reference)
      .def("SetLogicalVolume", &G4VPhysicalVolume::SetLogicalVolume, py::arg("pLogical"))
      .def("GetMotherLogical", &G4VPhysicalVolume::GetMotherLogical, py::return_value_policy::reference)
      .def("SetMotherLogical", &G4VPhysicalVolume::SetMotherLogical, py::arg("pMother"))
      .def("GetName", &G4VPhysicalVolume::GetName)
      .def("SetName", &G4VPhysicalVolume::SetName, py::arg("pName"))
      .def("GetMultiplicity", &G4VPhysicalVolume::GetMultiplicity)
      .def("VolumeType", &G4VPhysicalVolume::VolumeType)
      .def("IsMany", &G4VPhysicalVolume::IsMany)
      .def("GetCopyNo", &G4VPhysicalVolume::GetCopyNo)
      .def("SetCopyNo", &G4VPhysicalVolume::SetCopyNo, py::arg("CopyNo"))
      .def("IsReplicated", &G4VPhysicalVolume::IsReplicated)
      .def("IsParameterised", &G4VPhysicalVolume::IsParameterised)
      .def("GetParameterisation", &G4VPhysicalVolume::GetParameterisation, py::return_value_policy::reference)
      .def("GetReplicationData", &G4VPhysicalVolume::GetReplicationData, py::arg("axis"), py::arg("nReplicas"),
           py::arg("width"), py::arg("offset"), py::arg("consuming"))

      .def("IsRegularStructure", &G4VPhysicalVolume::IsRegularStructure)
      .def("GetRegularStructureId", &G4VPhysicalVolume::GetRegularStructureId)
      .def("CheckOverlaps", &G4VPhysicalVolume::CheckOverlaps, py::arg("res") = 1000, py::arg("tol") = 0.,
           py::arg("verbose") = true, py::arg("errMax") = 1)

      .def("GetInstanceID", &G4VPhysicalVolume::GetInstanceID)
      .def_static("GetSubInstanceManager", &G4VPhysicalVolume::GetSubInstanceManager)
      .def_static("Clean", &G4VPhysicalVolume::Clean)
      .def("DeduceVolumeType", &G4VPhysicalVolume::DeduceVolumeType);
}
