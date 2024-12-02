#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4MultiSensitiveDetector.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PublicG4MultiSensitiveDetector : public G4MultiSensitiveDetector {
public:
   using G4MultiSensitiveDetector::ProcessHits;
};

// Trampolin class
class PyG4MultiSensitiveDetector : public G4MultiSensitiveDetector, public py::trampoline_self_life_support {
public:
   using G4MultiSensitiveDetector::G4MultiSensitiveDetector;

   void Initialize(G4HCofThisEvent *hCofThisEvent) override
   {
      PYBIND11_OVERRIDE(void, G4MultiSensitiveDetector, Initialize, hCofThisEvent);
   }

   void EndOfEvent(G4HCofThisEvent *hCofThisEvent) override
   {
      PYBIND11_OVERRIDE(void, G4MultiSensitiveDetector, EndOfEvent, hCofThisEvent);
   }

   void clear() override { PYBIND11_OVERRIDE(void, G4MultiSensitiveDetector, clear, ); }

   void DrawAll() override { PYBIND11_OVERRIDE(void, G4MultiSensitiveDetector, DrawAll, ); }

   void PrintAll() override { PYBIND11_OVERRIDE(void, G4MultiSensitiveDetector, PrintAll, ); }

   G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) override
   {
      PYBIND11_OVERRIDE(G4bool, G4MultiSensitiveDetector, ProcessHits, aStep, ROhist);
   }
};

void export_G4MultiSensitiveDetector(py::module &m)
{
   py::class_<G4MultiSensitiveDetector, PyG4MultiSensitiveDetector, G4VSensitiveDetector>(m, "G4MultiSensitiveDetector")

      .def(py::init<G4String>())

      .def("Initialize", &G4MultiSensitiveDetector::Initialize)
      .def("EndOfEvent", &G4MultiSensitiveDetector::EndOfEvent)
      .def("clear", &G4MultiSensitiveDetector::clear)
      .def("DrawAll", &G4MultiSensitiveDetector::DrawAll)
      .def("PrintAll", &G4MultiSensitiveDetector::PrintAll)
      .def("ProcessHits", &PublicG4MultiSensitiveDetector::ProcessHits)
      .def("GetSD", &G4MultiSensitiveDetector::GetSD)
      .def("GetSize", &G4MultiSensitiveDetector::GetSize)
      .def("ClearSDs", &G4MultiSensitiveDetector::ClearSDs)
      .def("AddSD", &G4MultiSensitiveDetector::AddSD);
}
