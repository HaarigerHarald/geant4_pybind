#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VUserParallelWorld.hh>
#include <G4VSensitiveDetector.hh>
#include <G4LogicalVolume.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PublicG4VUserParallelWorld : public G4VUserParallelWorld {
public:
   using G4VUserParallelWorld::G4VUserParallelWorld;
   using G4VUserParallelWorld::GetWorld;
   using G4VUserParallelWorld::SetSensitiveDetector;
};

class PyG4VUserParallelWorld : public G4VUserParallelWorld {
public:
   using G4VUserParallelWorld::G4VUserParallelWorld;

   void Construct() override { PYBIND11_OVERRIDE_PURE(void, G4VUserParallelWorld, Construct, ); }

   void ConstructSD() override { PYBIND11_OVERRIDE_PURE(void, G4VUserParallelWorld, ConstructSD, ); }
};

void export_G4VUserParallelWorld(py::module &m)
{
   py::class_<G4VUserParallelWorld, PyG4VUserParallelWorld>(m, "G4VUserParallelWorld")

      .def(py::init<G4String>())
      .def("Construct", &G4VUserParallelWorld::Construct)
      .def("ConstructSD", &G4VUserParallelWorld::ConstructSD)
      .def("GetName", &G4VUserParallelWorld::GetName)

      .def("GetWorld", &PublicG4VUserParallelWorld::GetWorld)
      .def("SetSensitiveDetector",
           static_cast<void (G4VUserParallelWorld::*)(const G4String &, G4VSensitiveDetector *, G4bool)>(
              &PublicG4VUserParallelWorld::SetSensitiveDetector),
           py::arg("logVolName"), py::arg("aSD"), py::arg("multi") = false)

      .def("SetSensitiveDetector",
           static_cast<void (G4VUserParallelWorld::*)(G4LogicalVolume *, G4VSensitiveDetector *)>(
              &PublicG4VUserParallelWorld::SetSensitiveDetector),
           py::arg("logVol"), py::arg("aSD"));
}
