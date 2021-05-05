#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4FastSimulationManager.hh>
#include <G4LogicalVolume.hh>
#include <G4MaterialCutsCouple.hh>
#include <G4ProductionCuts.hh>
#include <G4Region.hh>
#include <G4UserLimits.hh>
#include <G4VUserRegionInformation.hh>

#include "holder.hh"
#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Region(py::module &m)
{
   py::class_<G4Region, std::unique_ptr<G4Region, py::nodelete>>(m, "G4Region", "region class")

      .def(py::init<const G4String &>())

      .def("AddRootLogicalVolume", &G4Region::AddRootLogicalVolume)
      .def("RemoveRootLogicalVolume", &G4Region::RemoveRootLogicalVolume)
      .def("SetName", &G4Region::SetName)
      .def("GetName", &G4Region::GetName)
      .def("RegionModified", &G4Region::RegionModified)
      .def("IsModified", &G4Region::IsModified)
      .def("SetProductionCuts", &G4Region::SetProductionCuts)
      .def("GetProductionCuts", &G4Region::GetProductionCuts, py::return_value_policy::reference_internal)
      .def("GetNumberOfMaterials", &G4Region::GetNumberOfMaterials)
      .def("GetNumberOfRootVolumes", &G4Region::GetNumberOfRootVolumes)
      .def("UpdateMaterialList", &G4Region::UpdateMaterialList)
      .def("ClearMaterialList", &G4Region::ClearMaterialList)
      .def("ScanVolumeTree", &G4Region::ScanVolumeTree)
      .def("SetUserInformation",
           [](G4Region &self, G4VUserRegionInformation *userInfo) {
              owntrans_ptr<G4VUserRegionInformation>::remove(userInfo);
              // TODO increase ref
              self.SetUserInformation(userInfo);
           })
      .def("GetUserInformation", &G4Region::GetUserInformation, py::return_value_policy::reference_internal)
      .def("SetUserLimits", &G4Region::SetUserLimits, py::keep_alive<1, 2>())
      .def("GetUserLimits", &G4Region::GetUserLimits, py::return_value_policy::reference_internal)
      .def("ClearMap", &G4Region::ClearMap)
      .def("RegisterMaterialCouplePair", &G4Region::RegisterMaterialCouplePair)
      .def("FindCouple", &G4Region::FindCouple, py::return_value_policy::reference)
      .def("SetFastSimulationManager", &G4Region::SetFastSimulationManager)
      .def("GetFastSimulationManager", &G4Region::GetFastSimulationManager, py::return_value_policy::reference_internal)
      .def("ClearFastSimulationManager", &G4Region::ClearFastSimulationManager)
      .def("GetWorldPhysical", &G4Region::GetWorldPhysical, py::return_value_policy::reference_internal)
      .def("SetWorld", &G4Region::SetWorld)
      .def("BelongsTo", &G4Region::BelongsTo)
      .def("GetParentRegion", &G4Region::GetParentRegion, py::return_value_policy::reference);
}
