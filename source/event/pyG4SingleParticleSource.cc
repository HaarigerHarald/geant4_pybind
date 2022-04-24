#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4SingleParticleSource.hh>
#include <G4Event.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4SingleParticleSource : public G4SingleParticleSource, public py::trampoline_self_life_support {
public:
   using G4SingleParticleSource::G4SingleParticleSource;

   void GeneratePrimaryVertex(G4Event *evt) override
   {
      PYBIND11_OVERRIDE(void, G4SingleParticleSource, GeneratePrimaryVertex, evt);
   }
};

void export_G4SingleParticleSource(py::module &m)
{
   py::class_<G4SingleParticleSource, PyG4SingleParticleSource, G4VPrimaryGenerator>(m, "G4SingleParticleSource")

      .def(py::init<>())
      .def("GeneratePrimaryVertex", &G4SingleParticleSource::GeneratePrimaryVertex, py::arg("evt"))
      .def("GetAngDist", &G4SingleParticleSource::GetAngDist, py::return_value_policy::reference)
      .def("GetBiasRndm", &G4SingleParticleSource::GetBiasRndm, py::return_value_policy::reference)
      .def("GetEneDist", &G4SingleParticleSource::GetEneDist, py::return_value_policy::reference)
      .def("GetNumberOfParticles", &G4SingleParticleSource::GetNumberOfParticles)
      .def("GetParticleDefinition", &G4SingleParticleSource::GetParticleDefinition, py::return_value_policy::reference)
      .def("GetParticleEnergy", &G4SingleParticleSource::GetParticleEnergy)
      .def("GetParticleMomentumDirection", &G4SingleParticleSource::GetParticleMomentumDirection)
      .def("GetParticlePolarization", &G4SingleParticleSource::GetParticlePolarization)
      .def("GetParticlePosition", &G4SingleParticleSource::GetParticlePosition)
      .def("GetParticleTime", &G4SingleParticleSource::GetParticleTime)
      .def("GetPosDist", &G4SingleParticleSource::GetPosDist, py::return_value_policy::reference)
      .def("SetNumberOfParticles", &G4SingleParticleSource::SetNumberOfParticles, py::arg("i"))
      .def("SetParticleCharge", &G4SingleParticleSource::SetParticleCharge, py::arg("aCharge"))
      .def("SetParticleDefinition", &G4SingleParticleSource::SetParticleDefinition, py::arg("aParticleDefinition"))
      .def("SetParticlePolarization", &G4SingleParticleSource::SetParticlePolarization, py::arg("aVal"))
      .def("SetParticleTime", &G4SingleParticleSource::SetParticleTime, py::arg("aTime"))
      .def("SetVerbosity", &G4SingleParticleSource::SetVerbosity);
}
