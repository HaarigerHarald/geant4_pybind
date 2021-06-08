#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Para.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Para(py::module &m)
{
   py::class_<G4Para, G4VSolid, py::nodelete>(m, "G4Para", "Skewed box sold class")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double, G4double>())

      .def(py::init<>([](const G4String &pName, py::list pt) {
         if (pt.size() != 8) {
            py::pybind11_fail("array with length 8 expected");
         } else {
            auto arrPts = std::make_unique<G4ThreeVector[]>(8);
            for (size_t i = 0; i < pt.size(); i++) {
               arrPts[i] = pt[i].cast<G4ThreeVector>();
            }
            return G4Para(pName, arrPts.get());
         }
      }))

      .def("GetZHalfLength", &G4Para::GetZHalfLength)
      .def("GetSymAxis", &G4Para::GetSymAxis)
      .def("GetYHalfLength", &G4Para::GetYHalfLength)
      .def("GetXHalfLength", &G4Para::GetXHalfLength)
      .def("GetTanAlpha", &G4Para::GetTanAlpha)
      .def("SetXHalfLength", &G4Para::SetXHalfLength)
      .def("SetYHalfLength", &G4Para::SetYHalfLength)
      .def("SetZHalfLength", &G4Para::SetZHalfLength)
      .def("SetAlpha", &G4Para::SetAlpha)
      .def("SetTanAlpha", &G4Para::SetTanAlpha)
      .def("SetThetaAndPhi", &G4Para::SetThetaAndPhi)
      .def("SetAllParameters", &G4Para::SetAllParameters)

      .def("__str__",
           [](const G4Para &self) {
              std::stringstream ss;
              ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
              return ss.str();
           },
           py::is_operator());
}
