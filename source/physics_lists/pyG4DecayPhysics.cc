#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4DecayPhysics.hh>
#include <G4MuonicAtomDecayPhysics.hh>
#include <G4RadioactiveDecayPhysics.hh>
#include <G4SpinDecayPhysics.hh>
#include <G4UnknownDecayPhysics.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

#define ADD_DECAY_PHYSICS(name)                           \
   py::class_<name, G4VPhysicsConstructor>(m, #name)      \
      .def(py::init<>())                                  \
      .def("ConstructParticle", &name::ConstructParticle) \
      .def("ConstructProcess", &name::ConstructProcess)

void export_G4DecayPhysics(py::module &m)
{
   ADD_DECAY_PHYSICS(G4DecayPhysics);
   ADD_DECAY_PHYSICS(G4MuonicAtomDecayPhysics);
   ADD_DECAY_PHYSICS(G4RadioactiveDecayPhysics);
   ADD_DECAY_PHYSICS(G4SpinDecayPhysics);
   ADD_DECAY_PHYSICS(G4UnknownDecayPhysics);
}
