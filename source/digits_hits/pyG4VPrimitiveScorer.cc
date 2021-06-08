#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VPrimitiveScorer.hh>
#include <G4VSolid.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PublicG4VPrimitiveScorer : public G4VPrimitiveScorer {
public:
   using G4VPrimitiveScorer::CheckAndSetUnit;
   using G4VPrimitiveScorer::ComputeCurrentSolid;
   using G4VPrimitiveScorer::ComputeSolid;
   using G4VPrimitiveScorer::G4VPrimitiveScorer;
   using G4VPrimitiveScorer::GetIndex;
   using G4VPrimitiveScorer::ProcessHits;
};

class PyG4VPrimitiveScorer : public G4VPrimitiveScorer, public py::trampoline_self_life_support {
public:
   using G4VPrimitiveScorer::G4VPrimitiveScorer;

   G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) override
   {
      PYBIND11_OVERRIDE_PURE(G4bool, G4VPrimitiveScorer, ProcessHits, aStep, ROhist);
   }

   virtual G4int GetIndex(G4Step *aStep) override { PYBIND11_OVERRIDE(G4int, G4VPrimitiveScorer, GetIndex, aStep); }

   void Initialize(G4HCofThisEvent *hCofThisEvent) override
   {
      PYBIND11_OVERRIDE(void, G4VPrimitiveScorer, Initialize, hCofThisEvent);
   }

   void EndOfEvent(G4HCofThisEvent *hCofThisEvent) override
   {
      PYBIND11_OVERRIDE(void, G4VPrimitiveScorer, EndOfEvent, hCofThisEvent);
   }

   void clear() override { PYBIND11_OVERRIDE(void, G4VPrimitiveScorer, clear, ); }

   void DrawAll() override { PYBIND11_OVERRIDE(void, G4VPrimitiveScorer, DrawAll, ); }

   void PrintAll() override { PYBIND11_OVERRIDE(void, G4VPrimitiveScorer, PrintAll, ); }
};

void export_G4VPrimitiveScorer(py::module &m)
{
   py::class_<G4VPrimitiveScorer, PyG4VPrimitiveScorer>(m, "G4VPrimitiveScorer")

      .def(py::init<G4String, G4int>(), py::arg("name"), py::arg("depth") = 0)

      .def("ProcessHits", &PublicG4VPrimitiveScorer::ProcessHits)
      .def("GetIndex", &PublicG4VPrimitiveScorer::GetIndex)

      .def("GetCollectionID", &G4VPrimitiveScorer::GetCollectionID)

      .def("Initialize", &G4VPrimitiveScorer::Initialize)
      .def("EndOfEvent", &G4VPrimitiveScorer::EndOfEvent)
      .def("clear", &G4VPrimitiveScorer::clear)
      .def("DrawAll", &G4VPrimitiveScorer::DrawAll)
      .def("PrintAll", &G4VPrimitiveScorer::PrintAll)

      .def("SetUnit", &G4VPrimitiveScorer::SetUnit)
      .def("GetUnit", &G4VPrimitiveScorer::GetUnit)
      .def("GetUnitValue", &G4VPrimitiveScorer::GetUnitValue)

      .def("CheckAndSetUnit", &PublicG4VPrimitiveScorer::CheckAndSetUnit)

      .def("SetMultiFunctionalDetector", &G4VPrimitiveScorer::SetMultiFunctionalDetector)
      .def("GetMultiFunctionalDetector", &G4VPrimitiveScorer::GetMultiFunctionalDetector,
           py::return_value_policy::reference)

      .def("GetName", &G4VPrimitiveScorer::GetName)
      .def("SetFilter", &G4VPrimitiveScorer::SetFilter)
      .def("GetFilter", &G4VPrimitiveScorer::GetFilter, py::return_value_policy::reference)

      .def("SetVerboseLevel", &G4VPrimitiveScorer::SetVerboseLevel)
      .def("GetVerboseLevel", &G4VPrimitiveScorer::GetVerboseLevel)

      .def("ComputeSolid", &PublicG4VPrimitiveScorer::ComputeSolid)
      .def("ComputeCurrentSolid", &PublicG4VPrimitiveScorer::ComputeCurrentSolid)
      .def("SetNijk", &G4VPrimitiveScorer::SetNijk, py::arg("i"), py::arg("j"), py::arg("k"));
}
