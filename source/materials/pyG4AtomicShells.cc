#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4AtomicShells.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4AtomicShells(py::module &m)
{
   py::class_<G4AtomicShells>(m, "G4AtomicShells", "Atomic subshell binding energy table")

      .def_static("GetNumberOfShells", &G4AtomicShells::GetNumberOfShells)
      .def_static("GetNumberOfElectrons", &G4AtomicShells::GetNumberOfElectrons)
      .def_static("GetNumberOfFreeElectrons", &G4AtomicShells::GetNumberOfFreeElectrons)
      .def_static("GetBindingEnergy", &G4AtomicShells::GetBindingEnergy)
      .def_static("GetTotalBindingEnergy", &G4AtomicShells::GetTotalBindingEnergy);
}
