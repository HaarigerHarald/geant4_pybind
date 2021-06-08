#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VProcess.hh>
#include <G4StepPoint.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4StepPoint(py::module &m)
{
   py::class_<G4StepPoint>(m, "G4StepPoint", "step point class")
      .def(py::init<>())
      .def(py::init<const G4StepPoint &>())

      .def("GetPosition", &G4StepPoint::GetPosition)
      .def("GetLocalTime", &G4StepPoint::GetLocalTime)
      .def("GetGlobalTime", &G4StepPoint::GetGlobalTime)
      .def("GetProperTime", &G4StepPoint::GetProperTime)
      .def("GetMomentumDirection", &G4StepPoint::GetMomentumDirection)
      .def("GetMomentum", &G4StepPoint::GetMomentum)
      .def("GetTotalEnergy", &G4StepPoint::GetTotalEnergy)
      .def("GetKineticEnergy", &G4StepPoint::GetKineticEnergy)
      .def("GetVelocity", &G4StepPoint::GetVelocity)
      .def("GetBeta", &G4StepPoint::GetBeta)
      .def("GetGamma", &G4StepPoint::GetGamma)
      .def("GetTouchable", &G4StepPoint::GetTouchable, py::return_value_policy::reference)
      .def("GetMaterial", &G4StepPoint::GetMaterial, py::return_value_policy::reference)
      .def("GetPolarization", &G4StepPoint::GetPolarization)
      .def("GetStepStatus", &G4StepPoint::GetStepStatus)
      .def("GetProcessDefinedStep", &G4StepPoint::GetProcessDefinedStep, py::return_value_policy::reference)
      .def("GetMass", &G4StepPoint::GetMass)
      .def("GetCharge", &G4StepPoint::GetCharge)
      .def("GetWeight", &G4StepPoint::GetWeight);
}
