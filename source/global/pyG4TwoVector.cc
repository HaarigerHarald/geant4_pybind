#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4TwoVector.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4TwoVector(py::module &m)
{
   py::class_<G4TwoVector>(m, "G4TwoVector", "general 2-vector")

      .def(py::init<>())
      .def(py::init<G4double>())
      .def(py::init<G4double, G4double>())
      .def(py::init<const G4TwoVector &>())

      .def_property("x", &G4TwoVector::x, &G4TwoVector::setX)
      .def_property("y", &G4TwoVector::y, &G4TwoVector::setY)

      .def("set", &G4TwoVector::set)
      .def("phi", &G4TwoVector::phi)
      .def("mag", &G4TwoVector::mag)
      .def("mag2", &G4TwoVector::mag2)
      .def("r", &G4TwoVector::r)
      .def("setPhi", &G4TwoVector::setPhi)
      .def("setMag", &G4TwoVector::setMag)
      .def("setR", &G4TwoVector::setR)
      .def("setPolar", &G4TwoVector::setPolar)
      .def("howNear", &G4TwoVector::howNear)
      .def("isNear", &G4TwoVector::isNear, py::arg("p"),
           py::arg("tolerance") = G4TwoVector::ZMpvToleranceTicks * 2.22045e-16)

      .def("howParallel", &G4TwoVector::howParallel)
      .def("isParallel", &G4TwoVector::isParallel, py::arg("p"),
           py::arg("tolerance") = G4TwoVector::ZMpvToleranceTicks * 2.22045e-16)

      .def("howOrthogonal", &G4TwoVector::howOrthogonal)
      .def("isOrthogonal", &G4TwoVector::isOrthogonal, py::arg("p"),
           py::arg("tolerance") = G4TwoVector::ZMpvToleranceTicks * 2.22045e-16)

      .def("unit", &G4TwoVector::unit)
      .def("orthogonal", &G4TwoVector::orthogonal)
      .def("dot", &G4TwoVector::dot)
      .def("angle", &G4TwoVector::angle)
      .def("rotate", &G4TwoVector::rotate)

      .def(
         "__str__",
         [](const G4TwoVector &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator())

      .def(py::self == py::self)
      .def(py::self != py::self)
      .def(py::self += py::self)
      .def(py::self -= py::self)
      .def(py::self - py::self)
      .def(py::self + py::self)
      .def(py::self * py::self)
      .def(py::self * G4double())
      .def(py::self / G4double())
      .def(G4double() * py::self)
      .def(py::self *= G4double())
      .def(py::self > py::self)
      .def(py::self < py::self)
      .def(py::self >= py::self)
      .def(py::self <= py::self);
}
