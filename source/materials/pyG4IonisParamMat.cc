#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4IonisParamMat.hh>
#include <G4Material.hh>
#include <G4DensityEffectData.hh>
#include <G4DensityEffectCalculator.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4IonisParamMat(py::module &m)
{
   py::class_<G4IonisParamMat>(m, "G4IonisParamMat")

      .def(py::init<const G4Material *>())
      .def("ComputeDensityEffectOnFly", &G4IonisParamMat::ComputeDensityEffectOnFly)
      .def("DensityCorrection", &G4IonisParamMat::DensityCorrection, py::arg("x"))
      .def("FindMeanExcitationEnergy", &G4IonisParamMat::FindMeanExcitationEnergy)
      .def("GetAdensity", &G4IonisParamMat::GetAdensity)
      .def("GetAdjustmentFactor", &G4IonisParamMat::GetAdjustmentFactor)
      .def("GetBirksConstant", &G4IonisParamMat::GetBirksConstant)
      .def("GetCdensity", &G4IonisParamMat::GetCdensity)
      .def("GetD0density", &G4IonisParamMat::GetD0density)
      .def("GetDensityCorrection", &G4IonisParamMat::GetDensityCorrection, py::arg("x"))
      .def("GetDensityEffectCalculator", &G4IonisParamMat::GetDensityEffectCalculator,
           py::return_value_policy::reference)

      .def_static("GetDensityEffectData", &G4IonisParamMat::GetDensityEffectData, py::return_value_policy::reference)
      .def("GetEnergy0fluct", &G4IonisParamMat::GetEnergy0fluct)
      .def("GetEnergy1fluct", &G4IonisParamMat::GetEnergy1fluct)
      .def("GetEnergy2fluct", &G4IonisParamMat::GetEnergy2fluct)
      .def("GetF1fluct", &G4IonisParamMat::GetF1fluct)
      .def("GetF2fluct", &G4IonisParamMat::GetF2fluct)
      .def("GetFermiEnergy", &G4IonisParamMat::GetFermiEnergy)
      .def("GetInvA23", &G4IonisParamMat::GetInvA23)
      .def("GetLFactor", &G4IonisParamMat::GetLFactor)
      .def("GetLogEnergy1fluct", &G4IonisParamMat::GetLogEnergy1fluct)
      .def("GetLogEnergy2fluct", &G4IonisParamMat::GetLogEnergy2fluct)
      .def("GetLogMeanExcEnergy", &G4IonisParamMat::GetLogMeanExcEnergy)
      .def("GetMdensity", &G4IonisParamMat::GetMdensity)
      .def("GetMeanEnergyPerIonPair", &G4IonisParamMat::GetMeanEnergyPerIonPair)
      .def("GetMeanExcitationEnergy", &G4IonisParamMat::GetMeanExcitationEnergy)
      .def("GetPlasmaEnergy", &G4IonisParamMat::GetPlasmaEnergy)
      .def("GetRateionexcfluct", &G4IonisParamMat::GetRateionexcfluct)
      .def("GetShellCorrectionVector",
           [](const G4IonisParamMat &self) {
              G4double               *shellCorrectionVector = self.GetShellCorrectionVector();
              std::array<G4double, 3> shellCorrectionArr;
              std::copy(shellCorrectionVector, shellCorrectionVector + 3, std::begin(shellCorrectionArr));
              return shellCorrectionArr;
           })
      .def("GetTaul", &G4IonisParamMat::GetTaul)
      .def("GetX0density", &G4IonisParamMat::GetX0density)
      .def("GetX1density", &G4IonisParamMat::GetX1density)
      .def("GetZeffective", &G4IonisParamMat::GetZeffective)
      .def("SetBirksConstant", &G4IonisParamMat::SetBirksConstant, py::arg("value"))
      .def("SetDensityEffectParameters",
           py::overload_cast<G4double, G4double, G4double, G4double, G4double, G4double>(
              &G4IonisParamMat::SetDensityEffectParameters),
           py::arg("cd"), py::arg("md"), py::arg("ad"), py::arg("x0"), py::arg("x1"), py::arg("d0"))

      .def("SetDensityEffectParameters",
           py::overload_cast<const G4Material *>(&G4IonisParamMat::SetDensityEffectParameters), py::arg("bmat"))

      .def("SetMeanEnergyPerIonPair", &G4IonisParamMat::SetMeanEnergyPerIonPair, py::arg("value"))
      .def("SetMeanExcitationEnergy", &G4IonisParamMat::SetMeanExcitationEnergy, py::arg("value"));
}
