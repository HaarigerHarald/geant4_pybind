#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Step.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Step(py::module &m)
{
   py::class_<G4Step>(m, "G4Step", "step class")
      .def(py::init<>())
      .def(py::init<const G4Step &>())

      .def("GetTrack", &G4Step::GetTrack, py::return_value_policy::reference)
      .def("GetPreStepPoint", &G4Step::GetPreStepPoint, py::return_value_policy::reference_internal)
      .def("GetPostStepPoint", &G4Step::GetPostStepPoint, py::return_value_policy::reference_internal)
      .def("GetTotalEnergyDeposit", &G4Step::GetTotalEnergyDeposit)
      .def("GetStepLength", &G4Step::GetStepLength)
      .def("GetDeltaPosition", &G4Step::GetDeltaPosition)
      .def("GetDeltaTime", &G4Step::GetDeltaTime)
      .def("GetDeltaMomentum", &G4Step::GetDeltaMomentum)
      .def("GetDeltaEnergy", &G4Step::GetDeltaEnergy);
}
