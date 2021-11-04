#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4GRSSolid.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VSolid.hh>
#include <G4NavigationHistory.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4GRSSolid : public G4GRSSolid, public py::trampoline_self_life_support {
public:
   using G4GRSSolid::G4GRSSolid;

   G4VSolid *GetSolid(G4int depth) const override { PYBIND11_OVERRIDE(G4VSolid *, G4GRSSolid, GetSolid, depth); }

   const G4ThreeVector &GetTranslation(G4int depth) const override
   {
      PYBIND11_OVERRIDE(const G4ThreeVector &, G4GRSSolid, GetTranslation, depth);
   }

   const G4RotationMatrix *GetRotation(G4int depth) const override
   {
      PYBIND11_OVERRIDE(const G4RotationMatrix *, G4GRSSolid, GetRotation, depth);
   }

   G4VPhysicalVolume *GetVolume(G4int depth) const override
   {
      PYBIND11_OVERRIDE(G4VPhysicalVolume *, G4GRSSolid, GetVolume, depth);
   }

   G4int GetReplicaNumber(G4int depth) const override { PYBIND11_OVERRIDE(G4int, G4GRSSolid, GetReplicaNumber, depth); }

   G4int GetHistoryDepth() const override { PYBIND11_OVERRIDE(G4int, G4GRSSolid, GetHistoryDepth, ); }

   G4int MoveUpHistory(G4int num_levels) override { PYBIND11_OVERRIDE(G4int, G4GRSSolid, MoveUpHistory, num_levels); }

   void UpdateYourself(G4VPhysicalVolume *pPhysVol, const G4NavigationHistory *history) override
   {
      PYBIND11_OVERRIDE(void, G4GRSSolid, UpdateYourself, pPhysVol, history);
   }

   const G4NavigationHistory *GetHistory() const override
   {
      PYBIND11_OVERRIDE(const G4NavigationHistory *, G4GRSSolid, GetHistory, );
   }
};

void export_G4GRSSolid(py::module &m)
{
   py::class_<G4GRSSolid, PyG4GRSSolid, G4VTouchable>(m, "G4GRSSolid")

      .def(py::init<G4VSolid *, const G4RotationMatrix *, const G4ThreeVector &>(), py::arg("pSolid"), py::arg("pRot"),
           py::arg("tlate"))

      .def(py::init<G4VSolid *, const G4RotationMatrix &, const G4ThreeVector &>(), py::arg("pSolid"), py::arg("rot"),
           py::arg("tlate"))

      .def("GetSolid", &G4GRSSolid::GetSolid, py::arg("depth") = 0, py::return_value_policy::reference)
      .def("GetTranslation", &G4GRSSolid::GetTranslation, py::arg("depth") = 0)
      .def("GetRotation", &G4GRSSolid::GetRotation, py::arg("depth") = 0, py::return_value_policy::reference);
}
