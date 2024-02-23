#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4HadronicParameters.hh>
#include <G4HadronicParametersMessenger.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4HadronicParameters(py::module &m)
{
   py::class_<G4HadronicParameters, py::nodelete>(m, "G4HadronicParameters")

      .def(
         "__copy__", [](const G4HadronicParameters &self) { return new G4HadronicParameters(self); },
         py::return_value_policy::reference)

      .def(
         "__deepcopy__", [](const G4HadronicParameters &self, py::dict) { return new G4HadronicParameters(self); },
         py::return_value_policy::reference)

      .def("ApplyFactorXS", &G4HadronicParameters::ApplyFactorXS)
      .def("EnableBCParticles", &G4HadronicParameters::EnableBCParticles)
      .def("EnableCRCoalescence", &G4HadronicParameters::EnableCRCoalescence)
      .def("EnableHyperNuclei", &G4HadronicParameters::EnableHyperNuclei)
      .def("EnergyThresholdForHeavyHadrons", &G4HadronicParameters::EnergyThresholdForHeavyHadrons)
      .def("GetMaxEnergy", &G4HadronicParameters::GetMaxEnergy)
      .def("GetMaxEnergyTransitionFTF_Cascade", &G4HadronicParameters::GetMaxEnergyTransitionFTF_Cascade)
      .def("GetMaxEnergyTransitionQGS_FTF", &G4HadronicParameters::GetMaxEnergyTransitionQGS_FTF)
      .def("GetMinEnergyTransitionFTF_Cascade", &G4HadronicParameters::GetMinEnergyTransitionFTF_Cascade)
      .def("GetMinEnergyTransitionQGS_FTF", &G4HadronicParameters::GetMinEnergyTransitionQGS_FTF)
      .def("GetVerboseLevel", &G4HadronicParameters::GetVerboseLevel)
      .def_static("Instance", &G4HadronicParameters::Instance, py::return_value_policy::reference)
      .def("SetApplyFactorXS", &G4HadronicParameters::SetApplyFactorXS, py::arg("val"))
      .def("SetEnableBCParticles", &G4HadronicParameters::SetEnableBCParticles, py::arg("val"))
      .def("SetEnableCRCoalescence", &G4HadronicParameters::SetEnableCRCoalescence, py::arg("val"))
      .def("SetEnableHyperNuclei", &G4HadronicParameters::SetEnableHyperNuclei, py::arg("val"))
      .def("SetEnergyThresholdForHeavyHadrons", &G4HadronicParameters::SetEnergyThresholdForHeavyHadrons,
           py::arg("val"))

      .def("SetMaxEnergy", &G4HadronicParameters::SetMaxEnergy, py::arg("val"))
      .def("SetMaxEnergyTransitionFTF_Cascade", &G4HadronicParameters::SetMaxEnergyTransitionFTF_Cascade,
           py::arg("val"))

      .def("SetMaxEnergyTransitionQGS_FTF", &G4HadronicParameters::SetMaxEnergyTransitionQGS_FTF, py::arg("val"))
      .def("SetMinEnergyTransitionFTF_Cascade", &G4HadronicParameters::SetMinEnergyTransitionFTF_Cascade,
           py::arg("val"))

      .def("SetMinEnergyTransitionQGS_FTF", &G4HadronicParameters::SetMinEnergyTransitionQGS_FTF, py::arg("val"))
      .def("SetVerboseLevel", &G4HadronicParameters::SetVerboseLevel, py::arg("val"))
      .def("SetXSFactorEM", &G4HadronicParameters::SetXSFactorEM, py::arg("val"))
      .def("SetXSFactorHadronElastic", &G4HadronicParameters::SetXSFactorHadronElastic, py::arg("val"))
      .def("SetXSFactorHadronInelastic", &G4HadronicParameters::SetXSFactorHadronInelastic, py::arg("val"))
      .def("SetXSFactorNucleonElastic", &G4HadronicParameters::SetXSFactorNucleonElastic, py::arg("val"))
      .def("SetXSFactorNucleonInelastic", &G4HadronicParameters::SetXSFactorNucleonInelastic, py::arg("val"))
      .def("SetXSFactorPionElastic", &G4HadronicParameters::SetXSFactorPionElastic, py::arg("val"))
      .def("SetXSFactorPionInelastic", &G4HadronicParameters::SetXSFactorPionInelastic, py::arg("val"))
      .def("XSFactorEM", &G4HadronicParameters::XSFactorEM)
      .def("XSFactorHadronElastic", &G4HadronicParameters::XSFactorHadronElastic)
      .def("XSFactorHadronInelastic", &G4HadronicParameters::XSFactorHadronInelastic)
      .def("XSFactorNucleonElastic", &G4HadronicParameters::XSFactorNucleonElastic)
      .def("XSFactorNucleonInelastic", &G4HadronicParameters::XSFactorNucleonInelastic)
      .def("XSFactorPionElastic", &G4HadronicParameters::XSFactorPionElastic)
      .def("XSFactorPionInelastic", &G4HadronicParameters::XSFactorPionInelastic);
}
