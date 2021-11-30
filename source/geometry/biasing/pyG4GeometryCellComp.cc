#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4GeometryCellComp.hh>
#include <G4GeometryCell.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4GeometryCellComp(py::module &m)
{
   py::class_<G4GeometryCellComp>(m, "G4GeometryCellComp")

      .def(py::init<>())
      .def("__copy__", [](const G4GeometryCellComp &self) { return G4GeometryCellComp(self); })
      .def("__deepcopy__", [](const G4GeometryCellComp &self, py::dict) { return G4GeometryCellComp(self); })
      .def("__call__", &G4GeometryCellComp::operator(), py::arg("g1"), py::arg("g2"), py::is_operator());
}
