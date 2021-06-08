#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Run.hh>
#include <G4HCtable.hh>
#include <G4DCtable.hh>
#include <G4Event.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4Run : public G4Run, public py::trampoline_self_life_support {
public:
   using G4Run::G4Run;

   void RecordEvent(const G4Event *anEvent) override { PYBIND11_OVERRIDE(void, G4Run, RecordEvent, anEvent); }

   void Merge(const G4Run *aRun) override { PYBIND11_OVERRIDE(void, G4Run, Merge, aRun); }
};

void export_G4Run(py::module &m)
{
   py::class_<G4Run, PyG4Run>(m, "G4Run", "run class")

      .def(py::init<>())

      .def("GetRunID", &G4Run::GetRunID)
      .def("SetRunID", &G4Run::SetRunID)
      .def("GetNumberOfEvent", &G4Run::GetNumberOfEvent)
      .def("GetNumberOfEventToBeProcessed", &G4Run::GetNumberOfEventToBeProcessed)
      .def("SetNumberOfEventToBeProcessed", &G4Run::SetNumberOfEventToBeProcessed)
      .def("GetHCtable", &G4Run::GetHCtable, py::return_value_policy::reference_internal)
      .def("SetHCtable", &G4Run::GetHCtable) // TODO pass ownership
      .def("GetDCtable", &G4Run::GetDCtable, py::return_value_policy::reference_internal)
      .def("SetDCtable", &G4Run::SetDCtable) // TODO pass ownership
      .def("GetRandomNumberStatus", &G4Run::GetRandomNumberStatus)
      .def("SetRandomNumberStatus", &G4Run::SetRandomNumberStatus)
      .def("StoreEvent", [](G4Run &self, py::disown_ptr<G4Event> evt) { self.StoreEvent(evt); })
      .def("GetEventVector", &G4Run::GetEventVector, py::return_value_policy::reference_internal)

      .def("RecordEvent", &G4Run::RecordEvent)
      .def("Merge", &G4Run::Merge);
}
