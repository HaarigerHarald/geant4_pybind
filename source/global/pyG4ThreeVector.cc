#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4RotationMatrix.hh>
#include <G4ThreeVector.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4ThreeVector(py::module &m)
{
   py::class_<G4ThreeVector>(m, "G4ThreeVector", "general 3-vector")

      .def(py::init<>())
      .def(py::init<G4double>())
      .def(py::init<G4double, G4double>())
      .def(py::init<G4double, G4double, G4double>())
      .def(py::init<const G4ThreeVector &>())

      .def_property("x", &G4ThreeVector::x, &G4ThreeVector::setX)
      .def_property("y", &G4ThreeVector::y, &G4ThreeVector::setY)
      .def_property("z", &G4ThreeVector::z, &G4ThreeVector::setZ)
      //.def_property("phi", &G4ThreeVector::phi, &G4ThreeVector::setPhi)
      //.def_property("theta", &G4ThreeVector::getTheta, &G4ThreeVector::setTheta)
      //.def_property("mag", &G4ThreeVector::mag, &G4ThreeVector::setMag)

      .def("set", &G4ThreeVector::set)
      .def("phi", &G4ThreeVector::phi)
      .def("mag", &G4ThreeVector::mag)
      .def("mag2", &G4ThreeVector::mag2)
      .def("setPhi", &G4ThreeVector::setPhi)
      .def("setTheta", &G4ThreeVector::setTheta)
      .def("setMag", &G4ThreeVector::setMag)
      .def("setPerp", &G4ThreeVector::setPerp)
      .def("setCylTheta", &G4ThreeVector::setCylTheta)
      .def("howNear", &G4ThreeVector::howNear)
      .def("deltaR", &G4ThreeVector::deltaR)
      .def("unit", &G4ThreeVector::unit)
      .def("orthogonal", &G4ThreeVector::orthogonal)
      .def("dot", &G4ThreeVector::dot)
      .def("cross", &G4ThreeVector::cross)
      .def("pseudoRapidity", &G4ThreeVector::pseudoRapidity)
      .def("setEta", &G4ThreeVector::setEta)
      .def("setCylEta", &G4ThreeVector::setCylEta)
      .def("setRThetaPhi", &G4ThreeVector::setRThetaPhi)
      .def("setREtaPhi", &G4ThreeVector::setREtaPhi)
      .def("setRhoPhiZ", &G4ThreeVector::setRhoPhiZ)
      .def("setRhoPhiEta", &G4ThreeVector::setRhoPhiEta)
      .def("getX", &G4ThreeVector::getX)
      .def("getY", &G4ThreeVector::getY)
      .def("getZ", &G4ThreeVector::getZ)
      .def("getR", &G4ThreeVector::getR)
      .def("getTheta", &G4ThreeVector::getTheta)
      .def("getPhi", &G4ThreeVector::getPhi)
      .def("r", &G4ThreeVector::r)
      .def("rho", &G4ThreeVector::rho)
      .def("getRho", &G4ThreeVector::getRho)
      .def("getEta", &G4ThreeVector::getEta)
      .def("setR", &G4ThreeVector::setR)
      .def("setRho", &G4ThreeVector::setRho)
      .def("compare", &G4ThreeVector::compare)
      .def("diff2", &G4ThreeVector::diff2)
      .def_static("setTolerance", &G4ThreeVector::setTolerance)
      .def_static("getTolerance", &G4ThreeVector::getTolerance)
      .def("isNear", &G4ThreeVector::isNear, py::arg("v"),
           py::arg("tolerance") = G4ThreeVector::ToleranceTicks * 2.22045e-16)

      .def("howParallel", &G4ThreeVector::howParallel)
      .def("isParallel", &G4ThreeVector::isParallel, py::arg("v"),
           py::arg("tolerance") = G4ThreeVector::ToleranceTicks * 2.22045e-16)

      .def("howOrthogonal", &G4ThreeVector::howOrthogonal)
      .def("isOrthogonal", &G4ThreeVector::isOrthogonal, py::arg("v"),
           py::arg("tolerance") = G4ThreeVector::ToleranceTicks * 2.22045e-16)

      .def("howParallel", &G4ThreeVector::howParallel)
      .def("howOrthogonal", &G4ThreeVector::howOrthogonal)
      .def("beta", &G4ThreeVector::beta)
      .def("gamma", &G4ThreeVector::gamma)
      .def("deltaPhi", &G4ThreeVector::deltaPhi)
      .def("coLinearRapidity", &G4ThreeVector::coLinearRapidity)
      .def("theta", py::overload_cast<const G4ThreeVector &>(&G4ThreeVector::theta, py::const_))
      .def("theta", py::overload_cast<const G4ThreeVector &>(&G4ThreeVector::theta, py::const_))

      .def("cosTheta", py::overload_cast<>(&G4ThreeVector::cosTheta, py::const_))
      .def("cosTheta", py::overload_cast<const G4ThreeVector &>(&G4ThreeVector::cos2Theta, py::const_))

      .def("cos2Theta", py::overload_cast<>(&G4ThreeVector::cosTheta, py::const_))
      .def("cos2Theta", py::overload_cast<const G4ThreeVector &>(&G4ThreeVector::cos2Theta, py::const_))

      .def("perp", py::overload_cast<>(&G4ThreeVector::perp, py::const_))
      .def("perp", py::overload_cast<const G4ThreeVector &>(&G4ThreeVector::perp, py::const_))

      .def("perp2", py::overload_cast<>(&G4ThreeVector::perp2, py::const_))
      .def("perp2", py::overload_cast<const G4ThreeVector &>(&G4ThreeVector::perp2, py::const_))

      .def("angle", py::overload_cast<>(&G4ThreeVector::angle, py::const_))
      .def("angle", py::overload_cast<const G4ThreeVector &>(&G4ThreeVector::perp2, py::const_))

      .def("eta", py::overload_cast<>(&G4ThreeVector::eta, py::const_))
      .def("eta", py::overload_cast<const G4ThreeVector &>(&G4ThreeVector::eta, py::const_))

      .def("project", py::overload_cast<>(&G4ThreeVector::project, py::const_))
      .def("project", py::overload_cast<const G4ThreeVector &>(&G4ThreeVector::project, py::const_))

      .def("perpPart", py::overload_cast<>(&G4ThreeVector::perpPart, py::const_))
      .def("perpPart", py::overload_cast<const G4ThreeVector &>(&G4ThreeVector::perpPart, py::const_))

      .def("rapidity", py::overload_cast<>(&G4ThreeVector::rapidity, py::const_))
      .def("rapidity", py::overload_cast<const G4ThreeVector &>(&G4ThreeVector::rapidity, py::const_))

      .def("polarAngle", py::overload_cast<const G4ThreeVector &>(&G4ThreeVector::polarAngle, py::const_))
      .def("polarAngle",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4ThreeVector::polarAngle, py::const_))

      .def("azimAngle", py::overload_cast<const G4ThreeVector &>(&G4ThreeVector::azimAngle, py::const_))
      .def("azimAngle",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4ThreeVector::azimAngle, py::const_))

      .def("rotateX", &G4ThreeVector::rotateX, py::return_value_policy::reference)
      .def("rotateY", &G4ThreeVector::rotateY, py::return_value_policy::reference)

      .def("rotateZ", &G4ThreeVector::rotateZ, py::return_value_policy::reference)
      .def("rotateUz", &G4ThreeVector::rotateUz, py::return_value_policy::reference)
      .def("transform", &G4ThreeVector::transform, py::return_value_policy::reference)
      .def("rotate", py::overload_cast<G4double, const G4ThreeVector &>(&G4ThreeVector::rotate),
           py::return_value_policy::reference)

      .def("rotate", py::overload_cast<const G4ThreeVector &, G4double>(&G4ThreeVector::rotate),
           py::return_value_policy::reference)

      .def("rotate", py::overload_cast<G4double, G4double, G4double>(&G4ThreeVector::rotate),
           py::return_value_policy::reference)
      // operators
      .def("__str__",
           [](const G4ThreeVector &self) {
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
      .def(py::self /= G4double())
      .def(py::self > py::self)
      .def(py::self < py::self)
      .def(py::self >= py::self)
      .def(py::self <= py::self);
}
