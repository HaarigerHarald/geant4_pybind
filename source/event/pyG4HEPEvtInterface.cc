#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4HEPEvtInterface.hh>
#include <G4Event.hh>
#include <G4ParticleDefinition.hh>
#include <G4VUserPrimaryParticleInformation.hh>
#include <G4PrimaryVertex.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4HEPEvtInterface : public G4HEPEvtInterface, public py::trampoline_self_life_support {
public:
   using G4HEPEvtInterface::G4HEPEvtInterface;

   void GeneratePrimaryVertex(G4Event *evt) override
   {
      PYBIND11_OVERRIDE(void, G4HEPEvtInterface, GeneratePrimaryVertex, evt);
   }
};

void export_G4HEPEvtInterface(py::module &m)
{
   py::class_<G4HEPEvtInterface, PyG4HEPEvtInterface, G4VPrimaryGenerator>(m, "G4HEPEvtInterface")

      .def(py::init<const char *, G4int>(), py::arg("evfile"), py::arg("vl") = 0)
      .def("GeneratePrimaryVertex", &G4HEPEvtInterface::GeneratePrimaryVertex, py::arg("evt"));
}
