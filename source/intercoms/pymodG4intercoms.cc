#include <pybind11/pybind11.h>

#include "typecast.hh"

namespace py = pybind11;

void export_G4UImanager(py::module &);
void export_G4UIcommandTree(py::module &);
void export_G4UIcommand(py::module &);
void export_G4UIparameter(py::module &);
void export_G4UIdirectory(py::module &);
void export_G4UImessenger(py::module &);
void export_G4UIcmdWithAString(py::module &);
void export_G4UIcmdWithADoubleAndUnit(py::module &);

void export_modG4intercoms(py::module &m)
{
   export_G4UImanager(m);
   export_G4UIcommandTree(m);
   export_G4UIcommand(m);
   export_G4UIparameter(m);
   export_G4UIdirectory(m);
   export_G4UImessenger(m);
   export_G4UIcmdWithAString(m);
   export_G4UIcmdWithADoubleAndUnit(m);
}
