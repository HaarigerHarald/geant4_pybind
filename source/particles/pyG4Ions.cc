#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Ions.hh>
#include <G4DecayTable.hh>

#include <G4Alpha.hh>
#include <G4AntiAlpha.hh>
#include <G4AntiDeuteron.hh>
#include <G4AntiHe3.hh>
#include <G4AntiTriton.hh>
#include <G4Deuteron.hh>
#include <G4GenericIon.hh>
#include <G4GenericMuonicAtom.hh>
#include <G4He3.hh>
#include <G4IonConstructor.hh>
#include <G4Triton.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

#define ADD_ION(name)                                                                                  \
   py::class_<G4##name, G4Ions, py::nodelete>(m, "G4" #name)                                           \
      .def_static("Definition", &G4##name::Definition, py::return_value_policy::reference)             \
      .def_static(#name "Definition", &G4##name::name##Definition, py::return_value_policy::reference) \
      .def_static(#name, &G4##name::name, py::return_value_policy::reference)

void export_G4Ions(py::module &m)
{
   py::class_<G4Ions, G4ParticleDefinition, py::nodelete> g4Ions(m, "G4Ions");

   py::enum_<G4Ions::G4FloatLevelBase>(g4Ions, "G4FloatLevelBase")
      .value("no_Float", G4Ions::G4FloatLevelBase::no_Float)
      .value("plus_X", G4Ions::G4FloatLevelBase::plus_X)
      .value("plus_Y", G4Ions::G4FloatLevelBase::plus_Y)
      .value("plus_Z", G4Ions::G4FloatLevelBase::plus_Z)
      .value("plus_U", G4Ions::G4FloatLevelBase::plus_U)
      .value("plus_V", G4Ions::G4FloatLevelBase::plus_V)
      .value("plus_W", G4Ions::G4FloatLevelBase::plus_W)
      .value("plus_R", G4Ions::G4FloatLevelBase::plus_R)
      .value("plus_S", G4Ions::G4FloatLevelBase::plus_S)
      .value("plus_T", G4Ions::G4FloatLevelBase::plus_T)
      .value("plus_A", G4Ions::G4FloatLevelBase::plus_A)
      .value("plus_B", G4Ions::G4FloatLevelBase::plus_B)
      .value("plus_C", G4Ions::G4FloatLevelBase::plus_C)
      .value("plus_D", G4Ions::G4FloatLevelBase::plus_D)
      .value("plus_E", G4Ions::G4FloatLevelBase::plus_E);

   g4Ions
      .def(py::init<>([](const G4String &aName, G4double mass, G4double width, G4double charge, G4int iSpin,
                         G4int iParity, G4int iConjugation, G4int iIsospin, G4int iIsospin3, G4int gParity,
                         const G4String &pType, G4int lepton, G4int baryon, G4int encoding, G4bool stable,
                         G4double lifetime, py::disown_ptr<G4DecayTable> decaytable, G4bool shortlived,
                         const G4String &subType, G4int anti_encoding, G4double excitation, G4int isomer) {
              return new G4Ions(aName, mass, width, charge, iSpin, iParity, iConjugation, iIsospin, iIsospin3, gParity,
                                pType, lepton, baryon, encoding, stable, lifetime, decaytable, shortlived, subType,
                                anti_encoding, excitation, isomer);
           }),
           py::arg("aName"), py::arg("mass"), py::arg("width"), py::arg("charge"), py::arg("iSpin"), py::arg("iParity"),
           py::arg("iConjugation"), py::arg("iIsospin"), py::arg("iIsospin3"), py::arg("gParity"), py::arg("pType"),
           py::arg("lepton"), py::arg("baryon"), py::arg("encoding"), py::arg("stable"), py::arg("lifetime"),
           py::arg("decaytable"), py::arg("shortlived"), py::arg("subType") = "", py::arg("anti_encoding") = 0,
           py::arg("excitation") = 0.0, py::arg("isomer") = 0)

      .def("IonsDefinition", &G4Ions::IonsDefinition)
      .def("Ions", &G4Ions::Ions)
      .def("GetExcitationEnergy", &G4Ions::GetExcitationEnergy)
      .def("GetIsomerLevel", &G4Ions::GetIsomerLevel)
      .def("GetExcitationEnergy", &G4Ions::GetExcitationEnergy)
      .def("GetExcitationEnergy", &G4Ions::GetExcitationEnergy)

      .def_static("FloatLevelBase", py::overload_cast<char>(&G4Ions::FloatLevelBase))
      .def_static("FloatLevelBase", py::overload_cast<G4int>(&G4Ions::FloatLevelBase))
      .def_static("FloatLevelBaseChar", &G4Ions::FloatLevelBaseChar)

      .def("GetFloatLevelBase", &G4Ions::GetFloatLevelBase)
      .def("GetFloatLevelBaseIndex", &G4Ions::GetFloatLevelBaseIndex)
      .def("SetFloatLevelBase", py::overload_cast<G4Ions::G4FloatLevelBase>(&G4Ions::SetFloatLevelBase))
      .def("SetFloatLevelBase", py::overload_cast<char>(&G4Ions::SetFloatLevelBase))
      .def("SetFloatLevelBase", py::overload_cast<G4int>(&G4Ions::SetFloatLevelBase));

   ADD_ION(Alpha);
   ADD_ION(AntiAlpha);
   ADD_ION(AntiDeuteron);
   ADD_ION(AntiHe3);
   ADD_ION(AntiTriton);
   ADD_ION(Deuteron);
   ADD_ION(GenericIon);
   ADD_ION(GenericMuonicAtom);
   ADD_ION(He3);
   // ADD_ION(G4IonConstructor,IonConstructor );
   ADD_ION(Triton);
}
