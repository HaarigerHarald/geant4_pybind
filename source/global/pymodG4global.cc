#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_globals(py::module &);
void export_geomdefs(py::module &);
void export_G4StateManager(py::module &);
void export_G4ApplicationState(py::module &);
void export_G4ThreeVector(py::module &);
void export_G4RotationMatrix(py::module &);
void export_G4Transform3D(py::module &);
void export_G4UnitsTable(py::module &);
void export_Randomize(py::module &);
void export_RandomEngines(py::module &);
void export_G4RandomDirection(py::module &);
void export_G4UserLimits(py::module &);
void export_G4Timer(py::module &);
void export_G4Version(py::module &);
void export_G4Exception(py::module &);
void export_G4ExceptionHandler(py::module &);
void export_G4ExceptionSeverity(py::module &);
void export_G4TwoVector(py::module &);
void export_G4GeometryTolerance(py::module &);
void export_G4SystemOfUnits(py::module &);
void export_G4PhysicalConstants(py::module &);
void export_G4StatAnalysis(py::module &);

void export_modG4global(py::module &m)
{
   export_geomdefs(m);
   export_G4StateManager(m);
   export_G4ApplicationState(m);
   export_G4ThreeVector(m);
   export_G4TwoVector(m);
   export_G4RotationMatrix(m);
   export_G4Transform3D(m);
   export_G4UnitsTable(m);
   export_RandomEngines(m);
   export_Randomize(m);
   export_G4RandomDirection(m);
   export_G4UserLimits(m);
   export_G4Timer(m);
   export_G4Version(m);
   export_G4Exception(m);
   export_G4ExceptionHandler(m);
   export_G4ExceptionSeverity(m);
   export_G4GeometryTolerance(m);
   export_G4SystemOfUnits(m);
   export_G4PhysicalConstants(m);
   export_G4StatAnalysis(m);
   export_globals(m);
}
