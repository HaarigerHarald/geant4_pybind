#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ProcessType.hh>
#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4ProcessType(py::module &m)
{
   py::enum_<G4ProcessType>(m, "G4ProcessType")
      .value("fNotDefined", fNotDefined)
      .value("fTransportation", fTransportation)
      .value("fElectromagnetic", fElectromagnetic)
      .value("fOptical", fOptical)
      .value("fHadronic", fHadronic)
      .value("fPhotolepton_hadron", fPhotolepton_hadron)
      .value("fDecay", fDecay)
      .value("fGeneral", fGeneral)
      .value("fParameterisation", fParameterisation)
      .value("fUserDefined", fUserDefined)
      .export_values();
}
