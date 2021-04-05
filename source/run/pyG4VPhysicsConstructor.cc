#include <pybind11/pybind11.h>

#include <G4VPhysicsConstructor.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

class TRAMPOLINE_NAME(G4VPhysicsConstructor) : public G4VPhysicsConstructor {

public:
   using G4VPhysicsConstructor::G4VPhysicsConstructor;

   void ConstructParticle() override { PYBIND11_OVERRIDE_PURE(void, G4VPhysicsConstructor, ConstructParticle, ); }

   void ConstructProcess() override { PYBIND11_OVERRIDE_PURE(void, G4VPhysicsConstructor, ConstructProcess, ); }

   TRAMPOLINE_DESTRUCTOR(G4VPhysicsConstructor);
};

void export_G4VPhysicsConstructor(py::module &m)
{
   py::class_<G4VPhysicsConstructor, TRAMPOLINE_NAME(G4VPhysicsConstructor), owntrans_ptr<G4VPhysicsConstructor>>(
      m, "G4VPhysicsConstructor", "base class of user physics constructor")

      .def(py::init<const G4String &>(), py::arg("name") = "")
      .def(py::init<const G4String &, G4int>())

      .def("ConstructParticle", &G4VPhysicsConstructor::ConstructParticle)
      .def("ConstructProcess", &G4VPhysicsConstructor::ConstructProcess)

      .def("SetPhysicsName", &G4VPhysicsConstructor::SetPhysicsName, py::arg("name") = "")
      .def("GetPhysicsName", &G4VPhysicsConstructor::GetPhysicsName)
      .def("SetVerboseLevel", &G4VPhysicsConstructor::SetVerboseLevel)
      .def("GetVerboseLevel", &G4VPhysicsConstructor::GetVerboseLevel);
}
