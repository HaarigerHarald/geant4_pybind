#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4SPSEneDistribution.hh>
#include <G4ProcessManager.hh>
#include <G4VTrackingManager.hh>
#include <G4DecayTable.hh>
#include <G4ParticleTable.hh>
#include <G4ParticlePropertyTable.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4SPSEneDistribution(py::module &m)
{
   py::class_<G4SPSEneDistribution>(m, "G4SPSEneDistribution")

      .def(py::init<>())
      .def("ApplyEnergyWeight", &G4SPSEneDistribution::ApplyEnergyWeight, py::arg("val"))
      .def("ArbEnergyHisto", &G4SPSEneDistribution::ArbEnergyHisto)
      .def("ArbEnergyHistoFile", &G4SPSEneDistribution::ArbEnergyHistoFile)
      .def("ArbInterpolate", &G4SPSEneDistribution::ArbInterpolate)
      .def("Calculate", &G4SPSEneDistribution::Calculate)
      .def("EpnEnergyHisto", &G4SPSEneDistribution::EpnEnergyHisto)
      .def("GenerateOne", &G4SPSEneDistribution::GenerateOne)
      .def("GetArbEmax", &G4SPSEneDistribution::GetArbEmax)
      .def("GetArbEmin", &G4SPSEneDistribution::GetArbEmin)
      .def("GetArbEneWeight", &G4SPSEneDistribution::GetArbEneWeight)
      .def("GetArbEnergyHisto", &G4SPSEneDistribution::GetArbEnergyHisto)
      .def("GetEmax", &G4SPSEneDistribution::GetEmax)
      .def("GetEmin", &G4SPSEneDistribution::GetEmin)
      .def("GetEnergyDisType", &G4SPSEneDistribution::GetEnergyDisType)
      .def("GetEzero", &G4SPSEneDistribution::GetEzero)
      .def("GetIntType", &G4SPSEneDistribution::GetIntType)
      .def("GetMonoEnergy", &G4SPSEneDistribution::GetMonoEnergy)
      .def("GetProbability", &G4SPSEneDistribution::GetProbability)
      .def("GetSE", &G4SPSEneDistribution::GetSE)
      .def("GetTemp", &G4SPSEneDistribution::GetTemp)
      .def("GetUserDefinedEnergyHisto", &G4SPSEneDistribution::GetUserDefinedEnergyHisto)
      .def("GetWeight", &G4SPSEneDistribution::GetWeight)
      .def("Getalpha", &G4SPSEneDistribution::Getalpha)
      .def("Getcept", &G4SPSEneDistribution::Getcept)
      .def("Getgrad", &G4SPSEneDistribution::Getgrad)
      .def("IfApplyEnergyWeight", &G4SPSEneDistribution::IfApplyEnergyWeight)
      .def("InputDifferentialSpectra", &G4SPSEneDistribution::InputDifferentialSpectra)
      .def("InputEnergySpectra", &G4SPSEneDistribution::InputEnergySpectra)
      .def("ReSetHist", &G4SPSEneDistribution::ReSetHist)
      .def("SetAlpha", &G4SPSEneDistribution::SetAlpha)
      .def("SetBeamSigmaInE", &G4SPSEneDistribution::SetBeamSigmaInE)
      .def("SetBiasAlpha", &G4SPSEneDistribution::SetBiasAlpha)
      .def("SetBiasRndm", &G4SPSEneDistribution::SetBiasRndm, py::arg("a"))
      .def("SetEmax", &G4SPSEneDistribution::SetEmax)
      .def("SetEmin", &G4SPSEneDistribution::SetEmin)
      .def("SetEnergyDisType", &G4SPSEneDistribution::SetEnergyDisType)
      .def("SetEzero", &G4SPSEneDistribution::SetEzero)
      .def("SetGradient", &G4SPSEneDistribution::SetGradient)
      .def("SetInterCept", &G4SPSEneDistribution::SetInterCept)
      .def("SetMonoEnergy", &G4SPSEneDistribution::SetMonoEnergy)
      .def("SetTemp", &G4SPSEneDistribution::SetTemp)
      .def("SetVerbosity", &G4SPSEneDistribution::SetVerbosity, py::arg("a"))
      .def("UserEnergyHisto", &G4SPSEneDistribution::UserEnergyHisto);
}
