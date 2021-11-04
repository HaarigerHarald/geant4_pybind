#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VIStore.hh>
#include <G4GeometryCell.hh>
#include <G4VPhysicalVolume.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VIStore : public G4VIStore, public py::trampoline_self_life_support {
public:
   using G4VIStore::G4VIStore;

   G4double GetImportance(const G4GeometryCell &gCell) const override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4VIStore, GetImportance, gCell);
   }

   G4bool IsKnown(const G4GeometryCell &gCell) const override
   {
      PYBIND11_OVERRIDE_PURE(G4bool, G4VIStore, IsKnown, gCell);
   }

   const G4VPhysicalVolume &GetWorldVolume() const override
   {
      PYBIND11_OVERRIDE_PURE(const G4VPhysicalVolume &, G4VIStore, GetWorldVolume, );
   }
};

void export_G4VIStore(py::module &m)
{
   py::class_<G4VIStore, PyG4VIStore>(m, "G4VIStore")

      .def(py::init<>())
      .def("__copy__", [](const PyG4VIStore &self) { return PyG4VIStore(self); })
      .def("__deepcopy__", [](const PyG4VIStore &self, py::dict) { return PyG4VIStore(self); })
      .def("GetImportance", &G4VIStore::GetImportance, py::arg("gCell"))
      .def("IsKnown", &G4VIStore::IsKnown, py::arg("gCell"))
      .def("GetWorldVolume", &G4VIStore::GetWorldVolume);
}
