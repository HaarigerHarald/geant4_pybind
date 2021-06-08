#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VPrimitivePlotter.hh>
#include <G4VSolid.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VPrimitivePlotter : public G4VPrimitivePlotter, public py::trampoline_self_life_support {
public:
   using G4VPrimitivePlotter::G4VPrimitivePlotter;

   G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) override
   {
      PYBIND11_OVERRIDE_PURE(G4bool, G4VPrimitivePlotter, ProcessHits, aStep, ROhist);
   }

   virtual G4int GetIndex(G4Step *aStep) override { PYBIND11_OVERRIDE(G4int, G4VPrimitivePlotter, GetIndex, aStep); }

   void Initialize(G4HCofThisEvent *hCofThisEvent) override
   {
      PYBIND11_OVERRIDE(void, G4VPrimitivePlotter, Initialize, hCofThisEvent);
   }

   void EndOfEvent(G4HCofThisEvent *hCofThisEvent) override
   {
      PYBIND11_OVERRIDE(void, G4VPrimitivePlotter, EndOfEvent, hCofThisEvent);
   }

   void clear() override { PYBIND11_OVERRIDE(void, G4VPrimitivePlotter, clear, ); }

   void DrawAll() override { PYBIND11_OVERRIDE(void, G4VPrimitivePlotter, DrawAll, ); }

   void PrintAll() override { PYBIND11_OVERRIDE(void, G4VPrimitivePlotter, PrintAll, ); }
};

void export_G4VPrimitivePlotter(py::module &m)
{
   py::class_<G4VPrimitivePlotter, PyG4VPrimitivePlotter, G4VPrimitiveScorer>(m, "G4VPrimitivePlotter")

      .def(py::init<G4String, G4int>(), py::arg("name"), py::arg("depth") = 0)

      .def("Plot", &G4VPrimitivePlotter::Plot)
      .def("GetNumberOfHist", &G4VPrimitivePlotter::GetNumberOfHist);
}
