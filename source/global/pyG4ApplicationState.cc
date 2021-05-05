#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ApplicationState.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4ApplicationState(py::module &m)
{
   py::enum_<G4ApplicationState>(m, "G4ApplicationState")
      .value("G4State_PreInit", G4State_PreInit)
      .value("G4State_Init", G4State_Init)
      .value("G4State_Idle", G4State_Idle)
      .value("G4State_GeomClosed", G4State_GeomClosed)
      .value("G4State_EventProc", G4State_EventProc)
      .value("G4State_Quit", G4State_Quit)
      .value("G4State_Abort", G4State_Abort)
      .export_values();
}
