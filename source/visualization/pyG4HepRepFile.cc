#include <pybind11/pybind11.h>

#include <G4HepRepFile.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

void export_G4HepRepFile(py::module &m)
{
   py::class_<G4HepRepFile, G4VGraphicsSystem, owntrans_ptr<G4HepRepFile>>(m, "G4HepRepFile",
                                                                           "HepRep(File) visualization module");
}
