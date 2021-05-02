#include <pybind11/pybind11.h>

#include <G4NeutronTrackingCut.hh>
#include <G4NeutronKiller.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

class TRAMPOLINE_NAME(G4NeutronTrackingCut) : public G4NeutronTrackingCut {
public:
   using G4NeutronTrackingCut::G4NeutronTrackingCut;

   void ConstructParticle() override { PYBIND11_OVERRIDE(void, G4NeutronTrackingCut, ConstructParticle, ); }

   void ConstructProcess() override { PYBIND11_OVERRIDE(void, G4NeutronTrackingCut, ConstructProcess, ); }

   TRAMPOLINE_DESTRUCTOR(G4NeutronTrackingCut);
};

void export_G4NeutronTrackingCut(py::module &m)
{
   py::class_<G4NeutronTrackingCut, TRAMPOLINE_NAME(G4NeutronTrackingCut), G4VPhysicsConstructor,
              owntrans_ptr<G4NeutronTrackingCut>>(m, "G4NeutronTrackingCut")

      .def(py::init<G4int>(), py::arg("ver") = 0)
      .def(py::init<const G4String &, G4int>(), py::arg("name"), py::arg("ver") = 0)

      .def("ConstructParticle", &G4NeutronTrackingCut::ConstructParticle)
      .def("ConstructProcess", &G4NeutronTrackingCut::ConstructProcess)

      .def("SetTimeLimit", &G4NeutronTrackingCut::SetTimeLimit)
      .def("SetKineticEnergyLimit", &G4NeutronTrackingCut::SetKineticEnergyLimit);
}
