#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4Event.hh>

#include "holder.hh"
#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class TRAMPOLINE_NAME(G4VUserPrimaryGeneratorAction) : public G4VUserPrimaryGeneratorAction {

public:
   using G4VUserPrimaryGeneratorAction::G4VUserPrimaryGeneratorAction;

   void GeneratePrimaries(G4Event *anEvent) override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VUserPrimaryGeneratorAction, GeneratePrimaries, anEvent);
   }

   TRAMPOLINE_DESTRUCTOR(G4VUserPrimaryGeneratorAction);
};

void export_G4VUserPrimaryGeneratorAction(py::module &m)
{
   py::class_<G4VUserPrimaryGeneratorAction, TRAMPOLINE_NAME(G4VUserPrimaryGeneratorAction),
              owntrans_ptr<G4VUserPrimaryGeneratorAction>>(m, "G4VUserPrimaryGeneratorAction",
                                                           "base class of user primary generator action")

      .def(py::init<>())
      .def("GeneratePrimaries", &G4VUserPrimaryGeneratorAction::GeneratePrimaries);
}
