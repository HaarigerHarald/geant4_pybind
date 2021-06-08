#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4GeometryTolerance.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4GeometryTolerance(py::module &m)
{
   py::class_<G4GeometryTolerance, py::nodelete>(m, "G4GeometryTolerance")
      .def_static("GetInstance", &G4GeometryTolerance::GetInstance, py::return_value_policy::reference)
      .def("GetSurfaceTolerance", &G4GeometryTolerance::GetSurfaceTolerance)
      .def("GetAngularTolerance", &G4GeometryTolerance::GetAngularTolerance)
      .def("GetRadialTolerance", &G4GeometryTolerance::GetRadialTolerance);
}