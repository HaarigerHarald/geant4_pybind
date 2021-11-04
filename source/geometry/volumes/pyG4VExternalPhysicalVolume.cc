#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VExternalPhysicalVolume.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4LogicalVolume.hh>
#include <G4VPVParameterisation.hh>

#include "typecast.hh"
#include "opaques.hh"

#include "../management/pyG4VPhysicalVolume.hh"

namespace py = pybind11;

class PyG4VExternalPhysicalVolume : public G4VExternalPhysicalVolume,
                                    public py::trampoline_self_life_support,
                                    public SharedPhysicalVolumeRotation {
public:
   using G4VExternalPhysicalVolume::G4VExternalPhysicalVolume;

   G4int GetCopyNo() const override { PYBIND11_OVERRIDE_PURE(G4int, G4VExternalPhysicalVolume, GetCopyNo, ); }

   void SetCopyNo(G4int CopyNo) override { PYBIND11_OVERRIDE_PURE(void, G4VExternalPhysicalVolume, SetCopyNo, CopyNo); }

   G4int GetMultiplicity() const override { PYBIND11_OVERRIDE(G4int, G4VExternalPhysicalVolume, GetMultiplicity, ); }

   G4bool CheckOverlaps(G4int res, G4double tol, G4bool verbose, G4int errMax) override
   {
      PYBIND11_OVERRIDE_PURE(G4bool, G4VExternalPhysicalVolume, CheckOverlaps, res, tol, verbose, errMax);
   }
};

void export_G4VExternalPhysicalVolume(py::module &m)
{
   py::class_<G4VExternalPhysicalVolume, PyG4VExternalPhysicalVolume, G4VPhysicalVolume, py::nodelete>(
      m, "G4VExternalPhysicalVolume")

      .def(py::init<>([](std::shared_ptr<G4RotationMatrix> pRot, const G4ThreeVector &tlate,
                         G4LogicalVolume *pCurrentLogical, const G4String &pName, G4VPhysicalVolume *pMother) {
              auto *physicalVolume =
                 new PyG4VExternalPhysicalVolume(pRot.get(), tlate, pCurrentLogical, pName, pMother);
              physicalVolume->sharedRotation = pRot;
              return physicalVolume;
           }),
           py::arg("pRot"), py::arg("tlate"), py::arg("pCurrentLogical"), py::arg("pName"), py::arg("pMother"))

      .def("CheckOverlaps", &G4VExternalPhysicalVolume::CheckOverlaps, py::arg("res") = 1000, py::arg("tol") = 0.,
           py::arg("verbose") = true, py::arg("maxErr") = 1)

      .def("VolumeType", &G4VExternalPhysicalVolume::VolumeType)
      .def("IsMany", &G4VExternalPhysicalVolume::IsMany)
      .def("IsReplicated", &G4VExternalPhysicalVolume::IsReplicated)
      .def("IsParameterised", &G4VExternalPhysicalVolume::IsParameterised)
      .def("GetParameterisation", &G4VExternalPhysicalVolume::GetParameterisation, py::return_value_policy::reference)
      .def("GetReplicationData", &G4VExternalPhysicalVolume::GetReplicationData, py::arg("axis"), py::arg("nReplicas"),
           py::arg("width"), py::arg("offset"), py::arg("consuming"))

      .def("IsRegularStructure", &G4VExternalPhysicalVolume::IsRegularStructure)
      .def("GetRegularStructureId", &G4VExternalPhysicalVolume::GetRegularStructureId)
      .def("SetMany", &G4VExternalPhysicalVolume::SetMany, py::arg("overlap"));
}
