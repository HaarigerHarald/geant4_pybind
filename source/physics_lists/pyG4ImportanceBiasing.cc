#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ImportanceBiasing.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4ImportanceBiasing : public G4ImportanceBiasing, public py::trampoline_self_life_support {
public:
   using G4ImportanceBiasing::G4ImportanceBiasing;

   void ConstructParticle() override { PYBIND11_OVERRIDE(void, G4ImportanceBiasing, ConstructParticle, ); }

   void ConstructProcess() override { PYBIND11_OVERRIDE(void, G4ImportanceBiasing, ConstructProcess, ); }
};

void export_G4ImportanceBiasing(py::module &m)
{
   py::class_<G4ImportanceBiasing, PyG4ImportanceBiasing, G4VPhysicsConstructor>(m, "G4ImportanceBiasing")

      .def(py::init<const G4String &>(), py::arg("name") = "NoParallelWP")
      .def(py::init<G4GeometrySampler *, const G4String &>(), py::arg("msg"), py::arg("name") = "NoParallelWP")

      .def("ConstructParticle", &G4ImportanceBiasing::ConstructParticle)
      .def("ConstructProcess", &G4ImportanceBiasing::ConstructProcess);
}
