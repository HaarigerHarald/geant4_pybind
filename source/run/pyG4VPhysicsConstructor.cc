#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VPhysicsConstructor.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VPhysicsConstructor : public G4VPhysicsConstructor, public py::trampoline_self_life_support {

public:
   using G4VPhysicsConstructor::G4VPhysicsConstructor;

   void ConstructParticle() override { PYBIND11_OVERRIDE_PURE(void, G4VPhysicsConstructor, ConstructParticle, ); }

   void ConstructProcess() override { PYBIND11_OVERRIDE_PURE(void, G4VPhysicsConstructor, ConstructProcess, ); }
};

void export_G4VPhysicsConstructor(py::module &m)
{
   py::class_<G4VPhysicsConstructor, PyG4VPhysicsConstructor>(m, "G4VPhysicsConstructor",
                                                              "base class of user physics constructor")

      .def(py::init<const G4String &>(), py::arg("name") = "")
      .def(py::init<const G4String &, G4int>())

      .def("ConstructParticle", &G4VPhysicsConstructor::ConstructParticle)
      .def("ConstructProcess", &G4VPhysicsConstructor::ConstructProcess)

      .def("SetPhysicsName", &G4VPhysicsConstructor::SetPhysicsName, py::arg("name") = "")
      .def("GetPhysicsName", &G4VPhysicsConstructor::GetPhysicsName)
      .def("SetVerboseLevel", &G4VPhysicsConstructor::SetVerboseLevel)
      .def("GetVerboseLevel", &G4VPhysicsConstructor::GetVerboseLevel);
}
