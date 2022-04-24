#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4AdjointStackingAction.hh>
#include <G4StackManager.hh>
#include <G4Track.hh>
#include <G4ParticleDefinition.hh>
#include <G4AdjointTrackingAction.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4AdjointStackingAction : public G4AdjointStackingAction, public py::trampoline_self_life_support {
public:
   using G4AdjointStackingAction::G4AdjointStackingAction;

   G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track *aTrack) override
   {
      PYBIND11_OVERRIDE(G4ClassificationOfNewTrack, G4AdjointStackingAction, ClassifyNewTrack, aTrack);
   }

   void NewStage() override { PYBIND11_OVERRIDE(void, G4AdjointStackingAction, NewStage, ); }

   void PrepareNewEvent() override { PYBIND11_OVERRIDE(void, G4AdjointStackingAction, PrepareNewEvent, ); }
};

void export_G4AdjointStackingAction(py::module &m)
{
   py::class_<G4AdjointStackingAction, PyG4AdjointStackingAction, G4UserStackingAction>(m, "G4AdjointStackingAction")

      .def("__copy__", [](const PyG4AdjointStackingAction &self) { return new PyG4AdjointStackingAction(self); })
      .def("__deepcopy__",
           [](const PyG4AdjointStackingAction &self, py::dict) { return new PyG4AdjointStackingAction(self); })

      .def("__copy__", [](const G4AdjointStackingAction &self) { return new G4AdjointStackingAction(self); })
      .def("__deepcopy__",
           [](const G4AdjointStackingAction &self, py::dict) { return new G4AdjointStackingAction(self); })

      .def(py::init<G4AdjointTrackingAction *>(), py::arg("anAction"))
      .def("ClassifyNewTrack", &G4AdjointStackingAction::ClassifyNewTrack, py::arg("aTrack"))
      .def("NewStage", &G4AdjointStackingAction::NewStage)
      .def("PrepareNewEvent", &G4AdjointStackingAction::PrepareNewEvent)
      .def("SetAdjointMode", &G4AdjointStackingAction::SetAdjointMode, py::arg("aBool"))
      .def("SetKillTracks", &G4AdjointStackingAction::SetKillTracks, py::arg("aBool"))
      .def("SetUserAdjointStackingAction", &G4AdjointStackingAction::SetUserAdjointStackingAction, py::arg("anAction"))
      .def("SetUserFwdStackingAction", &G4AdjointStackingAction::SetUserFwdStackingAction, py::arg("anAction"));
}
