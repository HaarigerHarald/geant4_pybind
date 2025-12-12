#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4TouchableHistory.hh>
#include <G4VSolid.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4VPVParameterisation.hh>
#include <G4ProductionCuts.hh>
#include <G4Material.hh>
#include <G4VUserRegionInformation.hh>
#include <G4MaterialCutsCouple.hh>
#include <G4UserLimits.hh>
#include <G4FieldManager.hh>
#include <G4FastSimulationManager.hh>
#include <G4UserSteppingAction.hh>
#include <G4VSensitiveDetector.hh>
#include <G4SmartVoxelHeader.hh>
#include <G4VisAttributes.hh>
#include <G4Version.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4TouchableHistory(py::module &m)
{
#if G4VERSION_NUMBER >= 1120
   py::class_<G4TouchableHistory>(m, "G4TouchableHistory")
#else
   py::class_<G4TouchableHistory, G4VTouchable>(m, "G4TouchableHistory")
#endif
      .def(py::init<>())
      .def(py::init<const G4NavigationHistory &>(), py::arg("history"))
      .def("__copy__", [](const G4TouchableHistory &self) { return G4TouchableHistory(self); })
      .def("__deepcopy__", [](const G4TouchableHistory &self, py::dict) { return G4TouchableHistory(self); })
      .def("GetVolume", &G4TouchableHistory::GetVolume, py::arg("depth") = 0, py::return_value_policy::reference)
      .def("GetSolid", &G4TouchableHistory::GetSolid, py::arg("depth") = 0, py::return_value_policy::reference)
      .def("GetTranslation", &G4TouchableHistory::GetTranslation, py::arg("depth") = 0)
      .def("GetRotation", &G4TouchableHistory::GetRotation, py::arg("depth") = 0, py::return_value_policy::reference)
      .def("GetReplicaNumber", &G4TouchableHistory::GetReplicaNumber, py::arg("depth") = 0)
      .def("GetCopyNumber", &G4TouchableHistory::GetCopyNumber, py::arg("depth") = 0)
      .def("GetHistoryDepth", &G4TouchableHistory::GetHistoryDepth)
      .def("MoveUpHistory", &G4TouchableHistory::MoveUpHistory, py::arg("num_levels") = 1)
      .def("UpdateYourself", &G4TouchableHistory::UpdateYourself, py::arg("pPhysVol"),
           py::arg("history") = static_cast<const G4NavigationHistory *>(nullptr))

      .def("GetHistory", &G4TouchableHistory::GetHistory, py::return_value_policy::reference);
}
