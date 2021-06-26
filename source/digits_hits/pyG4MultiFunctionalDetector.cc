#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4MultiFunctionalDetector.hh>
#include <G4VPrimitiveScorer.hh>
#include <G4VPrimitivePlotter.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PublicG4MultiFunctionalDetector : public G4MultiFunctionalDetector {
public:
   using G4MultiFunctionalDetector::ProcessHits;
};

// Trampolin class
class PyG4MultiFunctionalDetector : public G4MultiFunctionalDetector, public py::trampoline_self_life_support {
public:
   using G4MultiFunctionalDetector::G4MultiFunctionalDetector;

   void Initialize(G4HCofThisEvent *hCofThisEvent) override
   {
      PYBIND11_OVERRIDE(void, G4MultiFunctionalDetector, Initialize, hCofThisEvent);
   }

   void EndOfEvent(G4HCofThisEvent *hCofThisEvent) override
   {
      PYBIND11_OVERRIDE(void, G4MultiFunctionalDetector, EndOfEvent, hCofThisEvent);
   }

   void clear() override { PYBIND11_OVERRIDE(void, G4MultiFunctionalDetector, clear, ); }

   void DrawAll() override { PYBIND11_OVERRIDE(void, G4MultiFunctionalDetector, DrawAll, ); }

   void PrintAll() override { PYBIND11_OVERRIDE(void, G4MultiFunctionalDetector, PrintAll, ); }

   G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) override
   {
      PYBIND11_OVERRIDE(G4bool, G4MultiFunctionalDetector, ProcessHits, aStep, ROhist);
   }
};

void export_G4MultiFunctionalDetector(py::module &m)
{
   py::class_<G4MultiFunctionalDetector, PyG4MultiFunctionalDetector, G4VSensitiveDetector>(m,
                                                                                            "G4MultiFunctionalDetector")

      .def(py::init<G4String>())

      .def("Initialize", &G4MultiFunctionalDetector::Initialize)
      .def("EndOfEvent", &G4MultiFunctionalDetector::EndOfEvent)
      .def("clear", &G4MultiFunctionalDetector::clear)
      .def("DrawAll", &G4MultiFunctionalDetector::DrawAll)
      .def("PrintAll", &G4MultiFunctionalDetector::PrintAll)
      .def("ProcessHits", &PublicG4MultiFunctionalDetector::ProcessHits)
      .def("RegisterPrimitive",
           [](G4MultiFunctionalDetector &self, py::disown_ptr<G4VPrimitiveScorer> scorer) {
              return self.RegisterPrimitive(scorer);
           })

      .def("RemovePrimitive", &G4MultiFunctionalDetector::RemovePrimitive) // TODO pass ownership
      .def("GetNumberOfPrimitives", &G4MultiFunctionalDetector::GetNumberOfPrimitives)
      .def("GetPrimitive", &G4MultiFunctionalDetector::GetPrimitive, py::return_value_policy::reference_internal);
}
