#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UserSteppingAction.hh>
#include <G4Step.hh>
#include <G4SteppingManager.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4UserSteppingAction : public G4UserSteppingAction, public py::trampoline_self_life_support {

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
};

void export_G4UserSteppingAction(py::module &m)
{
   py::class_<G4UserSteppingAction, PyG4UserSteppingAction>(m, "G4UserSteppingAction", "stepping action class")

      .def(py::init<>())
      .def("SetSteppingManagerPointer", &G4UserSteppingAction::SetSteppingManagerPointer)
      .def("UserSteppingAction", &G4UserSteppingAction::UserSteppingAction);
}
