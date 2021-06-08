#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4EmExtraPhysics.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4GLNPhysics(py::module &m)
{
   py::class_<G4EmExtraPhysics, G4VPhysicsConstructor>(m, "G4EmExtraPhysics")
      .def(py::init<>())
      .def("ConstructParticle", &G4EmExtraPhysics::ConstructParticle)
      .def("ConstructProcess", &G4EmExtraPhysics::ConstructProcess);
}
