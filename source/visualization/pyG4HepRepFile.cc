#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4HepRepFile.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4HepRepFile(py::module &m)
{
   py::class_<G4HepRepFile, G4VGraphicsSystem>(m, "G4HepRepFile", "HepRep(File) visualization module");
}
