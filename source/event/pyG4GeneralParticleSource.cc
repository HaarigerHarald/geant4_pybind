#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4GeneralParticleSource.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4GeneralParticleSource(py::module &m)
{
   py::class_<G4GeneralParticleSource, G4VPrimaryGenerator>(m, "G4GeneralParticleSource")
      .def(py::init<>())
      .def("GeneratePrimaryVertex", &G4GeneralParticleSource::GeneratePrimaryVertex)
      .def("GetNumberofSource", &G4GeneralParticleSource::GetNumberofSource)
      .def("ListSource", &G4GeneralParticleSource::ListSource)
      .def("SetCurrentSourceto", &G4GeneralParticleSource::SetCurrentSourceto)
      .def("SetCurrentSourceIntensity", &G4GeneralParticleSource::SetCurrentSourceIntensity)
      .def("GeneratePrimaryVertex", &G4GeneralParticleSource::GeneratePrimaryVertex)
      .def("GetCurrentSource", &G4GeneralParticleSource::GetCurrentSource, py::return_value_policy::reference)
      .def("GetCurrentSourceIndex", &G4GeneralParticleSource::GetCurrentSourceIndex)
      .def("GetCurrentSourceIntensity", &G4GeneralParticleSource::GetCurrentSourceIntensity)

      .def("ClearAll", &G4GeneralParticleSource::ClearAll)
      .def("AddaSource", &G4GeneralParticleSource::AddaSource)
      .def("DeleteaSource", &G4GeneralParticleSource::DeleteaSource)
      .def("SetVerbosity", &G4GeneralParticleSource::SetVerbosity)
      .def("SetMultipleVertex", &G4GeneralParticleSource::SetMultipleVertex)

      .def("SetFlatSampling", &G4GeneralParticleSource::SetFlatSampling)
      .def("SetParticleDefinition", &G4GeneralParticleSource::SetParticleDefinition, py::keep_alive<1, 2>())
      .def("GetParticleDefinition", &G4GeneralParticleSource::GetParticleDefinition, py::return_value_policy::reference)

      .def("SetParticleCharge", &G4GeneralParticleSource::SetParticleCharge)
      .def("SetParticlePolarization", &G4GeneralParticleSource::SetParticlePolarization)
      .def("GetParticlePolarization", &G4GeneralParticleSource::GetParticlePolarization)

      .def("SetParticleTime", &G4GeneralParticleSource::SetParticleTime)
      .def("GetParticleTime", &G4GeneralParticleSource::GetParticleTime)
      .def("SetNumberOfParticles", &G4GeneralParticleSource::SetNumberOfParticles)
      .def("GetNumberOfParticles", &G4GeneralParticleSource::GetNumberOfParticles)

      .def("GetParticlePosition", &G4GeneralParticleSource::GetParticlePosition)
      .def("GetParticleMomentumDirection", &G4GeneralParticleSource::GetParticleMomentumDirection)
      .def("GetParticleEnergy", &G4GeneralParticleSource::GetParticleEnergy);
}