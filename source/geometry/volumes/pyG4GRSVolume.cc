#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4GRSVolume.hh>
#include <G4VSolid.hh>
#include <G4NavigationHistory.hh>
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

class PyG4GRSVolume : public G4GRSVolume, public py::trampoline_self_life_support {
public:
   using G4GRSVolume::G4GRSVolume;

   G4VPhysicalVolume *GetVolume(G4int depth) const override
   {
      PYBIND11_OVERRIDE(G4VPhysicalVolume *, G4GRSVolume, GetVolume, depth);
   }

   G4VSolid *GetSolid(G4int depth) const override { PYBIND11_OVERRIDE(G4VSolid *, G4GRSVolume, GetSolid, depth); }

   const G4ThreeVector &GetTranslation(G4int depth) const override
   {
      PYBIND11_OVERRIDE(const G4ThreeVector &, G4GRSVolume, GetTranslation, depth);
   }

   const G4RotationMatrix *GetRotation(G4int depth) const override
   {
      PYBIND11_OVERRIDE(const G4RotationMatrix *, G4GRSVolume, GetRotation, depth);
   }

   G4int GetReplicaNumber(G4int depth) const override
   {
      PYBIND11_OVERRIDE(G4int, G4GRSVolume, GetReplicaNumber, depth);
   }

   G4int GetHistoryDepth() const override { PYBIND11_OVERRIDE(G4int, G4GRSVolume, GetHistoryDepth, ); }

   G4int MoveUpHistory(G4int num_levels) override { PYBIND11_OVERRIDE(G4int, G4GRSVolume, MoveUpHistory, num_levels); }

   void UpdateYourself(G4VPhysicalVolume *pPhysVol, const G4NavigationHistory *history) override
   {
      PYBIND11_OVERRIDE(void, G4GRSVolume, UpdateYourself, pPhysVol, history);
   }

   const G4NavigationHistory *GetHistory() const override
   {
      PYBIND11_OVERRIDE(const G4NavigationHistory *, G4GRSVolume, GetHistory, );
   }
};

void export_G4GRSVolume(py::module &m)
{
   py::class_<G4GRSVolume, PyG4GRSVolume, G4VTouchable>(m, "G4GRSVolume")

      .def(py::init<G4VPhysicalVolume *, const G4RotationMatrix *, const G4ThreeVector &>(), py::arg("pVol"),
           py::arg("pRot"), py::arg("tlate"))

      .def(py::init<G4VPhysicalVolume *, const G4RotationMatrix &, const G4ThreeVector &>(), py::arg("pVol"),
           py::arg("rot"), py::arg("tlate"))

      .def("GetVolume", &G4GRSVolume::GetVolume, py::arg("depth") = 0, py::return_value_policy::reference)
      .def("GetSolid", &G4GRSVolume::GetSolid, py::arg("depth") = 0, py::return_value_policy::reference)
      .def("GetTranslation", &G4GRSVolume::GetTranslation, py::arg("depth") = 0)
      .def("GetRotation", &G4GRSVolume::GetRotation, py::arg("depth") = 0, py::return_value_policy::reference);
}
