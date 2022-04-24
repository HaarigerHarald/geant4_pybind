#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4StackChecker.hh>
#include <G4StackManager.hh>
#include <G4Track.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4StackChecker : public G4StackChecker, public py::trampoline_self_life_support {
public:
   using G4StackChecker::G4StackChecker;

   G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track *track) override
   {
      PYBIND11_OVERRIDE(G4ClassificationOfNewTrack, G4StackChecker, ClassifyNewTrack, track);
   }

   void NewStage() override { PYBIND11_OVERRIDE(void, G4StackChecker, NewStage, ); }

   void PrepareNewEvent() override { PYBIND11_OVERRIDE(void, G4StackChecker, PrepareNewEvent, ); }
};

void export_G4StackChecker(py::module &m)
{
   py::class_<G4StackChecker, PyG4StackChecker, G4UserStackingAction>(m, "G4StackChecker")

      .def("__copy__", [](const PyG4StackChecker &self) { return new PyG4StackChecker(self); })
      .def("__deepcopy__", [](const PyG4StackChecker &self, py::dict) { return new PyG4StackChecker(self); })
      .def("__copy__", [](const G4StackChecker &self) { return new G4StackChecker(self); })
      .def("__deepcopy__", [](const G4StackChecker &self, py::dict) { return new G4StackChecker(self); })
      .def(py::init<>())
      .def("ClassifyNewTrack", &G4StackChecker::ClassifyNewTrack, py::arg("track"))
      .def("NewStage", &G4StackChecker::NewStage)
      .def("PrepareNewEvent", &G4StackChecker::PrepareNewEvent);
}
