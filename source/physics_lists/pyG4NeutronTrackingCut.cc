#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4NeutronTrackingCut.hh>
#include <G4NeutronKiller.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4NeutronTrackingCut : public G4NeutronTrackingCut, public py::trampoline_self_life_support {
public:
   using G4NeutronTrackingCut::G4NeutronTrackingCut;

   void ConstructParticle() override { PYBIND11_OVERRIDE(void, G4NeutronTrackingCut, ConstructParticle, ); }

   void ConstructProcess() override { PYBIND11_OVERRIDE(void, G4NeutronTrackingCut, ConstructProcess, ); }
};

void export_G4NeutronTrackingCut(py::module &m)
{
   py::class_<G4NeutronTrackingCut, PyG4NeutronTrackingCut, G4VPhysicsConstructor>(m, "G4NeutronTrackingCut")

      .def(py::init<G4int>(), py::arg("ver") = 0)
      .def(py::init<const G4String &, G4int>(), py::arg("name"), py::arg("ver") = 0)

      .def("ConstructParticle", &G4NeutronTrackingCut::ConstructParticle)
      .def("ConstructProcess", &G4NeutronTrackingCut::ConstructProcess)

      .def("SetTimeLimit", &G4NeutronTrackingCut::SetTimeLimit)
      .def("SetKineticEnergyLimit", &G4NeutronTrackingCut::SetKineticEnergyLimit);
}
