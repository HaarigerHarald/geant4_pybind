#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4StepLimiterPhysics.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4StepLimiterPhysics : public G4StepLimiterPhysics, public py::trampoline_self_life_support {
public:
   using G4StepLimiterPhysics::G4StepLimiterPhysics;

   void ConstructParticle() override { PYBIND11_OVERRIDE(void, G4StepLimiterPhysics, ConstructParticle, ); }

   void ConstructProcess() override { PYBIND11_OVERRIDE(void, G4StepLimiterPhysics, ConstructProcess, ); }
};

void export_G4StepLimiterPhysics(py::module &m)
{
   py::class_<G4StepLimiterPhysics, PyG4StepLimiterPhysics, G4VPhysicsConstructor>(m, "G4StepLimiterPhysics")

      .def(py::init<const G4String &>(), py::arg("name") = "stepLimiter")

      .def("ConstructParticle", &G4StepLimiterPhysics::ConstructParticle)
      .def("ConstructProcess", &G4StepLimiterPhysics::ConstructProcess)
      .def("SetApplyToAll", &G4StepLimiterPhysics::SetApplyToAll)
      .def("GetApplyToAll", &G4StepLimiterPhysics::GetApplyToAll);
}
