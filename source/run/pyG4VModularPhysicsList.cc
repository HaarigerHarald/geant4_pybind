#include <pybind11/pybind11.h>

#include <G4VModularPhysicsList.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

class TRAMPOLINE_NAME(G4VModularPhysicsList) : public G4VModularPhysicsList {

public:
   using G4VModularPhysicsList::G4VModularPhysicsList;

   void ConstructParticle() override { PYBIND11_OVERRIDE(void, G4VModularPhysicsList, ConstructParticle, ); }

   void ConstructProcess() override { PYBIND11_OVERRIDE(void, G4VModularPhysicsList, ConstructProcess, ); }

   void SetCuts() override { PYBIND11_OVERRIDE(void, G4VModularPhysicsList, SetCuts, ); }

   TRAMPOLINE_DESTRUCTOR(G4VModularPhysicsList);
};

void export_G4VModularPhysicsList(py::module &m)
{
   py::class_<G4VModularPhysicsList, G4VUserPhysicsList, TRAMPOLINE_NAME(G4VModularPhysicsList),
              owntrans_ptr<G4VModularPhysicsList>>(m, "G4VModularPhysicsList", "base class of modular physics list")

      .def(py::init<>())

      .def("ConstructParticle", &G4VModularPhysicsList::ConstructParticle)
      .def("ConstructProcess", &G4VModularPhysicsList::ConstructProcess)

      .def("RegisterPhysics",
           [](G4VModularPhysicsList &self, G4VPhysicsConstructor *physics) {
              self.RegisterPhysics(physics);
              TRAMPOLINE_REF_INCREASE(G4VPhysicsConstructor, physics);
              owntrans_ptr<G4VPhysicsConstructor>::remove(physics);
           })

      .def("GetPhysics", py::overload_cast<G4int>(&G4VModularPhysicsList::GetPhysics, py::const_),
           py::return_value_policy::reference)

      .def("GetPhysics", py::overload_cast<const G4String &>(&G4VModularPhysicsList::GetPhysics, py::const_),
           py::return_value_policy::reference)

      .def("GetPhysicsWithType", &G4VModularPhysicsList::GetPhysicsWithType, py::return_value_policy::reference)
      .def("SetVerboseLevel", &G4VModularPhysicsList::SetVerboseLevel)
      .def("GetVerboseLevel", &G4VModularPhysicsList::GetVerboseLevel);
}
