#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UserStackingAction.hh>
#include <G4StackManager.hh>
#include <G4Track.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4UserStackingAction : public G4UserStackingAction, public py::trampoline_self_life_support {
public:
   using G4UserStackingAction::G4UserStackingAction;

   G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track *aTrack) override
   {
      PYBIND11_OVERRIDE(G4ClassificationOfNewTrack, G4UserStackingAction, ClassifyNewTrack, aTrack);
   }

   void NewStage() override { PYBIND11_OVERRIDE(void, G4UserStackingAction, NewStage, ); }

   void PrepareNewEvent() override { PYBIND11_OVERRIDE(void, G4UserStackingAction, PrepareNewEvent, ); }
};

void export_G4UserStackingAction(py::module &m)
{
   py::class_<G4UserStackingAction, PyG4UserStackingAction>(m, "G4UserStackingAction")

      .def(py::init<>())
      .def("__copy__", [](const PyG4UserStackingAction &self) { return new PyG4UserStackingAction(self); })
      .def("__deepcopy__",
           [](const PyG4UserStackingAction &self, py::dict) { return new PyG4UserStackingAction(self); })

      .def("__copy__", [](const G4UserStackingAction &self) { return new G4UserStackingAction(self); })
      .def("__deepcopy__", [](const G4UserStackingAction &self, py::dict) { return new G4UserStackingAction(self); })
      .def("SetStackManager", &G4UserStackingAction::SetStackManager, py::arg("value"))
      .def("ClassifyNewTrack", &G4UserStackingAction::ClassifyNewTrack, py::arg("aTrack"))
      .def("NewStage", &G4UserStackingAction::NewStage)
      .def("PrepareNewEvent", &G4UserStackingAction::PrepareNewEvent);
}
