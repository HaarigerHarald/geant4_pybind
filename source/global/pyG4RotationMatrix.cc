#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include <G4RotationMatrix.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4RotationMatrix(py::module &m)
{
   py::class_<G4RotationMatrix>(m, "G4RotationMatrix", "rotation matrix")

      .def(py::init<>(), "Default contructor gives a unit matrix")
      .def(py::init<const G4RotationMatrix &>())

      .def_property_readonly("xx", &G4RotationMatrix::xx)
      .def_property_readonly("xy", &G4RotationMatrix::xy)
      .def_property_readonly("xz", &G4RotationMatrix::xz)
      .def_property_readonly("yx", &G4RotationMatrix::yx)
      .def_property_readonly("yy", &G4RotationMatrix::yy)
      .def_property_readonly("yz", &G4RotationMatrix::yz)
      .def_property_readonly("zx", &G4RotationMatrix::zx)
      .def_property_readonly("zy", &G4RotationMatrix::zy)
      .def_property_readonly("zz", &G4RotationMatrix::zz)
      .def_readonly_static("IDENTITY", &G4RotationMatrix::IDENTITY)

      .def("colX", &G4RotationMatrix::colX)
      .def("colY", &G4RotationMatrix::colY)
      .def("colZ", &G4RotationMatrix::colZ)
      .def("rowX", &G4RotationMatrix::rowX)
      .def("rowY", &G4RotationMatrix::rowY)
      .def("rowZ", &G4RotationMatrix::rowZ)
      .def("getPhi", &G4RotationMatrix::getPhi)
      .def("getTheta", &G4RotationMatrix::getTheta)
      .def("getPsi", &G4RotationMatrix::getPsi)
      .def("phi", &G4RotationMatrix::phi)
      .def("theta", &G4RotationMatrix::theta)
      .def("psi", &G4RotationMatrix::psi)
      .def("getDelta", &G4RotationMatrix::getDelta)
      .def("getAxis", &G4RotationMatrix::getAxis)
      .def("delta", &G4RotationMatrix::axis)
      .def("axis", &G4RotationMatrix::delta)
      .def("phiX", &G4RotationMatrix::phiX)
      .def("phiY", &G4RotationMatrix::phiY)
      .def("phiZ", &G4RotationMatrix::phiZ)
      .def("thetaX", &G4RotationMatrix::thetaX)
      .def("thetaY", &G4RotationMatrix::thetaY)
      .def("thetaZ", &G4RotationMatrix::thetaZ)
      .def("setPhi", &G4RotationMatrix::setPhi)
      .def("setTheta", &G4RotationMatrix::setTheta)
      .def("setPsi", &G4RotationMatrix::setPsi)
      .def("setAxis", &G4RotationMatrix::setAxis)
      .def("setDelta", &G4RotationMatrix::setDelta)
      .def("isIdentity", &G4RotationMatrix::isIdentity)
      .def("rotateX", &G4RotationMatrix::rotateX, py::return_value_policy::reference)
      .def("rotateY", &G4RotationMatrix::rotateY, py::return_value_policy::reference)
      .def("rotateZ", &G4RotationMatrix::rotateZ, py::return_value_policy::reference)

      .def("rotate", py::overload_cast<G4double, const G4ThreeVector &>(&G4RotationMatrix::rotate),
           py::return_value_policy::reference)

      .def("rotate", py::overload_cast<G4double, const G4ThreeVector *>(&G4RotationMatrix::rotate),
           py::return_value_policy::reference)

      .def("rotateAxes", &G4RotationMatrix::rotateAxes, py::return_value_policy::reference)
      .def("inverse", &G4RotationMatrix::inverse)
      .def("invert", &G4RotationMatrix::invert, py::return_value_policy::reference);

   // .def(
   //    "__str__",
   //    [](const G4RotationMatrix &self) {
   //       std::stringstream ss;
   //       ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
   //       return ss.str();
   //    },
   //    py::is_operator())

   // .def(py::self == py::self)
   // .def(py::self != py::self)
   // .def(py::self > py::self)
   // .def(py::self < py::self)
   // .def(py::self >= py::self)
   // .def(py::self <= py::self)
   // .def(py::self * py::self)
   // .def(py::self * G4ThreeVector())
   // .def(py::self *= py::self);
}
