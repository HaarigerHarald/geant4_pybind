#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4AdjointAlpha.hh>
#include <G4AdjointDeuteron.hh>
#include <G4AdjointElectron.hh>
#include <G4AdjointElectronFI.hh>
#include <G4AdjointGamma.hh>
#include <G4AdjointGenericIon.hh>
#include <G4AdjointHe3.hh>
#include <G4AdjointIons.hh>
#include <G4AdjointPositron.hh>
#include <G4AdjointProton.hh>
#include <G4AdjointTriton.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

#define ADD_ADJOINT(name, sname)                                                                     \
   py::class_<name, G4ParticleDefinition, py::nodelete>(m, #name)                                    \
      .def_static("Definition", &name::Definition, py::return_value_policy::reference)               \
      .def_static(#sname "Definition", &name::sname##Definition, py::return_value_policy::reference) \
      .def_static(#sname, &name::sname, py::return_value_policy::reference)

void export_G4Adjoint(py::module &m)
{
   ADD_ADJOINT(G4AdjointAlpha, Alpha);
   ADD_ADJOINT(G4AdjointDeuteron, Deuteron);
   ADD_ADJOINT(G4AdjointElectron, AdjointElectron);
   ADD_ADJOINT(G4AdjointElectronFI, AdjointElectronFI);
   ADD_ADJOINT(G4AdjointGamma, AdjointGamma);
   ADD_ADJOINT(G4AdjointGenericIon, GenericIon);
   ADD_ADJOINT(G4AdjointHe3, He3);
   // ADD_ADJOINT(G4AdjointIons, G4AdjointIons);
   ADD_ADJOINT(G4AdjointPositron, AdjointPositron);
   ADD_ADJOINT(G4AdjointProton, AdjointProton);
   ADD_ADJOINT(G4AdjointTriton, Triton);
}
