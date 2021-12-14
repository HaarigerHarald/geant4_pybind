#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Run(py::module &);
void export_G4UserRunAction(py::module &);
void export_G4VUserPrimaryGeneratorAction(py::module &);
void export_G4VUserParallelWorld(py::module &);
void export_G4VUserDetectorConstruction(py::module &);
void export_G4VUserPhysicsList(py::module &);
void export_G4VModularPhysicsList(py::module &);
void export_G4VPhysicsConstructor(py::module &);
void export_G4VUserActionInitialization(py::module &);
void export_G4RunManager(py::module &);
void export_G4RunManagerKernel(py::module &);
void export_G4MTRunManager(py::module &);

void export_modG4run(py::module &m)
{
   export_G4Run(m);
   export_G4UserRunAction(m);
   export_G4VUserPrimaryGeneratorAction(m);
   export_G4VUserParallelWorld(m);
   export_G4VUserDetectorConstruction(m);
   export_G4VUserPhysicsList(m);
   export_G4VModularPhysicsList(m);
   export_G4VPhysicsConstructor(m);
   export_G4VUserActionInitialization(m);
   export_G4RunManager(m);
   export_G4RunManagerKernel(m);
   export_G4MTRunManager(m);
}
