#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4FastSimulationManager.hh>
#include <G4FieldManager.hh>
#include <G4LogicalVolume.hh>
#include <G4Material.hh>
#include <G4MaterialCutsCouple.hh>
#include <G4SmartVoxelHeader.hh>
#include <G4UserLimits.hh>
#include <G4VSensitiveDetector.hh>
#include <G4VSolid.hh>
#include <G4VisAttributes.hh>
#include <G4LogicalVolumeStore.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4LogicalVolume(py::module &m)
{
   py::class_<G4LogicalVolume, py::nodelete>(m, "G4LogicalVolume", "logical volume class")

      .def(py::init<G4VSolid *, G4Material *, const G4String &>(), py::keep_alive<1, 2>(), py::keep_alive<1, 3>())
      .def(py::init<G4VSolid *, G4Material *, const G4String &, G4FieldManager *>(), py::keep_alive<1, 2>(),
           py::keep_alive<1, 3>(), py::keep_alive<1, 5>())

      .def(py::init<G4VSolid *, G4Material *, const G4String &, G4FieldManager *, G4VSensitiveDetector *>(),
           py::keep_alive<1, 2>(), py::keep_alive<1, 3>(), py::keep_alive<1, 5>(), py::keep_alive<1, 6>())

      .def(py::init<G4VSolid *, G4Material *, const G4String &, G4FieldManager *, G4VSensitiveDetector *,
                    G4UserLimits *>(),
           py::keep_alive<1, 2>(), py::keep_alive<1, 3>(), py::keep_alive<1, 5>(), py::keep_alive<1, 6>(),
           py::keep_alive<1, 7>())

      .def(py::init<G4VSolid *, G4Material *, const G4String &, G4FieldManager *, G4VSensitiveDetector *,
                    G4UserLimits *, G4bool>(),
           py::keep_alive<1, 2>(), py::keep_alive<1, 3>(), py::keep_alive<1, 5>(), py::keep_alive<1, 6>(),
           py::keep_alive<1, 7>())

      .def("GetName", &G4LogicalVolume::GetName)
      .def("SetName", &G4LogicalVolume::SetName)

      .def("GetNoDaughters", &G4LogicalVolume::GetNoDaughters)
      .def("GetDaughter", &G4LogicalVolume::GetDaughter, py::return_value_policy::reference)
      .def("AddDaughter", &G4LogicalVolume::AddDaughter)
      .def("IsDaughter", &G4LogicalVolume::IsDaughter)
      .def("IsAncestor", &G4LogicalVolume::IsAncestor)
      .def("RemoveDaughter", &G4LogicalVolume::RemoveDaughter)
      .def("ClearDaughters", &G4LogicalVolume::ClearDaughters)
      .def("TotalVolumeEntities", &G4LogicalVolume::TotalVolumeEntities)

      .def("GetSolid", py::overload_cast<>(&G4LogicalVolume::GetSolid, py::const_), py::return_value_policy::reference)

      .def("SetSolid", py::overload_cast<G4VSolid *>(&G4LogicalVolume::SetSolid))
      .def("GetMaterial", &G4LogicalVolume::GetMaterial, py::return_value_policy::reference)
      .def("SetMaterial", &G4LogicalVolume::SetMaterial)
      .def("UpdateMaterial", &G4LogicalVolume::UpdateMaterial)

      .def("GetMass", &G4LogicalVolume::GetMass, py::arg("forced") = false, py::arg("propagate") = true,
           py::arg("parMaterial") = static_cast<G4Material *>(nullptr))

      .def("GetFieldManager", &G4LogicalVolume::GetFieldManager, py::return_value_policy::reference)
      .def("SetFieldManager", &G4LogicalVolume::SetFieldManager)
      .def("GetSensitiveDetector", &G4LogicalVolume::GetSensitiveDetector, py::return_value_policy::reference)
      .def("SetSensitiveDetector", &G4LogicalVolume::SetSensitiveDetector)

      .def("GetUserLimits", &G4LogicalVolume::GetUserLimits, py::return_value_policy::reference)
      .def("SetUserLimits", &G4LogicalVolume::SetUserLimits, py::keep_alive<1, 2>())

      .def("GetVoxelHeader", &G4LogicalVolume::GetVoxelHeader, py::return_value_policy::reference)
      .def("SetVoxelHeader", &G4LogicalVolume::SetVoxelHeader)
      .def("GetSmartless", &G4LogicalVolume::GetSmartless)
      .def("SetSmartless", &G4LogicalVolume::SetSmartless)
      .def("IsToOptimise", &G4LogicalVolume::IsToOptimise)
      .def("SetOptimisation", &G4LogicalVolume::SetOptimisation)

      .def("IsRootRegion", &G4LogicalVolume::IsRootRegion)
      .def("SetRegionRootFlag", &G4LogicalVolume::SetRegionRootFlag)
      .def("IsRegion", &G4LogicalVolume::IsRegion)
      .def("SetRegion", &G4LogicalVolume::SetRegion)
      .def("GetRegion", &G4LogicalVolume::GetRegion, py::return_value_policy::reference)
      .def("PropagateRegion", &G4LogicalVolume::PropagateRegion)
      .def("GetMaterialCutsCouple", &G4LogicalVolume::GetMaterialCutsCouple, py::return_value_policy::reference)

      .def("SetMaterialCutsCouple", &G4LogicalVolume::SetMaterialCutsCouple)

      .def("GetVisAttributes", &G4LogicalVolume::GetVisAttributes, py::return_value_policy::reference)
      .def("SetVisAttributes", py::overload_cast<const G4VisAttributes &>(&G4LogicalVolume::SetVisAttributes))

      .def("GetFastSimulationManager", &G4LogicalVolume::GetFastSimulationManager, py::return_value_policy::reference)

      .def("SetBiasWeight", &G4LogicalVolume::SetBiasWeight)
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
      .def("InitialiseWorker", &G4LogicalVolume::InitialiseWorker, py::keep_alive<1, 2>(), py::keep_alive<1, 3>(),
           py::keep_alive<1, 4>())

      .def("TerminateWorker", &G4LogicalVolume::TerminateWorker)
      .def("AssignFieldManager", &G4LogicalVolume::AssignFieldManager, py::keep_alive<1, 2>())

      //  .def_static("GetSolid", py::overload_cast<G4LVData &>(&G4LogicalVolume::GetSolid),
      //              py::return_value_policy::reference)

      //  .def_static("SetSolid", py::overload_cast<G4LVData &, G4VSolid *>(&G4LogicalVolume::SetSolid),
      //              py::keep_alive<1, 3>())

      .def("ChangeDaughtersType", &G4LogicalVolume::ChangeDaughtersType);

   py::class_<G4LogicalVolumeStore, py::nodelete>(m, "G4LogicalVolumeStore")
      .def_static("GetInstance", &G4LogicalVolumeStore::GetInstance, py::return_value_policy::reference)
      .def_static("Register", &G4LogicalVolumeStore::Register)
      .def_static("DeRegister", &G4LogicalVolumeStore::DeRegister)
      .def_static("SetNotifier", &G4LogicalVolumeStore::SetNotifier)
      .def_static("Clean", &G4LogicalVolumeStore::Clean)
      .def("GetVolume", &G4LogicalVolumeStore::GetVolume, py::arg("name"), py::arg("verbose") = true,
           py::return_value_policy::reference);
}
