#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Track.hh>
#include <G4UserStackingAction.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4UserStackingAction : public G4UserStackingAction, public py::trampoline_self_life_support {
public:
   using G4UserStackingAction::G4UserStackingAction;

   G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track *aTrack)
   {
      PYBIND11_OVERRIDE(G4ClassificationOfNewTrack, G4UserStackingAction, ClassifyNewTrack, aTrack);
   }

   void NewStage() { PYBIND11_OVERRIDE(void, G4UserStackingAction, NewStage, ); }

   void PrepareNewEvent() { PYBIND11_OVERRIDE(void, G4UserStackingAction, PrepareNewEvent, ); }
};

void export_G4UserStackingAction(py::module &m)
{
   py::class_<G4UserStackingAction, PyG4UserStackingAction>(m, "G4UserStackingAction", "stacking action class")
      .def(py::init<>())
      .def("ClassifyNewTrack", &G4UserStackingAction::ClassifyNewTrack)
      .def("NewStage", &G4UserStackingAction::NewStage)
      .def("PrepareNewEvent", &G4UserStackingAction::PrepareNewEvent);
}
