#include <pybind11/pybind11.h>

#include <G4FastSimulationPhysics.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

class TRAMPOLINE_NAME(G4FastSimulationPhysics) : public G4FastSimulationPhysics {
public:
   using G4FastSimulationPhysics::G4FastSimulationPhysics;

   void ConstructParticle() override { PYBIND11_OVERRIDE(void, G4FastSimulationPhysics, ConstructParticle, ); }

   void ConstructProcess() override { PYBIND11_OVERRIDE(void, G4FastSimulationPhysics, ConstructProcess, ); }

   TRAMPOLINE_DESTRUCTOR(G4FastSimulationPhysics);
};

void export_G4FastSimulationPhysics(py::module &m)
{

   py::class_<G4FastSimulationPhysics, TRAMPOLINE_NAME(G4FastSimulationPhysics), G4VPhysicsConstructor,
              owntrans_ptr<G4FastSimulationPhysics>>(m, "G4FastSimulationPhysics")

      .def(py::init<const G4String &>(), py::arg("name") = "FastSimP")

      .def("ConstructParticle", &G4FastSimulationPhysics::ConstructParticle)
      .def("ConstructProcess", &G4FastSimulationPhysics::ConstructProcess)

      .def("ActivateFastSimulation", &G4FastSimulationPhysics::ActivateFastSimulation, py::arg("particleName"),
           py::arg("parallelGeometryName") = "")
      .def("BeVerbose", &G4FastSimulationPhysics::BeVerbose);
}
