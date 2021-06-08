#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4AntiNeutrinoE.hh>
#include <G4AntiNeutrinoMu.hh>
#include <G4AntiNeutrinoTau.hh>
#include <G4Electron.hh>
#include <G4LeptonConstructor.hh>
#include <G4MuonMinus.hh>
#include <G4MuonPlus.hh>
#include <G4NeutrinoE.hh>
#include <G4NeutrinoMu.hh>
#include <G4NeutrinoTau.hh>
#include <G4Positron.hh>
#include <G4TauMinus.hh>
#include <G4TauPlus.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

#define ADD_LEPTON(name)                                                                               \
   py::class_<G4##name, G4ParticleDefinition, py::nodelete>(m, "G4" #name)                             \
      .def_static("Definition", &G4##name::Definition, py::return_value_policy::reference)             \
      .def_static(#name "Definition", &G4##name::name##Definition, py::return_value_policy::reference) \
      .def_static(#name, &G4##name::name, py::return_value_policy::reference)

void export_G4Leptons(py::module &m)
{
   ADD_LEPTON(AntiNeutrinoE);
   ADD_LEPTON(AntiNeutrinoMu);
   ADD_LEPTON(AntiNeutrinoTau);
   ADD_LEPTON(Electron);
   // ADD_LEPTON(LeptonConstructor);
   ADD_LEPTON(MuonMinus);
   ADD_LEPTON(MuonPlus);
   ADD_LEPTON(NeutrinoE);
   ADD_LEPTON(NeutrinoMu);
   ADD_LEPTON(NeutrinoTau);
   ADD_LEPTON(Positron);
   ADD_LEPTON(TauMinus);
   ADD_LEPTON(TauPlus);
}
