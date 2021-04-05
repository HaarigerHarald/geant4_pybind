#include <pybind11/pybind11.h>

#include <G4StepLimiterPhysics.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

class PyG4StepLimiterPhysics : public G4StepLimiterPhysics {
public:
   using G4StepLimiterPhysics::G4StepLimiterPhysics;

   void ConstructParticle() override { PYBIND11_OVERRIDE(void, G4StepLimiterPhysics, ConstructParticle, ); }

   void ConstructProcess() override { PYBIND11_OVERRIDE(void, G4StepLimiterPhysics, ConstructProcess, ); }
};

void export_G4StepLimiterPhysics(py::module &m)
{

   py::class_<G4StepLimiterPhysics, G4VPhysicsConstructor, owntrans_ptr<G4StepLimiterPhysics>>(m,
                                                                                               "G4StepLimiterPhysics")
      .def(py::init<const G4String &>(), py::arg("name") = "stepLimiter")

      .def("ConstructParticle", &G4StepLimiterPhysics::ConstructParticle)
      .def("ConstructProcess", &G4StepLimiterPhysics::ConstructProcess)
      .def("SetApplyToAll", &G4StepLimiterPhysics::SetApplyToAll)
      .def("GetApplyToAll", &G4StepLimiterPhysics::GetApplyToAll);
}
