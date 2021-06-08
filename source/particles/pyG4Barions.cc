#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4AntiLambda.hh>
#include <G4AntiLambdab.hh>
#include <G4AntiLambdacPlus.hh>
#include <G4AntiNeutron.hh>
#include <G4AntiOmegabMinus.hh>
#include <G4AntiOmegacZero.hh>
#include <G4AntiOmegaMinus.hh>
#include <G4AntiProton.hh>
#include <G4AntiSigmabMinus.hh>
#include <G4AntiSigmabPlus.hh>
#include <G4AntiSigmabZero.hh>
#include <G4AntiSigmacPlus.hh>
#include <G4AntiSigmacPlusPlus.hh>
#include <G4AntiSigmacZero.hh>
#include <G4AntiSigmaMinus.hh>
#include <G4AntiSigmaPlus.hh>
#include <G4AntiSigmaZero.hh>
#include <G4AntiXibMinus.hh>
#include <G4AntiXibZero.hh>
#include <G4AntiXicPlus.hh>
#include <G4AntiXicZero.hh>
#include <G4AntiXiMinus.hh>
#include <G4AntiXiZero.hh>
#include <G4Lambda.hh>
#include <G4Lambdab.hh>
#include <G4LambdacPlus.hh>
#include <G4Neutron.hh>
#include <G4OmegabMinus.hh>
#include <G4OmegacZero.hh>
#include <G4OmegaMinus.hh>
#include <G4Proton.hh>
#include <G4SigmabMinus.hh>
#include <G4SigmabPlus.hh>
#include <G4SigmabZero.hh>
#include <G4SigmacPlus.hh>
#include <G4SigmacPlusPlus.hh>
#include <G4SigmacZero.hh>
#include <G4SigmaMinus.hh>
#include <G4SigmaPlus.hh>
#include <G4SigmaZero.hh>
#include <G4XibMinus.hh>
#include <G4XibZero.hh>
#include <G4XicPlus.hh>
#include <G4XicZero.hh>
#include <G4XiMinus.hh>
#include <G4XiZero.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

#define ADD_BARION(name)                                                                               \
   py::class_<G4##name, G4ParticleDefinition, py::nodelete>(m, "G4" #name)                             \
      .def_static("Definition", &G4##name::Definition, py::return_value_policy::reference)             \
      .def_static(#name "Definition", &G4##name::name##Definition, py::return_value_policy::reference) \
      .def_static(#name, &G4##name::name, py::return_value_policy::reference)

void export_G4Barions(py::module &m)
{
   ADD_BARION(AntiLambda);
   ADD_BARION(AntiLambdab);
   ADD_BARION(AntiLambdacPlus);
   ADD_BARION(AntiNeutron);
   ADD_BARION(AntiOmegabMinus);
   ADD_BARION(AntiOmegacZero);
   ADD_BARION(AntiOmegaMinus);
   ADD_BARION(AntiProton);
   ADD_BARION(AntiSigmabMinus);
   ADD_BARION(AntiSigmabPlus);
   ADD_BARION(AntiSigmabZero);
   ADD_BARION(AntiSigmacPlus);
   ADD_BARION(AntiSigmacPlusPlus);
   ADD_BARION(AntiSigmacZero);
   ADD_BARION(AntiSigmaMinus);
   ADD_BARION(AntiSigmaPlus);
   ADD_BARION(AntiSigmaZero);
   ADD_BARION(AntiXibMinus);
   ADD_BARION(AntiXibZero);
   ADD_BARION(AntiXicPlus);
   ADD_BARION(AntiXicZero);
   ADD_BARION(AntiXiMinus);
   ADD_BARION(AntiXiZero);
   ADD_BARION(Lambda);
   ADD_BARION(Lambdab);
   ADD_BARION(LambdacPlus);
   ADD_BARION(Neutron);
   ADD_BARION(OmegabMinus);
   ADD_BARION(OmegacZero);
   ADD_BARION(OmegaMinus);
   ADD_BARION(Proton);
   ADD_BARION(SigmabMinus);
   ADD_BARION(SigmabPlus);
   ADD_BARION(SigmabZero);
   ADD_BARION(SigmacPlus);
   ADD_BARION(SigmacPlusPlus);
   ADD_BARION(SigmacZero);
   ADD_BARION(SigmaMinus);
   ADD_BARION(SigmaPlus);
   ADD_BARION(SigmaZero);
   ADD_BARION(XibMinus);
   ADD_BARION(XibZero);
   ADD_BARION(XicPlus);
   ADD_BARION(XicZero);
   ADD_BARION(XiMinus);
   ADD_BARION(XiZero);
}
