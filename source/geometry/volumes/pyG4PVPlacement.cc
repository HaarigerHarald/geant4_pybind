#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4PVPlacement.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4LogicalVolume.hh>
#include <G4VPVParameterisation.hh>

#include "typecast.hh"
#include "opaques.hh"

#include "../management/pyG4VPhysicalVolume.hh"

namespace py = pybind11;

class RotationSharedG4PVPlacement : public G4PVPlacement, public SharedPhysicalVolumeRotation {
public:
   using G4PVPlacement::G4PVPlacement;

   RotationSharedG4PVPlacement(std::shared_ptr<G4RotationMatrix> pRot, const G4ThreeVector &tlate,
                               G4LogicalVolume *pCurrentLogical, const G4String &pName, G4LogicalVolume *pMotherLogical,
                               G4bool pMany, G4int pCopyNo, G4bool pSurfChk = false)
      : G4PVPlacement(pRot.get(), tlate, pCurrentLogical, pName, pMotherLogical, pMany, pCopyNo, pSurfChk),
        SharedPhysicalVolumeRotation({pRot})

   {
   }

   RotationSharedG4PVPlacement(std::shared_ptr<G4RotationMatrix> pRot, const G4ThreeVector &tlate,
                               const G4String &pName, G4LogicalVolume *pLogical, G4VPhysicalVolume *pMother,
                               G4bool pMany, G4int pCopyNo, G4bool pSurfChk = false)
      : G4PVPlacement(pRot.get(), tlate, pName, pLogical, pMother, pMany, pCopyNo, pSurfChk),
        SharedPhysicalVolumeRotation({pRot})

   {
   }
};

class PyG4PVPlacement : public RotationSharedG4PVPlacement, public py::trampoline_self_life_support {
public:
   using RotationSharedG4PVPlacement::RotationSharedG4PVPlacement;

   G4int GetCopyNo() const override { PYBIND11_OVERRIDE(G4int, G4PVPlacement, GetCopyNo, ); }

   void SetCopyNo(G4int CopyNo) override { PYBIND11_OVERRIDE(void, G4PVPlacement, SetCopyNo, CopyNo); }

   G4bool CheckOverlaps(G4int res, G4double tol, G4bool verbose, G4int maxErr) override
   {
      PYBIND11_OVERRIDE(G4bool, G4PVPlacement, CheckOverlaps, res, tol, verbose, maxErr);
   }

   G4bool IsMany() const override { PYBIND11_OVERRIDE(G4bool, G4PVPlacement, IsMany, ); }

   G4bool IsReplicated() const override { PYBIND11_OVERRIDE(G4bool, G4PVPlacement, IsReplicated, ); }

   G4bool IsParameterised() const override { PYBIND11_OVERRIDE(G4bool, G4PVPlacement, IsParameterised, ); }

   G4VPVParameterisation *GetParameterisation() const override
   {
      PYBIND11_OVERRIDE(G4VPVParameterisation *, G4PVPlacement, GetParameterisation, );
   }

   void GetReplicationData(EAxis &axis, G4int &nReplicas, G4double &width, G4double &offset,
                           G4bool &consuming) const override
   {
      PYBIND11_OVERRIDE(void, G4PVPlacement, GetReplicationData, axis, nReplicas, width, offset, consuming);
   }

   G4bool IsRegularStructure() const override { PYBIND11_OVERRIDE(G4bool, G4PVPlacement, IsRegularStructure, ); }

   G4int GetRegularStructureId() const override { PYBIND11_OVERRIDE(G4int, G4PVPlacement, GetRegularStructureId, ); }

   EVolume VolumeType() const override { PYBIND11_OVERRIDE(EVolume, G4PVPlacement, VolumeType, ); }

   G4int GetMultiplicity() const override { PYBIND11_OVERRIDE(G4int, G4PVPlacement, GetMultiplicity, ); }
};

void export_G4PVPlacement(py::module &m)
{
   py::class_<RotationSharedG4PVPlacement, PyG4PVPlacement, G4VPhysicalVolume, py::nodelete>(m, "G4PVPlacement")

      .def(py::init<std::shared_ptr<G4RotationMatrix>, const G4ThreeVector &, G4LogicalVolume *, const G4String &,
                    G4LogicalVolume *, G4bool, G4int, G4bool>(),
           py::arg("pRot"), py::arg("tlate"), py::arg("pCurrentLogical"), py::arg("pName"), py::arg("pMotherLogical"),
           py::arg("pMany"), py::arg("pCopyNo"), py::arg("pSurfChk") = false)

      .def(py::init<const G4Transform3D &, G4LogicalVolume *, const G4String &, G4LogicalVolume *, G4bool, G4int,
                    G4bool>(),
           py::arg("Transform3D"), py::arg("pCurrentLogical"), py::arg("pName"), py::arg("pMotherLogical"),
           py::arg("pMany"), py::arg("pCopyNo"), py::arg("pSurfChk") = false)

      .def(py::init<std::shared_ptr<G4RotationMatrix>, const G4ThreeVector &, const G4String &, G4LogicalVolume *,
                    G4VPhysicalVolume *, G4bool, G4int, G4bool>(),
           py::arg("pRot"), py::arg("tlate"), py::arg("pName"), py::arg("pLogical"), py::arg("pMother"),
           py::arg("pMany"), py::arg("pCopyNo"), py::arg("pSurfChk") = false)

      .def(py::init<const G4Transform3D &, const G4String &, G4LogicalVolume *, G4VPhysicalVolume *, G4bool, G4int,
                    G4bool>(),
           py::arg("Transform3D"), py::arg("pName"), py::arg("pLogical"), py::arg("pMother"), py::arg("pMany"),
           py::arg("pCopyNo"), py::arg("pSurfChk") = false)

      .def("GetCopyNo", &G4PVPlacement::GetCopyNo)
      .def("SetCopyNo", &G4PVPlacement::SetCopyNo, py::arg("CopyNo"))
      .def("CheckOverlaps", &G4PVPlacement::CheckOverlaps, py::arg("res") = 1000, py::arg("tol") = 0.,
           py::arg("verbose") = true, py::arg("maxErr") = 1)

      .def("IsMany", &G4PVPlacement::IsMany)
      .def("IsReplicated", &G4PVPlacement::IsReplicated)
      .def("IsParameterised", &G4PVPlacement::IsParameterised)
      .def("GetParameterisation", &G4PVPlacement::GetParameterisation, py::return_value_policy::reference)
      .def("GetReplicationData", &G4PVPlacement::GetReplicationData, py::arg("axis"), py::arg("nReplicas"),
           py::arg("width"), py::arg("offset"), py::arg("consuming"))

      .def("IsRegularStructure", &G4PVPlacement::IsRegularStructure)
      .def("GetRegularStructureId", &G4PVPlacement::GetRegularStructureId)
      .def("VolumeType", &G4PVPlacement::VolumeType);
}
