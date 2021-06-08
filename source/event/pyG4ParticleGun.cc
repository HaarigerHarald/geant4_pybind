#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Event.hh>
#include <G4ParticleGun.hh>
#include <G4ParticleTable.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4ParticleGun(py::module &m)
{
   py::class_<G4ParticleGun>(m, "G4ParticleGun", "particle gun")

      .def(py::init<>())
      .def(py::init<G4int>())
      .def(py::init<G4ParticleDefinition *>())
      .def(py::init<G4ParticleDefinition *, G4int>())

      .def("GeneratePrimaryVertex", &G4ParticleGun::GeneratePrimaryVertex)
      .def("SetParticleDefinition", &G4ParticleGun::SetParticleDefinition)
      .def("GetParticleDefinition", &G4ParticleGun::GetParticleDefinition, py::return_value_policy::reference)
      .def("SetParticleMomentum", py::overload_cast<G4double>(&G4ParticleGun::SetParticleMomentum))
      .def("SetParticleMomentum", py::overload_cast<G4ParticleMomentum>(&G4ParticleGun::SetParticleMomentum))
      .def("SetParticleMomentumDirection", &G4ParticleGun::SetParticleMomentumDirection)
      .def("GetParticleMomentumDirection", &G4ParticleGun::GetParticleMomentumDirection)
      .def("SetParticleEnergy", &G4ParticleGun::SetParticleEnergy)
      .def("GetParticleEnergy", &G4ParticleGun::GetParticleEnergy)
      .def("SetParticleCharge", &G4ParticleGun::SetParticleCharge)
      .def("GetParticleCharge", &G4ParticleGun::GetParticleCharge)
      .def("SetParticlePolarization", &G4ParticleGun::SetParticlePolarization)
      .def("GetParticlePolarization", &G4ParticleGun::GetParticlePolarization)
      .def("SetNumberOfParticles", &G4ParticleGun::SetNumberOfParticles)
      .def("GetNumberOfParticles", &G4ParticleGun::GetNumberOfParticles)
      .def("SetParticlePosition", &G4ParticleGun::SetParticlePosition)
      .def("GetParticlePosition", &G4ParticleGun::GetParticlePosition)
      .def("SetParticleTime", &G4ParticleGun::SetParticleTime)
      .def("GetParticleTime", &G4ParticleGun::GetParticleTime)
      .def("SetParticleByName",
           [](G4ParticleGun &self, const std::string &pname) {
              G4ParticleTable *     particleTable = G4ParticleTable::GetParticleTable();
              G4ParticleDefinition *pd            = particleTable->FindParticle(pname);
              if (pd != 0) {
                 self.SetParticleDefinition(pd);
              } else {
                 G4cout << "*** \"" << pname << "\" is not registered "
                        << "in available particle list" << G4endl;
              }
           })

      .def("GetParticleByName", [](const G4ParticleGun &self) {
         const G4ParticleDefinition *pd = self.GetParticleDefinition();
         return (pd->GetParticleName()).c_str();
      });
}
