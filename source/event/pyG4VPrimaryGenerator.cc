#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VPrimaryGenerator.hh>
#include <G4Event.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VPrimaryGenerator : public G4VPrimaryGenerator {
public:
   using G4VPrimaryGenerator::G4VPrimaryGenerator;

   virtual void GeneratePrimaryVertex(G4Event *evt) override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VPrimaryGenerator, GeneratePrimaryVertex, evt);
   }
};

void export_G4VPrimaryGenerator(py::module &m)
{
   py::class_<G4VPrimaryGenerator, PyG4VPrimaryGenerator>(m, "G4VPrimaryGenerator")
      .def(py::init<>())
      .def_static("CheckVertexInsideWorld", &G4VPrimaryGenerator::CheckVertexInsideWorld)

      .def("GeneratePrimaryVertex", &G4VPrimaryGenerator::GeneratePrimaryVertex)
      .def("GetParticlePosition", &G4VPrimaryGenerator::GetParticlePosition)
      .def("GetParticleTime", &G4VPrimaryGenerator::GetParticleTime)

      .def("SetParticlePosition", &G4VPrimaryGenerator::SetParticlePosition)
      .def("SetParticleTime", &G4VPrimaryGenerator::SetParticleTime)
      .def("GetParticleTime", &G4VPrimaryGenerator::GetParticleTime);
}
