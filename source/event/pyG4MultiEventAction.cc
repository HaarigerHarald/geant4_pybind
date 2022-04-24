#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4MultiEventAction.hh>
#include <G4EventManager.hh>
#include <G4Event.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4MultiEventAction : public G4MultiEventAction, public py::trampoline_self_life_support {
public:
   using G4MultiEventAction::G4MultiEventAction;

   void BeginOfEventAction(const G4Event *arg0) override
   {
      PYBIND11_OVERRIDE(void, G4MultiEventAction, BeginOfEventAction, arg0);
   }

   void EndOfEventAction(const G4Event *arg0) override
   {
      PYBIND11_OVERRIDE(void, G4MultiEventAction, EndOfEventAction, arg0);
   }

   void SetEventManager(G4EventManager *arg0) override
   {
      PYBIND11_OVERRIDE(void, G4MultiEventAction, SetEventManager, arg0);
   }
};

void export_G4MultiEventAction(py::module &m)
{
   py::class_<G4MultiEventAction, PyG4MultiEventAction, G4UserEventAction>(m, "G4MultiEventAction",
                                                                           py::multiple_inheritance())

      .def(py::init<>())
      .def("BeginOfEventAction", &G4MultiEventAction::BeginOfEventAction)
      .def("EndOfEventAction", &G4MultiEventAction::EndOfEventAction)
      .def("SetEventManager", &G4MultiEventAction::SetEventManager);
}
