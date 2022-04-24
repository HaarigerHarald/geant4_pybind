#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4PrimaryTransformer.hh>
#include <G4Track.hh>
#include <G4ProcessManager.hh>
#include <G4VTrackingManager.hh>
#include <G4DecayTable.hh>
#include <G4ParticlePropertyTable.hh>
#include <G4UImessenger.hh>
#include <G4ParticleMessenger.hh>
#include <G4IonTable.hh>
#include <G4VUserPrimaryParticleInformation.hh>
#include <G4DecayProducts.hh>
#include <G4Event.hh>
#include <G4PrimaryVertex.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4PrimaryTransformer : public G4PrimaryTransformer, public py::trampoline_self_life_support {
public:
   using G4PrimaryTransformer::G4PrimaryTransformer;

   G4ParticleDefinition *GetDefinition(G4PrimaryParticle *pp) override
   {
      PYBIND11_OVERRIDE(G4ParticleDefinition *, G4PrimaryTransformer, GetDefinition, pp);
   }

   G4bool IsGoodForTrack(G4ParticleDefinition *pd) override
   {
      PYBIND11_OVERRIDE(G4bool, G4PrimaryTransformer, IsGoodForTrack, pd);
   }
};

void export_G4PrimaryTransformer(py::module &m)
{
   py::class_<G4PrimaryTransformer, PyG4PrimaryTransformer>(m, "G4PrimaryTransformer")

      .def("__copy__", [](const PyG4PrimaryTransformer &self) { return new PyG4PrimaryTransformer(self); })
      .def("__deepcopy__",
           [](const PyG4PrimaryTransformer &self, py::dict) { return new PyG4PrimaryTransformer(self); })

      .def("__copy__", [](const G4PrimaryTransformer &self) { return new G4PrimaryTransformer(self); })
      .def("__deepcopy__", [](const G4PrimaryTransformer &self, py::dict) { return new G4PrimaryTransformer(self); })
      .def(py::init<>())
      .def("CheckUnknown", &G4PrimaryTransformer::CheckUnknown)
      .def("GetUnknownParticleDefined", &G4PrimaryTransformer::GetUnknownParticleDefined)
      .def("GimmePrimaries", &G4PrimaryTransformer::GimmePrimaries, py::arg("anEvent"), py::arg("trackIDCounter") = 0,
           py::return_value_policy::reference)

      .def("SetUnknnownParticleDefined", &G4PrimaryTransformer::SetUnknnownParticleDefined, py::arg("vl"))
      .def("SetVerboseLevel", &G4PrimaryTransformer::SetVerboseLevel, py::arg("vl"));
}
