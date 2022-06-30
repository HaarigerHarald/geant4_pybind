#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4AtomicShells.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4AtomicShells(py::module &m)
{
   py::class_<G4AtomicShells>(m, "G4AtomicShells")

      .def_static("GetBindingEnergy", &G4AtomicShells::GetBindingEnergy, py::arg("Z"), py::arg("SubshellNb"))
      .def_static("GetNumberOfElectrons", &G4AtomicShells::GetNumberOfElectrons, py::arg("Z"), py::arg("SubshellNb"))
      .def_static("GetNumberOfFreeElectrons", &G4AtomicShells::GetNumberOfFreeElectrons, py::arg("Z"), py::arg("th"))
      .def_static("GetNumberOfShells", &G4AtomicShells::GetNumberOfShells, py::arg("Z"))
      .def_static("GetTotalBindingEnergy", &G4AtomicShells::GetTotalBindingEnergy, py::arg("Z"));
}
