#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VTouchable.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VSolid.hh>
#include <G4NavigationHistory.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VTouchable : public G4VTouchable, public py::trampoline_self_life_support {
public:
   using G4VTouchable::G4VTouchable;

   const G4ThreeVector &GetTranslation(G4int depth) const override
   {
      PYBIND11_OVERRIDE_PURE(const G4ThreeVector &, G4VTouchable, GetTranslation, depth);
   }

   const G4RotationMatrix *GetRotation(G4int depth) const override
   {
      PYBIND11_OVERRIDE_PURE(const G4RotationMatrix *, G4VTouchable, GetRotation, depth);
   }

   G4VPhysicalVolume *GetVolume(G4int depth) const override
   {
      PYBIND11_OVERRIDE(G4VPhysicalVolume *, G4VTouchable, GetVolume, depth);
   }

   G4VSolid *GetSolid(G4int depth) const override { PYBIND11_OVERRIDE(G4VSolid *, G4VTouchable, GetSolid, depth); }

   G4int GetReplicaNumber(G4int depth) const override
   {
      PYBIND11_OVERRIDE(G4int, G4VTouchable, GetReplicaNumber, depth);
   }

   G4int GetHistoryDepth() const override { PYBIND11_OVERRIDE(G4int, G4VTouchable, GetHistoryDepth, ); }

   G4int MoveUpHistory(G4int num_levels) override { PYBIND11_OVERRIDE(G4int, G4VTouchable, MoveUpHistory, num_levels); }

   void UpdateYourself(G4VPhysicalVolume *pPhysVol, const G4NavigationHistory *history) override
   {
      PYBIND11_OVERRIDE(void, G4VTouchable, UpdateYourself, pPhysVol, history);
   }

   const G4NavigationHistory *GetHistory() const override
   {
      PYBIND11_OVERRIDE(const G4NavigationHistory *, G4VTouchable, GetHistory, );
   }
};

void export_G4VTouchable(py::module &m)
{
   py::class_<G4VTouchable, PyG4VTouchable>(m, "G4VTouchable")

      .def(py::init<>())
      .def("__copy__", [](const PyG4VTouchable &self) { return PyG4VTouchable(self); })
      .def("__deepcopy__", [](const PyG4VTouchable &self, py::dict) { return PyG4VTouchable(self); })
      .def("GetTranslation", &G4VTouchable::GetTranslation, py::arg("depth") = 0)
      .def("GetRotation", &G4VTouchable::GetRotation, py::arg("depth") = 0, py::return_value_policy::reference)
      .def("GetVolume", &G4VTouchable::GetVolume, py::arg("depth") = 0, py::return_value_policy::reference)
      .def("GetSolid", &G4VTouchable::GetSolid, py::arg("depth") = 0, py::return_value_policy::reference)
      .def("GetReplicaNumber", &G4VTouchable::GetReplicaNumber, py::arg("depth") = 0)
      .def("GetCopyNumber", &G4VTouchable::GetCopyNumber, py::arg("depth") = 0)
      .def("GetHistoryDepth", &G4VTouchable::GetHistoryDepth)
      .def("MoveUpHistory", &G4VTouchable::MoveUpHistory, py::arg("num_levels") = 1)
      .def("UpdateYourself", &G4VTouchable::UpdateYourself, py::arg("pPhysVol"),
           py::arg("history") = static_cast<const G4NavigationHistory *>(nullptr))

      .def("GetHistory", &G4VTouchable::GetHistory, py::return_value_policy::reference);
}
