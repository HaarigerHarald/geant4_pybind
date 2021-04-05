#include <pybind11/pybind11.h>

#include <G4Track.hh>
#include <G4UserStackingAction.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

class TRAMPOLINE_NAME(G4UserStackingAction) : public G4UserStackingAction {
public:
   using G4UserStackingAction::G4UserStackingAction;

   G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track *aTrack)
   {
      PYBIND11_OVERRIDE(G4ClassificationOfNewTrack, G4UserStackingAction, ClassifyNewTrack, aTrack);
   }

   void NewStage() { PYBIND11_OVERRIDE(void, G4UserStackingAction, NewStage, ); }

   void PrepareNewEvent() { PYBIND11_OVERRIDE(void, G4UserStackingAction, PrepareNewEvent, ); }

   TRAMPOLINE_DESTRUCTOR(G4UserStackingAction);
};

void export_G4UserStackingAction(py::module &m)
{
   py::class_<G4UserStackingAction, TRAMPOLINE_NAME(G4UserStackingAction), owntrans_ptr<G4UserStackingAction>>(
      m, "G4UserStackingAction", "stacking action class")
      .def(py::init<>())
      .def("ClassifyNewTrack", &G4UserStackingAction::ClassifyNewTrack)
      .def("NewStage", &G4UserStackingAction::NewStage)
      .def("PrepareNewEvent", &G4UserStackingAction::PrepareNewEvent);
}
