#include <pybind11/pybind11.h>

#include <G4VPhysicalVolume.hh>
#include <G4VSolid.hh>
#include <G4VTouchable.hh>

#include "typecast.hh"

namespace py = pybind11;

// Trampolin class
class PyG4VTouchable : public G4VTouchable {
public:
   using G4VTouchable::G4VTouchable;

   const G4ThreeVector &GetTranslation(G4int depth = 0) const override
   {
      PYBIND11_OVERRIDE_PURE(G4ThreeVector &, G4VTouchable, GetTranslation, depth);
   }

   const G4RotationMatrix *GetRotation(G4int depth = 0) const override
   {
      PYBIND11_OVERRIDE_PURE(G4RotationMatrix *, G4VTouchable, GetRotation, depth);
   }

   G4VPhysicalVolume *GetVolume(G4int depth = 0) const override
   {
      PYBIND11_OVERRIDE(G4VPhysicalVolume *, G4VTouchable, GetVolume, depth);
   }

   G4VSolid *GetSolid(G4int depth = 0) const override { PYBIND11_OVERRIDE(G4VSolid *, G4VTouchable, GetSolid, depth); }

   G4int GetReplicaNumber(G4int depth = 0) const override
   {
      PYBIND11_OVERRIDE(G4int, G4VTouchable, GetReplicaNumber, depth);
   }

   G4int GetHistoryDepth() const override { PYBIND11_OVERRIDE(G4int, G4VTouchable, GetHistoryDepth, ); }

   G4int MoveUpHistory(G4int num_levels = 1) override { PYBIND11_OVERRIDE(G4int, G4VTouchable, MoveUpHistory); }
};

void export_G4VTouchable(py::module &m)
{
   py::class_<G4VTouchable, PyG4VTouchable, std::unique_ptr<G4VTouchable>>(m, "G4VTouchable", "touchable class")
      .def(py::init<>())
      .def("GetTranslation", &G4VTouchable::GetTranslation, py::arg("depth") = 0)
      .def("GetRotation", &G4VTouchable::GetRotation, py::arg("depth") = 0, py::return_value_policy::reference)
      .def("GetVolume", &G4VTouchable::GetVolume, py::arg("depth") = 0, py::return_value_policy::reference)
      .def("GetSolid", &G4VTouchable::GetSolid, py::arg("depth") = 0, py::return_value_policy::reference)
      .def("GetReplicaNumber", &G4VTouchable::GetReplicaNumber, py::arg("depth") = 0)
      .def("GetHistoryDepth", &G4VTouchable::GetHistoryDepth)
      .def("MoveUpHistory", &G4VTouchable::MoveUpHistory, py::arg("num_levels") = 1)
      .def("GetCopyNumber", &G4VTouchable::GetCopyNumber, py::arg("depth") = 0);
}
