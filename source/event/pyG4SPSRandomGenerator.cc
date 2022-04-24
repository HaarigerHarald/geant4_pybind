#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4SPSRandomGenerator.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4SPSRandomGenerator(py::module &m)
{
   py::class_<G4SPSRandomGenerator>(m, "G4SPSRandomGenerator")

      .def(py::init<>())
      .def("GenRandEnergy", &G4SPSRandomGenerator::GenRandEnergy)
      .def("GenRandPhi", &G4SPSRandomGenerator::GenRandPhi)
      .def("GenRandPosPhi", &G4SPSRandomGenerator::GenRandPosPhi)
      .def("GenRandPosTheta", &G4SPSRandomGenerator::GenRandPosTheta)
      .def("GenRandTheta", &G4SPSRandomGenerator::GenRandTheta)
      .def("GenRandX", &G4SPSRandomGenerator::GenRandX)
      .def("GenRandY", &G4SPSRandomGenerator::GenRandY)
      .def("GenRandZ", &G4SPSRandomGenerator::GenRandZ)
      .def("GetBiasWeight", &G4SPSRandomGenerator::GetBiasWeight)
      .def("ReSetHist", &G4SPSRandomGenerator::ReSetHist)
      .def("SetEnergyBias", &G4SPSRandomGenerator::SetEnergyBias)
      .def("SetIntensityWeight", &G4SPSRandomGenerator::SetIntensityWeight, py::arg("weight"))
      .def("SetPhiBias", &G4SPSRandomGenerator::SetPhiBias)
      .def("SetPosPhiBias", &G4SPSRandomGenerator::SetPosPhiBias)
      .def("SetPosThetaBias", &G4SPSRandomGenerator::SetPosThetaBias)
      .def("SetThetaBias", &G4SPSRandomGenerator::SetThetaBias)
      .def("SetVerbosity", &G4SPSRandomGenerator::SetVerbosity, py::arg("a"))
      .def("SetXBias", &G4SPSRandomGenerator::SetXBias)
      .def("SetYBias", &G4SPSRandomGenerator::SetYBias)
      .def("SetZBias", &G4SPSRandomGenerator::SetZBias);
}
