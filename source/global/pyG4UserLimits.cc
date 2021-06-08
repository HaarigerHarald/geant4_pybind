#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UserLimits.hh>
#include <G4Track.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4UserLimits(py::module &m)
{
   py::class_<G4UserLimits>(m, "G4UserLimits", "user step limitations")

      .def(py::init<G4double>())
      .def(py::init<G4double, G4double>())
      .def(py::init<G4double, G4double, G4double>())
      .def(py::init<G4double, G4double, G4double, G4double>())
      .def(py::init<G4double, G4double, G4double, G4double, G4double>())

      .def(py::init<const G4String &>())
      .def(py::init<const G4String &, G4double>())
      .def(py::init<const G4String &, G4double, G4double>())
      .def(py::init<const G4String &, G4double, G4double, G4double>())
      .def(py::init<const G4String &, G4double, G4double, G4double, G4double>())
      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double>())

      .def("GetUserMaxTrackLength", &G4UserLimits::GetUserMaxTrackLength)
      .def("GetUserMaxTime", &G4UserLimits::GetUserMaxTime)
      .def("GetUserMinEkine", &G4UserLimits::GetUserMinEkine)
      .def("GetUserMinRange", &G4UserLimits::GetUserMinRange)

      .def("SetMaxAllowedStep", &G4UserLimits::SetMaxAllowedStep)
      .def("SetUserMaxTrackLength", &G4UserLimits::SetUserMaxTrackLength)
      .def("SetUserMaxTime", &G4UserLimits::SetUserMaxTime)
      .def("SetUserMinEkine", &G4UserLimits::SetUserMinEkine)
      .def("SetUserMinRange", &G4UserLimits::SetUserMinRange)

      .def("GetType", &G4UserLimits::GetType, py::return_value_policy::reference_internal)
      .def("SetType", &G4UserLimits::SetType);
}
