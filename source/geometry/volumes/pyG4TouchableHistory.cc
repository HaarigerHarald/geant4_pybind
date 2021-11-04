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

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4TouchableHistory : public G4TouchableHistory, public py::trampoline_self_life_support {
public:
   using G4TouchableHistory::G4TouchableHistory;

   G4VPhysicalVolume *GetVolume(G4int depth) const override
   {
      PYBIND11_OVERRIDE(G4VPhysicalVolume *, G4TouchableHistory, GetVolume, depth);
   }

   G4VSolid *GetSolid(G4int depth) const override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4TouchableHistory, GetSolid, depth);
   }

   const G4ThreeVector &GetTranslation(G4int depth) const override
   {
      PYBIND11_OVERRIDE(const G4ThreeVector &, G4TouchableHistory, GetTranslation, depth);
   }

   const G4RotationMatrix *GetRotation(G4int depth) const override
   {
      PYBIND11_OVERRIDE(const G4RotationMatrix *, G4TouchableHistory, GetRotation, depth);
   }

   G4int GetReplicaNumber(G4int depth) const override
   {
      PYBIND11_OVERRIDE(G4int, G4TouchableHistory, GetReplicaNumber, depth);
   }

   G4int GetHistoryDepth() const override { PYBIND11_OVERRIDE(G4int, G4TouchableHistory, GetHistoryDepth, ); }

   G4int MoveUpHistory(G4int num_levels) override
   {
      PYBIND11_OVERRIDE(G4int, G4TouchableHistory, MoveUpHistory, num_levels);
   }

   void UpdateYourself(G4VPhysicalVolume *pPhysVol, const G4NavigationHistory *history) override
   {
      PYBIND11_OVERRIDE(void, G4TouchableHistory, UpdateYourself, pPhysVol, history);
   }

   const G4NavigationHistory *GetHistory() const override
   {
      PYBIND11_OVERRIDE(const G4NavigationHistory *, G4TouchableHistory, GetHistory, );
   }
};

void export_G4TouchableHistory(py::module &m)
{
   py::class_<G4TouchableHistory, PyG4TouchableHistory, G4VTouchable>(m, "G4TouchableHistory")

      .def(py::init<>())
      .def(py::init<const G4NavigationHistory &>(), py::arg("history"))
      .def("__copy__", [](const PyG4TouchableHistory &self) { return PyG4TouchableHistory(self); })
      .def("__deepcopy__", [](const PyG4TouchableHistory &self, py::dict) { return PyG4TouchableHistory(self); })
      .def("GetVolume", &G4TouchableHistory::GetVolume, py::arg("depth") = 0, py::return_value_policy::reference)
      .def("GetSolid", &G4TouchableHistory::GetSolid, py::arg("depth") = 0, py::return_value_policy::reference)
      .def("GetTranslation", &G4TouchableHistory::GetTranslation, py::arg("depth") = 0)
      .def("GetRotation", &G4TouchableHistory::GetRotation, py::arg("depth") = 0, py::return_value_policy::reference)
      .def("GetReplicaNumber", &G4TouchableHistory::GetReplicaNumber, py::arg("depth") = 0)
      .def("GetHistoryDepth", &G4TouchableHistory::GetHistoryDepth)
      .def("MoveUpHistory", &G4TouchableHistory::MoveUpHistory, py::arg("num_levels") = 1)
      .def("UpdateYourself", &G4TouchableHistory::UpdateYourself, py::arg("pPhysVol"),
           py::arg("history") = static_cast<const G4NavigationHistory *>(nullptr))

      .def("GetHistory", &G4TouchableHistory::GetHistory, py::return_value_policy::reference);
}
