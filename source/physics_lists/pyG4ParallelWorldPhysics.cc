#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ParallelWorldPhysics.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4ParallelWorldPhysics : public G4ParallelWorldPhysics, py::trampoline_self_life_support {
public:
   using G4ParallelWorldPhysics::G4ParallelWorldPhysics;

   void ConstructParticle() override { PYBIND11_OVERRIDE(void, G4ParallelWorldPhysics, ConstructParticle, ); }

   void ConstructProcess() override { PYBIND11_OVERRIDE(void, G4ParallelWorldPhysics, ConstructProcess, ); }
};

void export_G4ParallelWorldPhysics(py::module &m)
{
   py::class_<G4ParallelWorldPhysics, PyG4ParallelWorldPhysics, G4VPhysicsConstructor>(m, "G4ParallelWorldPhysics")

      .def(py::init<const G4String &, G4bool>(), py::arg("name") = "ParallelWP", py::arg("layerdMass") = false)

      .def("ConstructParticle", &G4ParallelWorldPhysics::ConstructParticle)
      .def("ConstructProcess", &G4ParallelWorldPhysics::ConstructProcess);
}
