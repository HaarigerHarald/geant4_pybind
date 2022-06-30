#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4AtomicShells_XDB_EADL.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4AtomicShells_XDB_EADL(py::module &m)
{
   py::class_<G4AtomicShells_XDB_EADL>(m, "G4AtomicShells_XDB_EADL")

      .def_static("GetBindingEnergy", &G4AtomicShells_XDB_EADL::GetBindingEnergy, py::arg("Z"), py::arg("SubshellNb"))
      .def_static("GetNumberOfElectrons", &G4AtomicShells_XDB_EADL::GetNumberOfElectrons, py::arg("Z"),
                  py::arg("SubshellNb"))
      .def_static("GetNumberOfFreeElectrons", &G4AtomicShells_XDB_EADL::GetNumberOfFreeElectrons, py::arg("Z"),
                  py::arg("th"))
      .def_static("GetNumberOfShells", &G4AtomicShells_XDB_EADL::GetNumberOfShells, py::arg("Z"))
      .def_static("GetTotalBindingEnergy", &G4AtomicShells_XDB_EADL::GetTotalBindingEnergy, py::arg("Z"));
}
