#include <pybind11/pybind11.h>

#include <G4ParallelWorldPhysics.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

class TRAMPOLINE_NAME(G4ParallelWorldPhysics) : public G4ParallelWorldPhysics {
public:
   using G4ParallelWorldPhysics::G4ParallelWorldPhysics;

   void ConstructParticle() override { PYBIND11_OVERRIDE(void, G4ParallelWorldPhysics, ConstructParticle, ); }

   void ConstructProcess() override { PYBIND11_OVERRIDE(void, G4ParallelWorldPhysics, ConstructProcess, ); }

   TRAMPOLINE_DESTRUCTOR(G4ParallelWorldPhysics);
};

void export_G4ParallelWorldPhysics(py::module &m)
{
   py::class_<G4ParallelWorldPhysics, TRAMPOLINE_NAME(G4ParallelWorldPhysics), G4VPhysicsConstructor,
              owntrans_ptr<G4ParallelWorldPhysics>>(m, "G4ParallelWorldPhysics")

      .def(py::init<const G4String &, G4bool>(), py::arg("name") = "ParallelWP", py::arg("layerdMass") = false)

      .def("ConstructParticle", &G4ParallelWorldPhysics::ConstructParticle)
      .def("ConstructProcess", &G4ParallelWorldPhysics::ConstructProcess);
}
