#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UserSteppingAction.hh>
#include <G4Step.hh>
#include <G4SteppingManager.hh>

#include "holder.hh"
#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class TRAMPOLINE_NAME(G4UserSteppingAction) : public G4UserSteppingAction {

public:
   using G4UserSteppingAction::G4UserSteppingAction;

   void SetSteppingManagerPointer(G4SteppingManager *pValue) override
   {
      PYBIND11_OVERRIDE(void, G4UserSteppingAction, SetSteppingManagerPointer, pValue);
   }

   void UserSteppingAction(const G4Step *aStep) override
   {
      PYBIND11_OVERRIDE(void, G4UserSteppingAction, UserSteppingAction, aStep);
   }

   TRAMPOLINE_DESTRUCTOR(G4UserSteppingAction);
};

void export_G4UserSteppingAction(py::module &m)
{
   py::class_<G4UserSteppingAction, TRAMPOLINE_NAME(G4UserSteppingAction), owntrans_ptr<G4UserSteppingAction>>(
      m, "G4UserSteppingAction", "stepping action class")

      .def(py::init<>())
      .def("SetSteppingManagerPointer", &G4UserSteppingAction::SetSteppingManagerPointer)
      .def("UserSteppingAction", &G4UserSteppingAction::UserSteppingAction);
}
