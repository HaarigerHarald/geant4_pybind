#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ParticleGun.hh>
#include <G4ParticleTable.hh>
#include <G4Event.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4ParticleGun : public G4ParticleGun, public py::trampoline_self_life_support {
public:
   using G4ParticleGun::G4ParticleGun;

   void GeneratePrimaryVertex(G4Event *evt) override
   {
      PYBIND11_OVERRIDE(void, G4ParticleGun, GeneratePrimaryVertex, evt);
   }

   void SetInitialValues() override { PYBIND11_OVERRIDE(void, G4ParticleGun, SetInitialValues, ); }
};

void export_G4ParticleGun(py::module &m)
{
   py::class_<G4ParticleGun, PyG4ParticleGun, G4VPrimaryGenerator>(m, "G4ParticleGun")

      .def(py::init<>())
      .def(py::init<G4int>(), py::arg("numberofparticles"))
      .def(py::init<G4ParticleDefinition *, G4int>(), py::arg("particleDef"), py::arg("numberofparticles") = 1)
      .def("GeneratePrimaryVertex", &G4ParticleGun::GeneratePrimaryVertex, py::arg("evt"))
      .def("GetNumberOfParticles", &G4ParticleGun::GetNumberOfParticles)
      .def("GetParticleCharge", &G4ParticleGun::GetParticleCharge)
      .def("GetParticleDefinition", &G4ParticleGun::GetParticleDefinition, py::return_value_policy::reference)
      .def("GetParticleEnergy", &G4ParticleGun::GetParticleEnergy)
      .def("GetParticleMomentum", &G4ParticleGun::GetParticleMomentum)
      .def("GetParticleMomentumDirection", &G4ParticleGun::GetParticleMomentumDirection)
      .def("GetParticlePolarization", &G4ParticleGun::GetParticlePolarization)
      .def("SetNumberOfParticles", &G4ParticleGun::SetNumberOfParticles, py::arg("i"))
      .def("SetParticleCharge", &G4ParticleGun::SetParticleCharge, py::arg("aCharge"))
      .def("SetParticleDefinition", &G4ParticleGun::SetParticleDefinition, py::arg("aParticleDefinition"))
      .def("SetParticleEnergy", &G4ParticleGun::SetParticleEnergy, py::arg("aKineticEnergy"))
      .def("SetParticleMomentum", py::overload_cast<G4double>(&G4ParticleGun::SetParticleMomentum),
           py::arg("aMomentum"))

      .def("SetParticleMomentum", py::overload_cast<G4ParticleMomentum>(&G4ParticleGun::SetParticleMomentum),
           py::arg("aMomentum"))

      .def("SetParticleMomentumDirection", &G4ParticleGun::SetParticleMomentumDirection, py::arg("aMomDirection"))
      .def("SetParticlePolarization", &G4ParticleGun::SetParticlePolarization, py::arg("aVal"))
      .def("SetParticleByName",
           [](G4ParticleGun &self, const G4String &pname) {
              G4ParticleTable      *particleTable = G4ParticleTable::GetParticleTable();
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
