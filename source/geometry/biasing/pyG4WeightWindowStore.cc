#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4WeightWindowStore.hh>
#include <G4VPhysicalVolume.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4WeightWindowStore : public G4WeightWindowStore, public py::trampoline_self_life_support {
public:
   using G4WeightWindowStore::G4WeightWindowStore;

   G4double GetLowerWeight(const G4GeometryCell &gCell, G4double partEnergy) const override
   {
      PYBIND11_OVERRIDE(G4double, G4WeightWindowStore, GetLowerWeight, gCell, partEnergy);
   }

   G4bool IsKnown(const G4GeometryCell &gCell) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4WeightWindowStore, IsKnown, gCell);
   }

   const G4VPhysicalVolume &GetWorldVolume() const override
   {
      PYBIND11_OVERRIDE(const G4VPhysicalVolume &, G4WeightWindowStore, GetWorldVolume, );
   }

   const G4VPhysicalVolume *GetParallelWorldVolumePointer() const override
   {
      PYBIND11_OVERRIDE(const G4VPhysicalVolume *, G4WeightWindowStore, GetParallelWorldVolumePointer, );
   }
};

void export_G4WeightWindowStore(py::module &m)
{
   py::class_<G4WeightWindowStore, PyG4WeightWindowStore, G4VWeightWindowStore, py::nodelete>(m, "G4WeightWindowStore")

      .def("__copy__", [](const PyG4WeightWindowStore &self) { return PyG4WeightWindowStore(self); })
      .def("__deepcopy__", [](const PyG4WeightWindowStore &self, py::dict) { return PyG4WeightWindowStore(self); })
      .def_static("GetInstance", py::overload_cast<>(&G4WeightWindowStore::GetInstance),
                  py::return_value_policy::reference)

      .def_static("GetInstance", py::overload_cast<G4String const &>(&G4WeightWindowStore::GetInstance),
                  py::arg("ParallelWorldName"), py::return_value_policy::reference)

      .def("GetLowerWeight", &G4WeightWindowStore::GetLowerWeight, py::arg("gCell"), py::arg("partEnergy"))
      .def("IsKnown", &G4WeightWindowStore::IsKnown, py::arg("gCell"))
      .def("Clear", &G4WeightWindowStore::Clear)
      .def("SetWorldVolume", &G4WeightWindowStore::SetWorldVolume)
      .def("SetParallelWorldVolume", &G4WeightWindowStore::SetParallelWorldVolume, py::arg("paraName"))
      .def("GetWorldVolume", &G4WeightWindowStore::GetWorldVolume)
      .def("GetParallelWorldVolumePointer", &G4WeightWindowStore::GetParallelWorldVolumePointer,
           py::return_value_policy::reference)

      .def("AddLowerWeights", &G4WeightWindowStore::AddLowerWeights, py::arg("gCell"), py::arg("lowerWeights"))
      .def("AddUpperEboundLowerWeightPairs", &G4WeightWindowStore::AddUpperEboundLowerWeightPairs, py::arg("gCell"),
           py::arg("enWeMap"))

      .def("SetGeneralUpperEnergyBounds", &G4WeightWindowStore::SetGeneralUpperEnergyBounds, py::arg("enBounds"));
}
