#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4LogicalSurface.hh>
#include <G4SurfaceProperty.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4LogicalSurface(py::module &m)
{
   py::class_<G4LogicalSurface>(m, "G4LogicalSurface")

      .def("GetSurfaceProperty", &G4LogicalSurface::GetSurfaceProperty, py::return_value_policy::reference)
      .def("SetSurfaceProperty", &G4LogicalSurface::SetSurfaceProperty, py::arg("ptrSurfaceProperty"))
      .def("GetName", &G4LogicalSurface::GetName)
      .def("SetName", &G4LogicalSurface::SetName, py::arg("name"))
      //.def("GetTransitionRadiationSurface", &G4LogicalSurface::GetTransitionRadiationSurface,
      // py::return_value_policy::reference)

      //.def("SetTransitionRadiationSurface", &G4LogicalSurface::SetTransitionRadiationSurface, py::arg("trs"))
      .def(py::self == py::self)
      .def(py::self != py::self);
}
