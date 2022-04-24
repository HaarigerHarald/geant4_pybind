#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4SPSPosDistribution.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4SPSPosDistribution(py::module &m)
{
   py::class_<G4SPSPosDistribution>(m, "G4SPSPosDistribution")

      .def(py::init<>())
      .def("ConfineSourceToVolume", &G4SPSPosDistribution::ConfineSourceToVolume)
      .def("GenerateOne", &G4SPSPosDistribution::GenerateOne)
      .def("GetCentreCoords", &G4SPSPosDistribution::GetCentreCoords)
      .def("GetConfineVolume", &G4SPSPosDistribution::GetConfineVolume)
      .def("GetConfined", &G4SPSPosDistribution::GetConfined)
      .def("GetHalfX", &G4SPSPosDistribution::GetHalfX)
      .def("GetHalfY", &G4SPSPosDistribution::GetHalfY)
      .def("GetHalfZ", &G4SPSPosDistribution::GetHalfZ)
      .def("GetParAlpha", &G4SPSPosDistribution::GetParAlpha)
      .def("GetParPhi", &G4SPSPosDistribution::GetParPhi)
      .def("GetParTheta", &G4SPSPosDistribution::GetParTheta)
      .def("GetParticlePos", &G4SPSPosDistribution::GetParticlePos)
      .def("GetPosDisShape", &G4SPSPosDistribution::GetPosDisShape)
      .def("GetPosDisType", &G4SPSPosDistribution::GetPosDisType)
      .def("GetRadius", &G4SPSPosDistribution::GetRadius)
      .def("GetRadius0", &G4SPSPosDistribution::GetRadius0)
      .def("GetRotx", &G4SPSPosDistribution::GetRotx)
      .def("GetRoty", &G4SPSPosDistribution::GetRoty)
      .def("GetRotz", &G4SPSPosDistribution::GetRotz)
      .def("GetSideRefVec1", &G4SPSPosDistribution::GetSideRefVec1)
      .def("GetSideRefVec2", &G4SPSPosDistribution::GetSideRefVec2)
      .def("GetSideRefVec3", &G4SPSPosDistribution::GetSideRefVec3)
      .def("GetSourcePosType", &G4SPSPosDistribution::GetSourcePosType)
      .def("SetBeamSigmaInR", &G4SPSPosDistribution::SetBeamSigmaInR)
      .def("SetBeamSigmaInX", &G4SPSPosDistribution::SetBeamSigmaInX)
      .def("SetBeamSigmaInY", &G4SPSPosDistribution::SetBeamSigmaInY)
      .def("SetBiasRndm", &G4SPSPosDistribution::SetBiasRndm, py::arg("a"))
      .def("SetCentreCoords", &G4SPSPosDistribution::SetCentreCoords)
      .def("SetHalfX", &G4SPSPosDistribution::SetHalfX)
      .def("SetHalfY", &G4SPSPosDistribution::SetHalfY)
      .def("SetHalfZ", &G4SPSPosDistribution::SetHalfZ)
      .def("SetParAlpha", &G4SPSPosDistribution::SetParAlpha)
      .def("SetParPhi", &G4SPSPosDistribution::SetParPhi)
      .def("SetParTheta", &G4SPSPosDistribution::SetParTheta)
      .def("SetPosDisShape", &G4SPSPosDistribution::SetPosDisShape)
      .def("SetPosDisType", &G4SPSPosDistribution::SetPosDisType)
      .def("SetPosRot1", &G4SPSPosDistribution::SetPosRot1)
      .def("SetPosRot2", &G4SPSPosDistribution::SetPosRot2)
      .def("SetRadius", &G4SPSPosDistribution::SetRadius)
      .def("SetRadius0", &G4SPSPosDistribution::SetRadius0)
      .def("SetVerbosity", &G4SPSPosDistribution::SetVerbosity, py::arg("a"));
}
