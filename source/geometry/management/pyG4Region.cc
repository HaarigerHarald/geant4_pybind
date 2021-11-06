#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4Region.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4ProductionCuts.hh>
#include <G4LogicalVolume.hh>
#include <G4Material.hh>
#include <G4VUserRegionInformation.hh>
#include <G4MaterialCutsCouple.hh>
#include <G4UserLimits.hh>
#include <G4FieldManager.hh>
#include <G4FastSimulationManager.hh>
#include <G4VPhysicalVolume.hh>
#include <G4UserSteppingAction.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4Region : public G4Region, public py::trampoline_self_life_support {
public:
   using G4Region::G4Region;
};

void export_G4Region(py::module &m)
{
   py::class_<G4RegionData>(m, "G4RegionData")

      .def(py::init<>())
      .def("__copy__", [](const G4RegionData &self) { return G4RegionData(self); })
      .def("__deepcopy__", [](const G4RegionData &self, py::dict) { return G4RegionData(self); })
      .def("initialize", &G4RegionData::initialize)
      .def_readwrite("fFastSimulationManager", &G4RegionData::fFastSimulationManager)
      .def_readwrite("fRegionalSteppingAction", &G4RegionData::fRegionalSteppingAction);

   py::class_<G4Region, PyG4Region, py::nodelete>(m, "G4Region")

      .def(py::init_alias<const G4String &>(), py::arg("name"))
      .def(py::self == py::self)
      .def("AddRootLogicalVolume", &G4Region::AddRootLogicalVolume, py::arg("lv"), py::arg("search") = true)
      .def("RemoveRootLogicalVolume", &G4Region::RemoveRootLogicalVolume, py::arg("lv"), py::arg("scan") = true)
      .def("SetName", &G4Region::SetName, py::arg("name"))
      .def("GetName", &G4Region::GetName)
      .def("RegionModified", &G4Region::RegionModified, py::arg("flag"))
      .def("IsModified", &G4Region::IsModified)
      .def("SetProductionCuts", &G4Region::SetProductionCuts, py::arg("cut"))
      .def("GetProductionCuts", &G4Region::GetProductionCuts, py::return_value_policy::reference)
      .def(
         "GetRootLogicalVolumeIterator",
         [](G4Region &self) {
            auto begin = self.GetRootLogicalVolumeIterator();
            auto end   = begin + self.GetNumberOfRootVolumes();

            return py::make_iterator(begin, end);
         },
         py::keep_alive<0, 1>())

      .def(
         "GetMaterialIterator",
         [](G4Region &self) {
            auto begin = self.GetMaterialIterator();
            auto end   = begin + self.GetNumberOfMaterials();

            return py::make_iterator(begin, end);
         },
         py::keep_alive<0, 1>())

      .def("GetNumberOfMaterials", &G4Region::GetNumberOfMaterials)
      .def("GetNumberOfRootVolumes", &G4Region::GetNumberOfRootVolumes)
      .def("UpdateMaterialList", &G4Region::UpdateMaterialList)
      .def("ClearMaterialList", &G4Region::ClearMaterialList)
      .def("ScanVolumeTree", &G4Region::ScanVolumeTree, py::arg("lv"), py::arg("region"))
      .def(
         "SetUserInformation",
         [](G4Region &self, py::disown_ptr<G4VUserRegionInformation> userInfo) { self.SetUserInformation(userInfo); },
         py::arg("ui"))

      .def("GetUserInformation", &G4Region::GetUserInformation, py::return_value_policy::reference)
      .def("SetUserLimits", &G4Region::SetUserLimits, py::arg("ul"), py::keep_alive<1, 2>())
      .def("GetUserLimits", &G4Region::GetUserLimits, py::return_value_policy::reference)
      .def("ClearMap", &G4Region::ClearMap)
      .def("RegisterMaterialCouplePair", &G4Region::RegisterMaterialCouplePair, py::arg("mat"), py::arg("couple"))
      .def("FindCouple", &G4Region::FindCouple, py::arg("mat"), py::return_value_policy::reference)
      .def("SetFastSimulationManager", &G4Region::SetFastSimulationManager, py::arg("fsm"))
      .def("GetFastSimulationManager", &G4Region::GetFastSimulationManager, py::return_value_policy::reference)
      .def("ClearFastSimulationManager", &G4Region::ClearFastSimulationManager)
      .def("SetFieldManager", &G4Region::SetFieldManager, py::arg("fm"))
      .def("GetFieldManager", &G4Region::GetFieldManager, py::return_value_policy::reference)
      .def("GetWorldPhysical", &G4Region::GetWorldPhysical, py::return_value_policy::reference)
      .def("SetWorld", &G4Region::SetWorld, py::arg("wp"))
      .def("BelongsTo", &G4Region::BelongsTo, py::arg("thePhys"))
      .def("GetParentRegion", &G4Region::GetParentRegion, py::arg("unique"), py::return_value_policy::reference)
      .def("SetRegionalSteppingAction", &G4Region::SetRegionalSteppingAction, py::arg("rusa"))
      .def("GetRegionalSteppingAction", &G4Region::GetRegionalSteppingAction, py::return_value_policy::reference)
      .def("GetInstanceID", &G4Region::GetInstanceID)
      .def_static("GetSubInstanceManager", &G4Region::GetSubInstanceManager)
      .def_static("Clean", &G4Region::Clean)
      .def("UsedInMassGeometry", &G4Region::UsedInMassGeometry, py::arg("val") = true)
      .def("UsedInParallelGeometry", &G4Region::UsedInParallelGeometry, py::arg("val") = true)
      .def("IsInMassGeometry", &G4Region::IsInMassGeometry)
      .def("IsInParallelGeometry", &G4Region::IsInParallelGeometry);
}
