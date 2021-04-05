#include <pybind11/pybind11.h>

#include "typecast.hh"

namespace py = pybind11;

void export_PhysicsLists(py::module &);
void export_PhysListFactory(py::module &);
void export_G4StepLimiterPhysics(py::module &);
void export_G4DecayPhysics(py::module &);
void export_G4EmPhysics(py::module &);
void export_G4GLNPhysics(py::module &);
void export_G4HadronElasticPhysics(py::module &);
void export_G4HadronInelasticPhysics(py::module &);
void export_G4IonPhysics(py::module &);
void export_G4StoppingPhysics(py::module &);

void export_modG4physics_list(py::module &m)
{
   export_PhysicsLists(m);
   export_PhysListFactory(m);
   export_G4StepLimiterPhysics(m);
   export_G4DecayPhysics(m);
   export_G4EmPhysics(m);
   export_G4GLNPhysics(m);
   export_G4HadronElasticPhysics(m);
   export_G4HadronInelasticPhysics(m);
   export_G4IonPhysics(m);
   export_G4StoppingPhysics(m);
}
