#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4FastSimulationPhysics.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4FastSimulationPhysics : public G4FastSimulationPhysics, public py::trampoline_self_life_support {
public:
   using G4FastSimulationPhysics::G4FastSimulationPhysics;

   void ConstructParticle() override { PYBIND11_OVERRIDE(void, G4FastSimulationPhysics, ConstructParticle, ); }

   void ConstructProcess() override { PYBIND11_OVERRIDE(void, G4FastSimulationPhysics, ConstructProcess, ); }
};

void export_G4FastSimulationPhysics(py::module &m)
{
   py::class_<G4FastSimulationPhysics, PyG4FastSimulationPhysics, G4VPhysicsConstructor>(m, "G4FastSimulationPhysics")

      .def(py::init<const G4String &>(), py::arg("name") = "FastSimP")

      .def("ConstructParticle", &G4FastSimulationPhysics::ConstructParticle)
      .def("ConstructProcess", &G4FastSimulationPhysics::ConstructProcess)

      .def("ActivateFastSimulation", &G4FastSimulationPhysics::ActivateFastSimulation, py::arg("particleName"),
           py::arg("parallelGeometryName") = "")
      .def("BeVerbose", &G4FastSimulationPhysics::BeVerbose);
}
