#include <pybind11/pybind11.h>

#include <G4Event.hh>
#include <G4UserEventAction.hh>
#include <G4EventManager.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

class TRAMPOLINE_NAME(G4UserEventAction) : public G4UserEventAction {
public:
   using G4UserEventAction::G4UserEventAction;

   void BeginOfEventAction(const G4Event *anEvent) override
   {
      PYBIND11_OVERRIDE(void, G4UserEventAction, BeginOfEventAction, anEvent);
   }

   void EndOfEventAction(const G4Event *anEvent) override
   {
      PYBIND11_OVERRIDE(void, G4UserEventAction, EndOfEventAction, anEvent);
   }

   void SetEventManager(G4EventManager *value) override
   {
      PYBIND11_OVERRIDE(void, G4UserEventAction, SetEventManager, value);
   }

   TRAMPOLINE_DESTRUCTOR(G4UserEventAction);
};

void export_G4UserEventAction(py::module &m)
{
   py::class_<G4UserEventAction, TRAMPOLINE_NAME(G4UserEventAction), owntrans_ptr<G4UserEventAction>>(
      m, "G4UserEventAction", "event action class")

      .def(py::init<>())
      .def("BeginOfEventAction", &G4UserEventAction::BeginOfEventAction)
      .def("EndOfEventAction", &G4UserEventAction::EndOfEventAction)
      .def("SetEventManager", &G4UserEventAction::SetEventManager);
}
