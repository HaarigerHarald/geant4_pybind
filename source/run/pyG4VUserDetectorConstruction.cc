#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VUserDetectorConstruction.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VUserParallelWorld.hh>
#include <G4VSensitiveDetector.hh>
#include <G4LogicalVolume.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PublicG4VUserDetectorConstruction : public G4VUserDetectorConstruction {

public:
   using G4VUserDetectorConstruction::G4VUserDetectorConstruction;
   using G4VUserDetectorConstruction::SetSensitiveDetector;
};

class PyG4VUserDetectorConstruction : public G4VUserDetectorConstruction, public py::trampoline_self_life_support {

public:
   using G4VUserDetectorConstruction::G4VUserDetectorConstruction;

   G4VPhysicalVolume *Construct() override
   {
      PYBIND11_OVERRIDE_PURE(G4VPhysicalVolume *, G4VUserDetectorConstruction, Construct, );
   }

   void ConstructSDandField() override { PYBIND11_OVERRIDE(void, G4VUserDetectorConstruction, ConstructSDandField, ); }

   void CloneSD() override { PYBIND11_OVERRIDE(void, G4VUserDetectorConstruction, CloneSD, ); }

   void CloneF() override { PYBIND11_OVERRIDE(void, G4VUserDetectorConstruction, CloneF, ); }
};

void export_G4VUserDetectorConstruction(py::module &m)
{
   py::class_<G4VUserDetectorConstruction, PyG4VUserDetectorConstruction>(m, "G4VUserDetectorConstruction",
                                                                          "base class of user detector construction")

      .def(py::init<>())
      .def("Construct", &G4VUserDetectorConstruction::Construct)
      .def("ConstructSDandField", &G4VUserDetectorConstruction::ConstructSDandField)
      .def("GetNumberOfParallelWorld", &G4VUserDetectorConstruction::GetNumberOfParallelWorld)
      .def("ConstructParallelGeometries", &G4VUserDetectorConstruction::ConstructParallelGeometries)
      .def("ConstructParallelSD", &G4VUserDetectorConstruction::ConstructParallelSD)

      .def("CloneSD", &G4VUserDetectorConstruction::CloneSD)
      .def("CloneF", &G4VUserDetectorConstruction::CloneF)
      .def("RegisterParallelWorld", &G4VUserDetectorConstruction::RegisterParallelWorld)
      .def("GetParallelWorld", &G4VUserDetectorConstruction::GetParallelWorld)

      .def("SetSensitiveDetector",
           static_cast<void (G4VUserDetectorConstruction::*)(const G4String &, G4VSensitiveDetector *, G4bool)>(
              &PublicG4VUserDetectorConstruction::SetSensitiveDetector),
           py::arg("logVolName"), py::arg("aSD"), py::arg("multi") = false)

      .def("SetSensitiveDetector",
           static_cast<void (G4VUserDetectorConstruction::*)(G4LogicalVolume *, G4VSensitiveDetector *)>(
              &PublicG4VUserDetectorConstruction::SetSensitiveDetector),
           py::arg("logVol"), py::arg("aSD"));
}
