#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4AffineTransform.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4AffineTransform(py::module &m)
{
   py::class_<G4AffineTransform>(m, "G4AffineTransform")

      .def(py::init<>())
      .def(py::init<const G4ThreeVector &>(), py::arg("tlate"))
      .def(py::init<const G4RotationMatrix &>(), py::arg("rot"))
      .def(py::init<const G4RotationMatrix &, const G4ThreeVector &>(), py::arg("rot"), py::arg("tlate"))
      .def(py::init<const G4RotationMatrix *, const G4ThreeVector &>(), py::arg("rot"), py::arg("tlate"))
      .def("__copy__", [](const G4AffineTransform &self) { return G4AffineTransform(self); })
      .def("__deepcopy__", [](const G4AffineTransform &self, py::dict) { return G4AffineTransform(self); })
      .def(py::self * py::self)
      .def(py::self *= py::self)
      .def("Product", &G4AffineTransform::Product, py::arg("tf1"), py::arg("tf2"))
      .def("InverseProduct", &G4AffineTransform::InverseProduct, py::arg("tf1"), py::arg("tf2"))
      .def("TransformPoint", &G4AffineTransform::TransformPoint, py::arg("vec"))
      .def("InverseTransformPoint", &G4AffineTransform::InverseTransformPoint, py::arg("vec"))
      .def("TransformAxis", &G4AffineTransform::TransformAxis, py::arg("axis"))
      .def("InverseTransformAxis", &G4AffineTransform::InverseTransformAxis, py::arg("axis"))
      .def("ApplyPointTransform", &G4AffineTransform::ApplyPointTransform, py::arg("vec"))
      .def("ApplyAxisTransform", &G4AffineTransform::ApplyAxisTransform, py::arg("axis"))
      .def("Inverse", &G4AffineTransform::Inverse)
      .def("Invert", &G4AffineTransform::Invert)
      .def(py::self += G4ThreeVector())
      .def(py::self -= G4ThreeVector())
      .def(py::self == py::self)
      .def(py::self != py::self)
      .def("__getitem__", &G4AffineTransform::operator[], py::is_operator())
      .def("IsRotated", &G4AffineTransform::IsRotated)
      .def("IsTranslated", &G4AffineTransform::IsTranslated)
      .def("NetRotation", &G4AffineTransform::NetRotation)
      .def("InverseNetRotation", &G4AffineTransform::InverseNetRotation)
      .def("NetTranslation", &G4AffineTransform::NetTranslation)
      .def("InverseNetTranslation", &G4AffineTransform::InverseNetTranslation)
      .def("SetNetRotation", &G4AffineTransform::SetNetRotation, py::arg("rot"))
      .def("SetNetTranslation", &G4AffineTransform::SetNetTranslation, py::arg("tlate"));

   py::implicitly_convertible<G4AffineTransform, G4Transform3D>();
}