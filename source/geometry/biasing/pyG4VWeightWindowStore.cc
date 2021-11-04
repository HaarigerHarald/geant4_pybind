#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VWeightWindowStore.hh>
#include <G4GeometryCell.hh>
#include <G4VPhysicalVolume.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VWeightWindowStore : public G4VWeightWindowStore, public py::trampoline_self_life_support {
public:
   using G4VWeightWindowStore::G4VWeightWindowStore;

   G4double GetLowerWeight(const G4GeometryCell &gCell, G4double partEnergy) const override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4VWeightWindowStore, GetLowerWeight, gCell, partEnergy);
   }

   G4bool IsKnown(const G4GeometryCell &gCell) const override
   {
      PYBIND11_OVERRIDE_PURE(G4bool, G4VWeightWindowStore, IsKnown, gCell);
   }

   const G4VPhysicalVolume &GetWorldVolume() const override
   {
      PYBIND11_OVERRIDE_PURE(const G4VPhysicalVolume &, G4VWeightWindowStore, GetWorldVolume, );
   }
};

void export_G4VWeightWindowStore(py::module &m)
{
   py::class_<G4VWeightWindowStore, PyG4VWeightWindowStore>(m, "G4VWeightWindowStore")

      .def(py::init<>())
      .def("__copy__", [](const PyG4VWeightWindowStore &self) { return PyG4VWeightWindowStore(self); })
      .def("__deepcopy__", [](const PyG4VWeightWindowStore &self, py::dict) { return PyG4VWeightWindowStore(self); })
      .def("GetLowerWeight", &G4VWeightWindowStore::GetLowerWeight, py::arg("gCell"), py::arg("partEnergy"))
      .def("IsKnown", &G4VWeightWindowStore::IsKnown, py::arg("gCell"))
      .def("GetWorldVolume", &G4VWeightWindowStore::GetWorldVolume);
}
