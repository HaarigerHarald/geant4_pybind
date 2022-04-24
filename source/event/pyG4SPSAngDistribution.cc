#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4SPSAngDistribution.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4SPSAngDistribution(py::module &m)
{
   py::class_<G4SPSAngDistribution>(m, "G4SPSAngDistribution")

      .def(py::init<>())
      .def("DefineAngRefAxes", &G4SPSAngDistribution::DefineAngRefAxes)
      .def("GenerateOne", &G4SPSAngDistribution::GenerateOne)
      .def("GetDirection", &G4SPSAngDistribution::GetDirection)
      .def("GetDistType", &G4SPSAngDistribution::GetDistType)
      .def("GetMaxPhi", &G4SPSAngDistribution::GetMaxPhi)
      .def("GetMaxTheta", &G4SPSAngDistribution::GetMaxTheta)
      .def("GetMinPhi", &G4SPSAngDistribution::GetMinPhi)
      .def("GetMinTheta", &G4SPSAngDistribution::GetMinTheta)
      .def("ReSetHist", &G4SPSAngDistribution::ReSetHist)
      .def("SetAngDistType", &G4SPSAngDistribution::SetAngDistType)
      .def("SetBeamSigmaInAngR", &G4SPSAngDistribution::SetBeamSigmaInAngR)
      .def("SetBeamSigmaInAngX", &G4SPSAngDistribution::SetBeamSigmaInAngX)
      .def("SetBeamSigmaInAngY", &G4SPSAngDistribution::SetBeamSigmaInAngY)
      .def("SetBiasRndm", &G4SPSAngDistribution::SetBiasRndm, py::arg("a"))
      .def("SetFocusPoint", &G4SPSAngDistribution::SetFocusPoint)
      .def("SetMaxPhi", &G4SPSAngDistribution::SetMaxPhi)
      .def("SetMaxTheta", &G4SPSAngDistribution::SetMaxTheta)
      .def("SetMinPhi", &G4SPSAngDistribution::SetMinPhi)
      .def("SetMinTheta", &G4SPSAngDistribution::SetMinTheta)
      .def("SetParticleMomentumDirection", &G4SPSAngDistribution::SetParticleMomentumDirection,
           py::arg("aMomDirection"))

      .def("SetPosDistribution", &G4SPSAngDistribution::SetPosDistribution, py::arg("a"))
      .def("SetUseUserAngAxis", &G4SPSAngDistribution::SetUseUserAngAxis)
      .def("SetUserWRTSurface", &G4SPSAngDistribution::SetUserWRTSurface)
      .def("SetVerbosity", &G4SPSAngDistribution::SetVerbosity, py::arg("a"))
      .def("UserDefAngPhi", &G4SPSAngDistribution::UserDefAngPhi)
      .def("UserDefAngTheta", &G4SPSAngDistribution::UserDefAngTheta);
}
