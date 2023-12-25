#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4StoppingPhysics.hh>
#include <G4StoppingPhysicsFritiofWithBinaryCascade.hh>
#include <G4Version.hh>
#if G4VERSION_NUMBER >= 1120
#include <G4StoppingPhysicsWithINCLXX.hh>
#endif

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

#define ADD_STOPPING_PHYSICS(name)                        \
   py::class_<name, G4VPhysicsConstructor>(m, #name)      \
      .def(py::init<>())                                  \
      .def("ConstructParticle", &name::ConstructParticle) \
      .def("ConstructProcess", &name::ConstructProcess)

void export_G4StoppingPhysics(py::module &m)
{
   ADD_STOPPING_PHYSICS(G4StoppingPhysics);
   ADD_STOPPING_PHYSICS(G4StoppingPhysicsFritiofWithBinaryCascade);
#if G4VERSION_NUMBER >= 1120
   ADD_STOPPING_PHYSICS(G4StoppingPhysicsWithINCLXX)
      .def("SetMuonMinusCapture", &G4StoppingPhysicsWithINCLXX::SetMuonMinusCapture);
#endif
}
