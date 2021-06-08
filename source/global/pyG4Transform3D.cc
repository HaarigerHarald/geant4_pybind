#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4RotationMatrix.hh>
#include <G4ThreeVector.hh>
#include <G4Transform3D.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Transform3D(py::module &m)
{
   py::class_<G4Transform3D>(m, "G4Transform3D", "geometrical 3D transformation")

      .def(py::init<>())
      .def(py::init<const G4RotationMatrix &, const G4ThreeVector &>())
      .def(py::init<const G4Transform3D &>())

      .def_property_readonly("xx", &G4Transform3D::xx)
      .def_property_readonly("xy", &G4Transform3D::xy)
      .def_property_readonly("xz", &G4Transform3D::xz)
      .def_property_readonly("yx", &G4Transform3D::yx)
      .def_property_readonly("yy", &G4Transform3D::yy)
      .def_property_readonly("yz", &G4Transform3D::yz)
      .def_property_readonly("zx", &G4Transform3D::zx)
      .def_property_readonly("zy", &G4Transform3D::zy)
      .def_property_readonly("zz", &G4Transform3D::zz)
      .def_property_readonly("dx", &G4Transform3D::dx)
      .def_property_readonly("dy", &G4Transform3D::dy)
      .def_property_readonly("dz", &G4Transform3D::dz)
      .def_readonly_static("Identity", &G4Transform3D::Identity)

      .def("inverse", &G4Transform3D::inverse)
      .def("getRotation", &G4Transform3D::getRotation)
      .def("getTranslation", &G4Transform3D::getTranslation)

      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self * py::self);
}
