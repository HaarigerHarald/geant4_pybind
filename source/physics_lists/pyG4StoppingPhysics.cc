#include <pybind11/pybind11.h>

#include <G4StoppingPhysics.hh>
#include <G4StoppingPhysicsFritiofWithBinaryCascade.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

#define ADD_STOPPING_PHYSICS(name)                                       \
   py::class_<name, G4VPhysicsConstructor, owntrans_ptr<name>>(m, #name) \
      .def(py::init<>())                                                 \
      .def("ConstructParticle", &name::ConstructParticle)                \
      .def("ConstructProcess", &name::ConstructProcess)

void export_G4StoppingPhysics(py::module &m)
{
   ADD_STOPPING_PHYSICS(G4StoppingPhysics);
   ADD_STOPPING_PHYSICS(G4StoppingPhysicsFritiofWithBinaryCascade);
}
