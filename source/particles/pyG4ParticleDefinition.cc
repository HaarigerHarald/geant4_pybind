#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4DecayTable.hh>
#include <G4ParticleDefinition.hh>
#include <G4ParticleTable.hh>
#include <G4ProcessManager.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4ParticleDefinition(py::module &m)
{
   py::class_<G4ParticleDefinition>(m, "G4ParticleDefinition", "particle definition")

      .def(py::init<>([](const G4String &aName, G4double mass, G4double width, G4double charge, G4int iSpin,
                         G4int iParity, G4int iConjugation, G4int iIsospin, G4int iIsospin3, G4int gParity,
                         const G4String &pType, G4int lepton, G4int baryon, G4int encoding, G4bool stable,
                         G4double lifetime, py::disown_ptr<G4DecayTable> decaytable, G4bool shortlived,
                         const G4String &subType, G4int anti_encoding, G4double magneticMoment) {
              return new G4ParticleDefinition(aName, mass, width, charge, iSpin, iParity, iConjugation, iIsospin,
                                              iIsospin3, gParity, pType, lepton, baryon, encoding, stable, lifetime,
                                              decaytable, shortlived, subType, anti_encoding, magneticMoment);
           }),
           py::arg("aName"), py::arg("mass"), py::arg("width"), py::arg("charge"), py::arg("iSpin"), py::arg("iParity"),
           py::arg("iConjugation"), py::arg("iIsospin"), py::arg("iIsospinZ"), py::arg("gParity"), py::arg("pType"),
           py::arg("lepton"), py::arg("baryon"), py::arg("encoding"), py::arg("stable"), py::arg("lifetime"),
           py::arg("decaytable"), py::arg("shortlived") = false, py::arg("subType") = "", py::arg("anti_encoding") = 0,
           py::arg("magneticMoment") = 0.0)

      .def("GetParticleName", &G4ParticleDefinition::GetParticleName)
      .def("GetPDGMass", &G4ParticleDefinition::GetPDGMass)
      .def("GetPDGWidth", &G4ParticleDefinition::GetPDGWidth)
      .def("GetPDGCharge", &G4ParticleDefinition::GetPDGCharge)
      .def("GetPDGSpin", &G4ParticleDefinition::GetPDGSpin)
      .def("GetPDGiSpin", &G4ParticleDefinition::GetPDGiSpin)
      .def("GetPDGiParity", &G4ParticleDefinition::GetPDGiParity)
      .def("GetPDGiConjugation", &G4ParticleDefinition::GetPDGiConjugation)
      .def("GetPDGIsospin", &G4ParticleDefinition::GetPDGIsospin)
      .def("GetPDGIsospin3", &G4ParticleDefinition::GetPDGIsospin3)
      .def("GetPDGiIsospin", &G4ParticleDefinition::GetPDGiIsospin)
      .def("GetPDGiIsospin3", &G4ParticleDefinition::GetPDGiIsospin3)
      .def("GetPDGiGParity", &G4ParticleDefinition::GetPDGiGParity)
      .def("GetParticleType", &G4ParticleDefinition::GetParticleType)
      .def("GetParticleSubType", &G4ParticleDefinition::GetParticleSubType)
      .def("GetLeptonNumber", &G4ParticleDefinition::GetLeptonNumber)
      .def("GetBaryonNumber", &G4ParticleDefinition::GetBaryonNumber)
      .def("GetPDGEncoding", &G4ParticleDefinition::GetPDGEncoding)
      .def("GetAntiPDGEncoding", &G4ParticleDefinition::GetAntiPDGEncoding)
      .def("GetQuarkContent", &G4ParticleDefinition::GetQuarkContent)
      .def("GetAntiQuarkContent", &G4ParticleDefinition::GetAntiQuarkContent)
      .def("IsShortLived", &G4ParticleDefinition::IsShortLived)
      .def("GetPDGStable", &G4ParticleDefinition::GetPDGStable)
      .def("SetPDGStable", &G4ParticleDefinition::SetPDGStable)
      .def("GetPDGLifeTime", &G4ParticleDefinition::GetPDGLifeTime)
      .def("SetPDGLifeTime", &G4ParticleDefinition::SetPDGLifeTime)
      .def("GetDecayTable", &G4ParticleDefinition::GetDecayTable, py::return_value_policy::reference_internal)
      .def("SetDecayTable",
           [](G4ParticleDefinition &self, py::disown_ptr<G4DecayTable> decayTable) { self.SetDecayTable(decayTable); })

      .def("GetProcessManager", &G4ParticleDefinition::GetProcessManager, py::return_value_policy::reference_internal)
      .def("SetProcessManager", &G4ParticleDefinition::SetProcessManager)
      .def("GetParticleTable", &G4ParticleDefinition::GetParticleTable, py::return_value_policy::reference)
      .def("DumpTable", &G4ParticleDefinition::DumpTable)
      .def("GetAtomicNumber", &G4ParticleDefinition::GetAtomicNumber)
      .def("GetAtomicMass", &G4ParticleDefinition::GetAtomicMass)
      .def("SetVerboseLevel", &G4ParticleDefinition::SetVerboseLevel)
      .def("GetVerboseLevel", &G4ParticleDefinition::GetVerboseLevel)
      .def("SetApplyCutsFlag", &G4ParticleDefinition::SetApplyCutsFlag)
      .def("GetApplyCutsFlag", &G4ParticleDefinition::GetApplyCutsFlag);
}
