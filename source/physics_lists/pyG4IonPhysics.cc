#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4IonBinaryCascadePhysics.hh>
#include <G4IonINCLXXPhysics.hh>
#include <G4IonPhysics.hh>
#include <G4IonPhysicsPHP.hh>
#include <G4IonPhysicsXS.hh>
#include <G4IonQMDPhysics.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

#define ADD_ION_PHYSICS(name)                             \
   py::class_<name, G4VPhysicsConstructor>(m, #name)      \
      .def(py::init<>())                                  \
      .def("ConstructParticle", &name::ConstructParticle) \
      .def("ConstructProcess", &name::ConstructProcess)

void export_G4IonPhysics(py::module &m)
{
   ADD_ION_PHYSICS(G4IonBinaryCascadePhysics);
   ADD_ION_PHYSICS(G4IonINCLXXPhysics);
   ADD_ION_PHYSICS(G4IonPhysics);
   ADD_ION_PHYSICS(G4IonPhysicsPHP);
   ADD_ION_PHYSICS(G4IonPhysicsXS);
   ADD_ION_PHYSICS(G4IonQMDPhysics);
}
