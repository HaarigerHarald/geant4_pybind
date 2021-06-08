#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4AntiBMesonZero.hh>
#include <G4AntiBsMesonZero.hh>
#include <G4AntiDMesonZero.hh>
#include <G4AntiKaonZero.hh>
#include <G4BcMesonMinus.hh>
#include <G4BcMesonPlus.hh>
#include <G4BMesonMinus.hh>
#include <G4BMesonPlus.hh>
#include <G4BMesonZero.hh>
#include <G4BsMesonZero.hh>
#include <G4DMesonMinus.hh>
#include <G4DMesonPlus.hh>
#include <G4DMesonZero.hh>
#include <G4DsMesonMinus.hh>
#include <G4DsMesonPlus.hh>
#include <G4Eta.hh>
#include <G4Etac.hh>
#include <G4EtaPrime.hh>
#include <G4JPsi.hh>
#include <G4KaonMinus.hh>
#include <G4KaonPlus.hh>
#include <G4KaonZero.hh>
#include <G4KaonZeroLong.hh>
#include <G4KaonZeroShort.hh>
#include <G4MesonConstructor.hh>
#include <G4PionMinus.hh>
#include <G4PionPlus.hh>
#include <G4PionZero.hh>
#include <G4Upsilon.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

#define ADD_MESON(name)                                                                                \
   py::class_<G4##name, G4ParticleDefinition, py::nodelete>(m, "G4" #name)                             \
      .def_static("Definition", &G4##name::Definition, py::return_value_policy::reference)             \
      .def_static(#name "Definition", &G4##name::name##Definition, py::return_value_policy::reference) \
      .def_static(#name, &G4##name::name, py::return_value_policy::reference)

void export_G4Mesons(py::module &m)
{
   ADD_MESON(AntiBMesonZero);
   ADD_MESON(AntiBsMesonZero);
   ADD_MESON(AntiDMesonZero);
   ADD_MESON(AntiKaonZero);
   ADD_MESON(BcMesonMinus);
   ADD_MESON(BcMesonPlus);
   ADD_MESON(BMesonMinus);
   ADD_MESON(BMesonPlus);
   ADD_MESON(BMesonZero);
   ADD_MESON(BsMesonZero);
   ADD_MESON(DMesonMinus);
   ADD_MESON(DMesonPlus);
   ADD_MESON(DMesonZero);
   ADD_MESON(DsMesonMinus);
   ADD_MESON(DsMesonPlus);
   ADD_MESON(Eta);
   ADD_MESON(Etac);
   ADD_MESON(EtaPrime);
   ADD_MESON(JPsi);
   ADD_MESON(KaonMinus);
   ADD_MESON(KaonPlus);
   ADD_MESON(KaonZero);
   ADD_MESON(KaonZeroLong);
   ADD_MESON(KaonZeroShort);
   // ADD_MESON(MesonConstructor);
   ADD_MESON(PionMinus);
   ADD_MESON(PionPlus);
   ADD_MESON(PionZero);
   ADD_MESON(Upsilon);
}
