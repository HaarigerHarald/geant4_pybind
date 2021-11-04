#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4IStore.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4ProductionCuts.hh>
#include <G4Material.hh>
#include <G4VUserRegionInformation.hh>
#include <G4MaterialCutsCouple.hh>
#include <G4UserLimits.hh>
#include <G4FieldManager.hh>
#include <G4FastSimulationManager.hh>
#include <G4UserSteppingAction.hh>
#include <G4VSensitiveDetector.hh>
#include <G4VisAttributes.hh>
#include <G4Allocator.hh>
#include <G4ReferenceCountedHandle.hh>
#include <G4VoxelLimits.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>
#include <G4VoxelSafety.hh>
#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4Trd.hh>
#include <G4Trap.hh>
#include <G4Cons.hh>
#include <G4Sphere.hh>
#include <G4Orb.hh>
#include <G4Ellipsoid.hh>
#include <G4Torus.hh>
#include <G4Para.hh>
#include <G4Polycone.hh>
#include <G4Polyhedra.hh>
#include <G4Hype.hh>
#include <G4PathFinder.hh>
#include <G4PropagatorInField.hh>
#include <G4GeometryMessenger.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4IStore : public G4IStore, public py::trampoline_self_life_support {
public:
   using G4IStore::G4IStore;

   G4double GetImportance(const G4GeometryCell &gCell) const override
   {
      PYBIND11_OVERRIDE(G4double, G4IStore, GetImportance, gCell);
   }

   G4bool IsKnown(const G4GeometryCell &gCell) const override { PYBIND11_OVERRIDE(G4bool, G4IStore, IsKnown, gCell); }

   const G4VPhysicalVolume &GetWorldVolume() const override
   {
      PYBIND11_OVERRIDE(const G4VPhysicalVolume &, G4IStore, GetWorldVolume, );
   }

   const G4VPhysicalVolume *GetParallelWorldVolumePointer() const override
   {
      PYBIND11_OVERRIDE(const G4VPhysicalVolume *, G4IStore, GetParallelWorldVolumePointer, );
   }
};

void export_G4IStore(py::module &m)
{
   py::class_<G4IStore, PyG4IStore, G4VIStore, py::nodelete>(m, "G4IStore")

      .def("__copy__", [](const PyG4IStore &self) { return PyG4IStore(self); })
      .def("__deepcopy__", [](const PyG4IStore &self, py::dict) { return PyG4IStore(self); })
      .def_static("GetInstance", py::overload_cast<>(&G4IStore::GetInstance), py::return_value_policy::reference)
      .def_static("GetInstance", py::overload_cast<G4String const &>(&G4IStore::GetInstance),
                  py::arg("ParallelWorldName"), py::return_value_policy::reference)

      .def("GetImportance", py::overload_cast<const G4GeometryCell &>(&G4IStore::GetImportance, py::const_),
           py::arg("gCell"))

      .def("IsKnown", &G4IStore::IsKnown, py::arg("gCell"))
      .def("Clear", &G4IStore::Clear)
      .def("SetWorldVolume", &G4IStore::SetWorldVolume)
      .def("SetParallelWorldVolume", &G4IStore::SetParallelWorldVolume, py::arg("paraName"))
      .def("GetWorldVolume", &G4IStore::GetWorldVolume)
      .def("GetParallelWorldVolumePointer", &G4IStore::GetParallelWorldVolumePointer,
           py::return_value_policy::reference)

      .def("AddImportanceGeometryCell",
           py::overload_cast<G4double, const G4GeometryCell &>(&G4IStore::AddImportanceGeometryCell),
           py::arg("importance"), py::arg("gCell"))

      .def("AddImportanceGeometryCell",
           py::overload_cast<G4double, const G4VPhysicalVolume &, G4int>(&G4IStore::AddImportanceGeometryCell),
           py::arg("importance"), py::arg("arg1"), py::arg("aRepNum") = 0)

      .def("ChangeImportance", py::overload_cast<G4double, const G4GeometryCell &>(&G4IStore::ChangeImportance),
           py::arg("importance"), py::arg("gCell"))

      .def("ChangeImportance",
           py::overload_cast<G4double, const G4VPhysicalVolume &, G4int>(&G4IStore::ChangeImportance),
           py::arg("importance"), py::arg("arg1"), py::arg("aRepNum") = 0)

      .def("GetImportance", py::overload_cast<const G4VPhysicalVolume &, G4int>(&G4IStore::GetImportance, py::const_),
           py::arg("arg0"), py::arg("aRepNum") = 0);
}
