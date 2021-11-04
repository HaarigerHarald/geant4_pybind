#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4LogicalVolume.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4ProductionCuts.hh>
#include <G4Material.hh>
#include <G4VUserRegionInformation.hh>
#include <G4MaterialCutsCouple.hh>
#include <G4UserLimits.hh>
#include <G4FieldManager.hh>
#include <G4FastSimulationManager.hh>
#include <G4UserSteppingAction.hh>
#include <G4VPVParameterisation.hh>
#include <G4VSensitiveDetector.hh>
#include <G4VSolid.hh>
#include <G4SmartVoxelHeader.hh>
#include <G4VisAttributes.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4LogicalVolume : public G4LogicalVolume, public py::trampoline_self_life_support {
public:
   using G4LogicalVolume::G4LogicalVolume;

   G4bool IsExtended() const override { PYBIND11_OVERRIDE(G4bool, G4LogicalVolume, IsExtended, ); }
};

void export_G4LogicalVolume(py::module &m)
{
   py::class_<G4LVData>(m, "G4LVData")

      .def(py::init<>())
      .def("__copy__", [](const G4LVData &self) { return G4LVData(self); })
      .def("__deepcopy__", [](const G4LVData &self, py::dict) { return G4LVData(self); })
      .def("initialize", &G4LVData::initialize)
      .def_readwrite("fSolid", &G4LVData::fSolid)
      .def_readwrite("fSensitiveDetector", &G4LVData::fSensitiveDetector)
      .def_readwrite("fFieldManager", &G4LVData::fFieldManager)
      .def_readwrite("fMaterial", &G4LVData::fMaterial)
      .def_readwrite("fMass", &G4LVData::fMass)
      .def_readwrite("fCutsCouple", &G4LVData::fCutsCouple);

   py::class_<G4LogicalVolume, PyG4LogicalVolume, py::nodelete>(m, "G4LogicalVolume")

      .def(py::init_alias<G4VSolid *, G4Material *, const G4String &, G4FieldManager *, G4VSensitiveDetector *,
                          G4UserLimits *, G4bool>(),
           py::arg("pSolid"), py::arg("pMaterial"), py::arg("name"),
           py::arg("pFieldMgr")  = static_cast<G4FieldManager *>(nullptr),
           py::arg("pSDetector") = static_cast<G4VSensitiveDetector *>(nullptr),
           py::arg("pULimits") = static_cast<G4UserLimits *>(nullptr), py::arg("optimise") = true,
           py::keep_alive<1, 5>(), py::keep_alive<1, 6>(), py::keep_alive<1, 7>())

      .def("GetName", &G4LogicalVolume::GetName)
      .def("SetName", &G4LogicalVolume::SetName, py::arg("pName"))
      .def("GetNoDaughters", &G4LogicalVolume::GetNoDaughters)
      .def("GetDaughter", &G4LogicalVolume::GetDaughter, py::arg("i"), py::return_value_policy::reference)
      .def("AddDaughter", &G4LogicalVolume::AddDaughter, py::arg("p"))
      .def("IsDaughter", &G4LogicalVolume::IsDaughter, py::arg("p"))
      .def("IsAncestor", &G4LogicalVolume::IsAncestor, py::arg("p"))
      .def("RemoveDaughter", &G4LogicalVolume::RemoveDaughter, py::arg("p"))
      .def("ClearDaughters", &G4LogicalVolume::ClearDaughters)
      .def("TotalVolumeEntities", &G4LogicalVolume::TotalVolumeEntities)
      .def("CharacteriseDaughters", &G4LogicalVolume::CharacteriseDaughters)
      .def("DeduceDaughtersType", &G4LogicalVolume::DeduceDaughtersType)
      .def("GetSolid", py::overload_cast<>(&G4LogicalVolume::GetSolid, py::const_), py::return_value_policy::reference)
      .def("SetSolid", py::overload_cast<G4VSolid *>(&G4LogicalVolume::SetSolid), py::arg("pSolid"))
      .def("GetMaterial", &G4LogicalVolume::GetMaterial, py::return_value_policy::reference)
      .def("SetMaterial", &G4LogicalVolume::SetMaterial, py::arg("pMaterial"))
      .def("UpdateMaterial", &G4LogicalVolume::UpdateMaterial, py::arg("pMaterial"))
      .def("GetMass", &G4LogicalVolume::GetMass, py::arg("forced") = false, py::arg("propagate") = true,
           py::arg("parMaterial") = static_cast<G4Material *>(nullptr))

      .def("ResetMass", &G4LogicalVolume::ResetMass)
      .def("GetFieldManager", &G4LogicalVolume::GetFieldManager, py::return_value_policy::reference)
      .def("SetFieldManager", &G4LogicalVolume::SetFieldManager, py::arg("pFieldMgr"), py::arg("forceToAllDaughters"),
           py::keep_alive<1, 2>())

      .def("GetSensitiveDetector", &G4LogicalVolume::GetSensitiveDetector, py::return_value_policy::reference)
      .def("SetSensitiveDetector", &G4LogicalVolume::SetSensitiveDetector, py::arg("pSDetector"),
           py::keep_alive<1, 2>())

      .def("GetUserLimits", &G4LogicalVolume::GetUserLimits, py::return_value_policy::reference)
      .def("SetUserLimits", &G4LogicalVolume::SetUserLimits, py::arg("pULimits"), py::keep_alive<1, 2>())
      .def("GetVoxelHeader", &G4LogicalVolume::GetVoxelHeader, py::return_value_policy::reference)
      .def("SetVoxelHeader", &G4LogicalVolume::SetVoxelHeader, py::arg("pVoxel"))
      .def("GetSmartless", &G4LogicalVolume::GetSmartless)
      .def("SetSmartless", &G4LogicalVolume::SetSmartless, py::arg("s"))
      .def("IsToOptimise", &G4LogicalVolume::IsToOptimise)
      .def("SetOptimisation", &G4LogicalVolume::SetOptimisation, py::arg("optim"))
      .def("IsRootRegion", &G4LogicalVolume::IsRootRegion)
      .def("SetRegionRootFlag", &G4LogicalVolume::SetRegionRootFlag, py::arg("rreg"))
      .def("IsRegion", &G4LogicalVolume::IsRegion)
      .def("SetRegion", &G4LogicalVolume::SetRegion, py::arg("reg"))
      .def("GetRegion", &G4LogicalVolume::GetRegion, py::return_value_policy::reference)
      .def("PropagateRegion", &G4LogicalVolume::PropagateRegion)
      .def("GetMaterialCutsCouple", &G4LogicalVolume::GetMaterialCutsCouple, py::return_value_policy::reference)
      .def("SetMaterialCutsCouple", &G4LogicalVolume::SetMaterialCutsCouple, py::arg("cuts"))
      .def(py::self == py::self)
      .def("GetVisAttributes", &G4LogicalVolume::GetVisAttributes, py::return_value_policy::reference)
      .def("SetVisAttributes", py::overload_cast<const G4VisAttributes *>(&G4LogicalVolume::SetVisAttributes),
           py::arg("pVA"))

      .def("SetVisAttributes", py::overload_cast<const G4VisAttributes &>(&G4LogicalVolume::SetVisAttributes),
           py::arg("VA"))

      .def("GetFastSimulationManager", &G4LogicalVolume::GetFastSimulationManager, py::return_value_policy::reference)
      .def("SetBiasWeight", &G4LogicalVolume::SetBiasWeight, py::arg("w"))
      .def("GetBiasWeight", &G4LogicalVolume::GetBiasWeight)
      .def("IsExtended", &G4LogicalVolume::IsExtended)
      .def("GetMasterFieldManager", &G4LogicalVolume::GetMasterFieldManager, py::return_value_policy::reference)
      .def("GetMasterSensitiveDetector", &G4LogicalVolume::GetMasterSensitiveDetector,
           py::return_value_policy::reference)

      .def("GetMasterSolid", &G4LogicalVolume::GetMasterSolid, py::return_value_policy::reference)
      .def("GetInstanceID", &G4LogicalVolume::GetInstanceID)
      .def_static("GetSubInstanceManager", &G4LogicalVolume::GetSubInstanceManager)
      .def_static("Clean", &G4LogicalVolume::Clean)
      .def("Lock", &G4LogicalVolume::Lock)
      .def("InitialiseWorker", &G4LogicalVolume::InitialiseWorker, py::arg("ptrMasterObject"), py::arg("pSolid"),
           py::arg("pSDetector"))

      .def("TerminateWorker", &G4LogicalVolume::TerminateWorker, py::arg("ptrMasterObject"))
      .def("AssignFieldManager", &G4LogicalVolume::AssignFieldManager, py::arg("fldMgr"), py::keep_alive<1, 2>())
      .def_static("GetSolid_", py::overload_cast<G4LVData &>(&G4LogicalVolume::GetSolid), py::arg("instLVdata"),
                  py::return_value_policy::reference)

      .def_static("SetSolid_", py::overload_cast<G4LVData &, G4VSolid *>(&G4LogicalVolume::SetSolid),
                  py::arg("instLVdata"), py::arg("pSolid"))

      .def("ChangeDaughtersType", &G4LogicalVolume::ChangeDaughtersType, py::arg("atype"));
}
