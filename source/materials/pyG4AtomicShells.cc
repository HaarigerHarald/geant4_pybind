#include <pybind11/pybind11.h>

#include <G4AtomicShells.hh>

#include "OpaqueTypes.hh"
#include "typecast.hh"

namespace py = pybind11;

void export_G4AtomicShells(py::module &m)
{
   py::class_<G4AtomicShells, std::unique_ptr<G4AtomicShells>>(m, "G4AtomicShells",
                                                               "Atomic subshell binding energy table")

      .def_static("GetNumberOfShells", &G4AtomicShells::GetNumberOfShells)
      .def_static("GetNumberOfElectrons", &G4AtomicShells::GetNumberOfElectrons)
      .def_static("GetNumberOfFreeElectrons", &G4AtomicShells::GetNumberOfFreeElectrons)
      .def_static("GetBindingEnergy", &G4AtomicShells::GetBindingEnergy)
      .def_static("GetTotalBindingEnergy", &G4AtomicShells::GetTotalBindingEnergy);
}
