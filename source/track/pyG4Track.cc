#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Track.hh>
#include <G4VProcess.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Track(py::module &m)
{
   py::class_<G4Track>(m, "G4Track", "track class")
      .def(py::init<>())
      .def(py::init<G4DynamicParticle *, G4double, const G4ThreeVector &>())
      .def(py::init<const G4Track &>())

      .def("GetTrackID", &G4Track::GetTrackID)
      .def("GetParentID", &G4Track::GetParentID)
      .def("GetDynamicParticle", &G4Track::GetDynamicParticle, py::return_value_policy::reference_internal)
      .def("GetDefinition", &G4Track::GetDefinition, py::return_value_policy::reference_internal)
      .def("GetPosition", &G4Track::GetPosition)
      .def("GetGlobalTime", &G4Track::GetGlobalTime)
      .def("GetLocalTime", &G4Track::GetLocalTime)
      .def("GetProperTime", &G4Track::GetProperTime)
      .def("GetVolume", &G4Track::GetVolume, py::return_value_policy::reference)
      .def("GetMaterial", &G4Track::GetMaterial, py::return_value_policy::reference)
      .def("GetTouchable", &G4Track::GetTouchable, py::return_value_policy::reference)
      .def("GetKineticEnergy", &G4Track::GetKineticEnergy)
      .def("GetTotalEnergy", &G4Track::GetTotalEnergy)
      .def("GetMomentumDirection", &G4Track::GetMomentumDirection)
      .def("GetMomentum", &G4Track::GetMomentum)
      .def("GetVelocity", &G4Track::GetVelocity)
      .def("GetPolarization", &G4Track::GetPolarization)
      .def("GetTrackStatus", &G4Track::GetTrackStatus)
      .def("GetTrackLength", &G4Track::GetTrackLength)
      .def("GetStep", &G4Track::GetStep, py::return_value_policy::reference)
      .def("GetCurrentStepNumber", &G4Track::GetCurrentStepNumber)
      .def("GetStepLength", &G4Track::GetStepLength)
      .def("GetVertexPosition", &G4Track::GetVertexPosition)
      .def("GetVertexMomentumDirection", &G4Track::GetVertexMomentumDirection)
      .def("GetVertexKineticEnergy", &G4Track::GetVertexKineticEnergy)
      .def("GetLogicalVolumeAtVertex", &G4Track::GetLogicalVolumeAtVertex, py::return_value_policy::reference)
      .def("GetCreatorProcess", &G4Track::GetCreatorProcess, py::return_value_policy::reference)
      .def("GetWeight", &G4Track::GetWeight)
      .def("SetWeight", &G4Track::SetWeight);
}
