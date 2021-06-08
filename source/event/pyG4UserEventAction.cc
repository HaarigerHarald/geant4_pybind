#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Event.hh>
#include <G4UserEventAction.hh>
#include <G4EventManager.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4UserEventAction : public G4UserEventAction, public py::trampoline_self_life_support {
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
};

void export_G4UserEventAction(py::module &m)
{
   py::class_<G4UserEventAction, PyG4UserEventAction>(m, "G4UserEventAction", "event action class")

      .def(py::init<>())
      .def("BeginOfEventAction", &G4UserEventAction::BeginOfEventAction)
      .def("EndOfEventAction", &G4UserEventAction::EndOfEventAction)
      .def("SetEventManager", &G4UserEventAction::SetEventManager);
}
