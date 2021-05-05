#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4UImanager(py::module &);
void export_G4UIcommandTree(py::module &);
void export_G4UIcommand(py::module &);
void export_G4UIparameter(py::module &);
void export_G4UIdirectory(py::module &);
void export_G4UImessenger(py::module &);
void export_G4UIcmdWithAString(py::module &);
void export_G4UIcmdWithADoubleAndUnit(py::module &);
void export_G4UIcmdWithADouble(py::module &);
void export_G4UIcmdWith3Vector(py::module &);
void export_G4UIcmdWith3VectorAndUnit(py::module &);
void export_G4UIcmdWithABool(py::module &);
void export_G4UIcmdWithALongInt(py::module &);
void export_G4UIcmdWithAnInteger(py::module &);
void export_G4UIcmdWithoutParameter(py::module &);
void export_G4UIcommandStatus(py::module &);
void export_G4GenericMessenger(py::module &);

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
   export_G4UIcmdWithADouble(m);
   export_G4UIcmdWith3Vector(m);
   export_G4UIcmdWith3VectorAndUnit(m);
   export_G4UIcmdWithABool(m);
   export_G4UIcmdWithALongInt(m);
   export_G4UIcmdWithAnInteger(m);
   export_G4UIcmdWithoutParameter(m);
   export_G4UIcommandStatus(m);
   export_G4GenericMessenger(m);
}
