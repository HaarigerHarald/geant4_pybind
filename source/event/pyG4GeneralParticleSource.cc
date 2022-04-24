#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4GeneralParticleSource.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4GeneralParticleSource : public G4GeneralParticleSource, public py::trampoline_self_life_support {
public:
   using G4GeneralParticleSource::G4GeneralParticleSource;

   void GeneratePrimaryVertex(G4Event *arg0) override
   {
      PYBIND11_OVERRIDE(void, G4GeneralParticleSource, GeneratePrimaryVertex, arg0);
   }
};

void export_G4GeneralParticleSource(py::module &m)
{
   py::class_<G4GeneralParticleSource, PyG4GeneralParticleSource, G4VPrimaryGenerator>(m, "G4GeneralParticleSource")

      .def("__copy__", [](const PyG4GeneralParticleSource &self) { return new PyG4GeneralParticleSource(self); })
      .def("__deepcopy__",
           [](const PyG4GeneralParticleSource &self, py::dict) { return new PyG4GeneralParticleSource(self); })

      .def("__copy__", [](const G4GeneralParticleSource &self) { return new G4GeneralParticleSource(self); })
      .def("__deepcopy__",
           [](const G4GeneralParticleSource &self, py::dict) { return new G4GeneralParticleSource(self); })

      .def(py::init<>())
      .def("AddaSource", &G4GeneralParticleSource::AddaSource)
      .def("ClearAll", &G4GeneralParticleSource::ClearAll)
      .def("DeleteaSource", &G4GeneralParticleSource::DeleteaSource)
      .def("GeneratePrimaryVertex", &G4GeneralParticleSource::GeneratePrimaryVertex)
      .def("GetCurrentSource", &G4GeneralParticleSource::GetCurrentSource, py::return_value_policy::reference)
      .def("GetCurrentSourceIndex", &G4GeneralParticleSource::GetCurrentSourceIndex)
      .def("GetCurrentSourceIntensity", &G4GeneralParticleSource::GetCurrentSourceIntensity)
      .def("GetNumberOfParticles", &G4GeneralParticleSource::GetNumberOfParticles)
      .def("GetNumberofSource", &G4GeneralParticleSource::GetNumberofSource)
      .def("GetParticleDefinition", &G4GeneralParticleSource::GetParticleDefinition, py::return_value_policy::reference)
      .def("GetParticleEnergy", &G4GeneralParticleSource::GetParticleEnergy)
      .def("GetParticleMomentumDirection", &G4GeneralParticleSource::GetParticleMomentumDirection)
      .def("GetParticlePolarization", &G4GeneralParticleSource::GetParticlePolarization)
      .def("GetParticlePosition", &G4GeneralParticleSource::GetParticlePosition)
      .def("GetParticleTime", &G4GeneralParticleSource::GetParticleTime)
      .def("ListSource", &G4GeneralParticleSource::ListSource)
      .def("SetCurrentSourceIntensity", &G4GeneralParticleSource::SetCurrentSourceIntensity)
      .def("SetCurrentSourceto", &G4GeneralParticleSource::SetCurrentSourceto)
      .def("SetFlatSampling", &G4GeneralParticleSource::SetFlatSampling, py::arg("av"))
      .def("SetMultipleVertex", &G4GeneralParticleSource::SetMultipleVertex, py::arg("av"))
      .def("SetNumberOfParticles", &G4GeneralParticleSource::SetNumberOfParticles, py::arg("i"))
      .def("SetParticleCharge", &G4GeneralParticleSource::SetParticleCharge, py::arg("aCharge"))
      .def("SetParticleDefinition", &G4GeneralParticleSource::SetParticleDefinition, py::arg("aPDef"))
      .def("SetParticlePolarization", &G4GeneralParticleSource::SetParticlePolarization, py::arg("aVal"))
      .def("SetParticleTime", &G4GeneralParticleSource::SetParticleTime, py::arg("aTime"))
      .def("SetVerbosity", &G4GeneralParticleSource::SetVerbosity, py::arg("i"));
}
