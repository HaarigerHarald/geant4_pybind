#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ChargedGeantino.hh>
#include <G4Gamma.hh>
#include <G4Geantino.hh>
#include <G4OpticalPhoton.hh>
#include <G4PhononLong.hh>
#include <G4PhononTransFast.hh>
#include <G4PhononTransSlow.hh>
#include <G4UnknownParticle.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

#define ADD_BOSON(name, sname)                                                                       \
   py::class_<name, G4ParticleDefinition, py::nodelete>(m, #name)                                    \
      .def_static("Definition", &name::Definition, py::return_value_policy::reference)               \
      .def_static(#sname "Definition", &name::sname##Definition, py::return_value_policy::reference) \
      .def_static(#sname, &name::sname, py::return_value_policy::reference)

#define ADD_BOSON_REDUCED(name, sname)                                                 \
   py::class_<name, G4ParticleDefinition, py::nodelete>(m, #name)                      \
      .def_static("Definition", &name::Definition, py::return_value_policy::reference) \
      .def_static(#sname "Definition", &name::sname##Definition, py::return_value_policy::reference)

void export_G4Bosons(py::module &m)
{
   ADD_BOSON(G4ChargedGeantino, ChargedGeantino);
   ADD_BOSON(G4Gamma, Gamma);
   ADD_BOSON(G4Geantino, Geantino);
   ADD_BOSON(G4OpticalPhoton, OpticalPhoton);
   ADD_BOSON_REDUCED(G4PhononLong, Phonon);
   ADD_BOSON_REDUCED(G4PhononTransFast, Phonon);
   ADD_BOSON_REDUCED(G4PhononTransSlow, Phonon);
   ADD_BOSON(G4UnknownParticle, UnknownParticle);
}
