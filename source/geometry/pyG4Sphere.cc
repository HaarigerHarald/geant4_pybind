#include <pybind11/pybind11.h>

#include <G4Sphere.hh>

#include <limits>

#include "typecast.hh"

namespace py = pybind11;

void export_G4Sphere(py::module &m)
{
   py::class_<G4Sphere, G4VSolid, std::unique_ptr<G4Sphere, py::nodelete>>(m, "G4Sphere", "Sphere solid class")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double, G4double>())

      .def("GetInsideRadius", &G4Sphere::GetInsideRadius)
      .def("GetOuterRadius", &G4Sphere::GetOuterRadius)
      .def("GetStartPhiAngle", &G4Sphere::GetStartPhiAngle)
      .def("GetDeltaPhiAngle", &G4Sphere::GetDeltaPhiAngle)
      .def("GetStartThetaAngle", &G4Sphere::GetStartThetaAngle)
      .def("GetDeltaThetaAngle", &G4Sphere::GetDeltaThetaAngle)
      .def("SetInsideRadius", &G4Sphere::SetInsideRadius)
      .def("SetOuterRadius", &G4Sphere::SetOuterRadius)
      .def("SetStartPhiAngle", &G4Sphere::SetStartPhiAngle, py::arg("newSPhi"), py::arg("compute") = true)
      .def("SetDeltaPhiAngle", &G4Sphere::SetDeltaPhiAngle)
      .def("SetStartThetaAngle", &G4Sphere::SetStartThetaAngle)
      .def("SetDeltaThetaAngle", &G4Sphere::SetDeltaThetaAngle)

      .def("__str__", [](const G4Sphere &self) {
         std::stringstream ss;
         ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
         return ss.str();
      });
}
