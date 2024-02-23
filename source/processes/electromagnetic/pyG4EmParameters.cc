#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4EmParameters.hh>
#include <G4GeomSplitter.hh>
#include <G4VPVParameterisation.hh>
#include <G4Allocator.hh>
#include <G4VSolid.hh>
#include <G4NavigationHistory.hh>
#include <G4ReferenceCountedHandle.hh>
#include <G4DensityEffectData.hh>
#include <G4DensityEffectCalculator.hh>
#include <G4ProductionCuts.hh>
#include <G4VUserRegionInformation.hh>
#include <G4MaterialCutsCouple.hh>
#include <G4UserLimits.hh>
#include <G4FieldManager.hh>
#include <G4FastSimulationManager.hh>
#include <G4UserSteppingAction.hh>
#include <G4VSensitiveDetector.hh>
#include <G4SmartVoxelHeader.hh>
#include <G4VisAttributes.hh>
#include <G4VProcess.hh>
#include <G4Run.hh>
#include <G4Event.hh>
#include <G4Polyline.hh>
#include <G4ProcessManager.hh>
#include <G4VTrackingManager.hh>
#include <G4DecayTable.hh>
#include <G4ParticleTable.hh>
#include <G4ParticlePropertyTable.hh>
#include <G4PrimaryParticle.hh>
#include <G4DecayProducts.hh>
#include <G4VAuxiliaryTrackInformation.hh>
#include <G4NistManager.hh>
#include <G4EmParametersMessenger.hh>
#include <G4EmExtraParameters.hh>
#include <G4EmLowEParameters.hh>
#include <G4VAtomDeexcitation.hh>
#include <G4VEnergyLossProcess.hh>
#include <G4VEmProcess.hh>
#include <G4StateManager.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4EmParameters(py::module &m)
{
   py::enum_<G4eSingleScatteringType>(m, "G4eSingleScatteringType")
      .value("fWVI", fWVI)
      .value("fMott", fMott)
      .value("fDPWA", fDPWA)
      .export_values();

   py::class_<G4EmParameters, py::nodelete>(m, "G4EmParameters")

      .def("ANSTOFluoDir", &G4EmParameters::ANSTOFluoDir)
      .def("ActivateAngularGeneratorForIonisation", &G4EmParameters::ActivateAngularGeneratorForIonisation,
           py::arg("val"))

      .def("ActivateDNA", &G4EmParameters::ActivateDNA)
      .def("ActivateForcedInteraction", &G4EmParameters::ActivateForcedInteraction, py::arg("procname"),
           py::arg("region"), py::arg("length"), py::arg("wflag"))

      .def("ActivateSecondaryBiasing", &G4EmParameters::ActivateSecondaryBiasing, py::arg("name"), py::arg("region"),
           py::arg("factor"), py::arg("energyLimit"))

      .def("AddDNA", &G4EmParameters::AddDNA, py::arg("region"), py::arg("type"))
      .def("AddMicroElec", &G4EmParameters::AddMicroElec, py::arg("region"))
      .def("AddPAIModel", &G4EmParameters::AddPAIModel, py::arg("particle"), py::arg("region"), py::arg("type"))
      .def("AddPhysics", &G4EmParameters::AddPhysics, py::arg("region"), py::arg("type"))
      .def("ApplyCuts", &G4EmParameters::ApplyCuts)
      .def("Auger", &G4EmParameters::Auger)
      .def("AugerCascade", &G4EmParameters::AugerCascade)
      .def("BeardenFluoDir", &G4EmParameters::BeardenFluoDir)
      .def("BirksActive", &G4EmParameters::BirksActive)
      .def("BremsstrahlungTh", &G4EmParameters::BremsstrahlungTh)
      .def("BuildCSDARange", &G4EmParameters::BuildCSDARange)
      .def("DNAElectronMsc", &G4EmParameters::DNAElectronMsc)
      .def("DNAFast", &G4EmParameters::DNAFast)
      .def("DNAStationary", &G4EmParameters::DNAStationary)
      .def("DNAeSolvationSubType", &G4EmParameters::DNAeSolvationSubType)
      .def("DeexcitationIgnoreCut", &G4EmParameters::DeexcitationIgnoreCut)
      .def("DefineRegParamForDeex", &G4EmParameters::DefineRegParamForDeex)
      .def("DefineRegParamForEM", &G4EmParameters::DefineRegParamForEM)
      .def("DefineRegParamForLoss", &G4EmParameters::DefineRegParamForLoss)
      .def("Dump", &G4EmParameters::Dump)
      .def("EnablePolarisation", &G4EmParameters::EnablePolarisation)
      .def("EnableSamplingTable", &G4EmParameters::EnableSamplingTable)
      .def("FactorForAngleLimit", &G4EmParameters::FactorForAngleLimit)
      .def("FillStepFunction", &G4EmParameters::FillStepFunction)
      .def("Fluo", &G4EmParameters::Fluo)
      .def("GeneralProcessActive", &G4EmParameters::GeneralProcessActive)
      .def("GetConversionType", &G4EmParameters::GetConversionType)
      .def("GetDirectionalSplitting", &G4EmParameters::GetDirectionalSplitting)
      .def("GetDirectionalSplittingRadius", &G4EmParameters::GetDirectionalSplittingRadius)
      .def("GetDirectionalSplittingTarget", &G4EmParameters::GetDirectionalSplittingTarget)
      .def("GetEmSaturation", &G4EmParameters::GetEmSaturation, py::return_value_policy::reference)
      .def_static("Instance", &G4EmParameters::Instance, py::return_value_policy::reference)
      .def("Integral", &G4EmParameters::Integral)
      .def("IsPrintLocked", &G4EmParameters::IsPrintLocked)
      .def("LPM", &G4EmParameters::LPM)
      .def("LambdaFactor", &G4EmParameters::LambdaFactor)
      .def("LateralDisplacement", &G4EmParameters::LateralDisplacement)
      .def("LateralDisplacementAlg96", &G4EmParameters::LateralDisplacementAlg96)
      .def("LinearLossLimit", &G4EmParameters::LinearLossLimit)
      .def("LivermoreDataDir", &G4EmParameters::LivermoreDataDir)
      .def("LossFluctuation", &G4EmParameters::LossFluctuation)
      .def("LowestElectronEnergy", &G4EmParameters::LowestElectronEnergy)
      .def("LowestMuHadEnergy", &G4EmParameters::LowestMuHadEnergy)
      .def("LowestTripletEnergy", &G4EmParameters::LowestTripletEnergy)
      .def("MaxEnergyFor5DMuPair", &G4EmParameters::MaxEnergyFor5DMuPair)
      .def("MaxEnergyForCSDARange", &G4EmParameters::MaxEnergyForCSDARange)
      .def("MaxKinEnergy", &G4EmParameters::MaxKinEnergy)
      .def("MaxNIELEnergy", &G4EmParameters::MaxNIELEnergy)
      .def("MinKinEnergy", &G4EmParameters::MinKinEnergy)
      .def("MscEnergyLimit", &G4EmParameters::MscEnergyLimit)
      .def("MscGeomFactor", &G4EmParameters::MscGeomFactor)
      .def("MscLambdaLimit", &G4EmParameters::MscLambdaLimit)
      .def("MscMuHadRangeFactor", &G4EmParameters::MscMuHadRangeFactor)
      .def("MscMuHadStepLimitType", &G4EmParameters::MscMuHadStepLimitType)
      .def("MscRangeFactor", &G4EmParameters::MscRangeFactor)
      .def("MscSafetyFactor", &G4EmParameters::MscSafetyFactor)
      .def("MscSkin", &G4EmParameters::MscSkin)
      .def("MscStepLimitType", &G4EmParameters::MscStepLimitType)
      .def("MscThetaLimit", &G4EmParameters::MscThetaLimit)
      .def("MuHadBremsstrahlungTh", &G4EmParameters::MuHadBremsstrahlungTh)
      .def("MuHadLateralDisplacement", &G4EmParameters::MuHadLateralDisplacement)
      .def("NuclearFormfactorType", &G4EmParameters::NuclearFormfactorType)
      .def("NumberOfBins", &G4EmParameters::NumberOfBins)
      .def("NumberOfBinsPerDecade", &G4EmParameters::NumberOfBinsPerDecade)
      .def("OnIsolated", &G4EmParameters::OnIsolated)
      .def("PIXECrossSectionModel", &G4EmParameters::PIXECrossSectionModel)
      .def("PIXEElectronCrossSectionModel", &G4EmParameters::PIXEElectronCrossSectionModel)
      .def("ParticlesPAI", &G4EmParameters::ParticlesPAI)
      .def("Pixe", &G4EmParameters::Pixe)
      .def("QuantumEntanglement", &G4EmParameters::QuantumEntanglement)
      .def("RegionsDNA", &G4EmParameters::RegionsDNA)
      .def("RegionsMicroElec", &G4EmParameters::RegionsMicroElec)
      .def("RegionsPAI", &G4EmParameters::RegionsPAI)
      .def("RegionsPhysics", &G4EmParameters::RegionsPhysics)
      .def("RetrieveMuDataFromFile", &G4EmParameters::RetrieveMuDataFromFile)
      .def("ScreeningFactor", &G4EmParameters::ScreeningFactor)
      .def("SetANSTOFluoDir", &G4EmParameters::SetANSTOFluoDir, py::arg("val"))
      .def("SetApplyCuts", &G4EmParameters::SetApplyCuts, py::arg("val"))
      .def("SetAuger", &G4EmParameters::SetAuger, py::arg("val"))
      .def("SetAugerCascade", &G4EmParameters::SetAugerCascade, py::arg("val"))
      .def("SetBeardenFluoDir", &G4EmParameters::SetBeardenFluoDir, py::arg("val"))
      .def("SetBirksActive", &G4EmParameters::SetBirksActive, py::arg("val"))
      .def("SetBremsstrahlungTh", &G4EmParameters::SetBremsstrahlungTh, py::arg("val"))
      .def("SetBuildCSDARange", &G4EmParameters::SetBuildCSDARange, py::arg("val"))
      .def("SetConversionType", &G4EmParameters::SetConversionType, py::arg("val"))
      .def("SetDNAElectronMsc", &G4EmParameters::SetDNAElectronMsc, py::arg("val"))
      .def("SetDNAFast", &G4EmParameters::SetDNAFast, py::arg("val"))
      .def("SetDNAStationary", &G4EmParameters::SetDNAStationary, py::arg("val"))
      .def("SetDNAeSolvationSubType", &G4EmParameters::SetDNAeSolvationSubType, py::arg("val"))
      .def("SetDeexActiveRegion", &G4EmParameters::SetDeexActiveRegion, py::arg("region"), py::arg("fdeex"),
           py::arg("fauger"), py::arg("fpixe"))

      .def("SetDeexcitationIgnoreCut", &G4EmParameters::SetDeexcitationIgnoreCut, py::arg("val"))
      .def("SetDefaults", &G4EmParameters::SetDefaults)
      .def("SetDirectionalSplitting", &G4EmParameters::SetDirectionalSplitting, py::arg("v"))
      .def("SetDirectionalSplittingRadius", &G4EmParameters::SetDirectionalSplittingRadius, py::arg("r"))
      .def("SetDirectionalSplittingTarget", &G4EmParameters::SetDirectionalSplittingTarget, py::arg("v"))
      .def("SetEmSaturation", &G4EmParameters::SetEmSaturation)
      .def("SetEnablePolarisation", &G4EmParameters::SetEnablePolarisation, py::arg("val"))
      .def("SetEnableSamplingTable", &G4EmParameters::SetEnableSamplingTable, py::arg("val"))
      .def("SetFactorForAngleLimit", &G4EmParameters::SetFactorForAngleLimit, py::arg("val"))
      .def("SetFluo", &G4EmParameters::SetFluo, py::arg("val"))
      .def("SetGeneralProcessActive", &G4EmParameters::SetGeneralProcessActive, py::arg("val"))
      .def("SetIntegral", &G4EmParameters::SetIntegral, py::arg("val"))
      .def("SetIsPrintedFlag", &G4EmParameters::SetIsPrintedFlag, py::arg("val"))
      .def("SetLPM", &G4EmParameters::SetLPM, py::arg("val"))
      .def("SetLambdaFactor", &G4EmParameters::SetLambdaFactor, py::arg("val"))
      .def("SetLateralDisplacement", &G4EmParameters::SetLateralDisplacement, py::arg("val"))
      .def("SetLateralDisplacementAlg96", &G4EmParameters::SetLateralDisplacementAlg96, py::arg("val"))
      .def("SetLinearLossLimit", &G4EmParameters::SetLinearLossLimit, py::arg("val"))
      .def("SetLivermoreDataDir", &G4EmParameters::SetLivermoreDataDir)
      .def("SetLossFluctuations", &G4EmParameters::SetLossFluctuations, py::arg("val"))
      .def("SetLowestElectronEnergy", &G4EmParameters::SetLowestElectronEnergy, py::arg("val"))
      .def("SetLowestMuHadEnergy", &G4EmParameters::SetLowestMuHadEnergy, py::arg("val"))
      .def("SetLowestTripletEnergy", &G4EmParameters::SetLowestTripletEnergy, py::arg("val"))
      .def("SetMaxEnergy", &G4EmParameters::SetMaxEnergy, py::arg("val"))
      .def("SetMaxEnergyFor5DMuPair", &G4EmParameters::SetMaxEnergyFor5DMuPair, py::arg("val"))
      .def("SetMaxEnergyForCSDARange", &G4EmParameters::SetMaxEnergyForCSDARange, py::arg("val"))
      .def("SetMaxNIELEnergy", &G4EmParameters::SetMaxNIELEnergy, py::arg("val"))
      .def("SetMinEnergy", &G4EmParameters::SetMinEnergy, py::arg("val"))
      .def("SetMscEnergyLimit", &G4EmParameters::SetMscEnergyLimit, py::arg("val"))
      .def("SetMscGeomFactor", &G4EmParameters::SetMscGeomFactor, py::arg("val"))
      .def("SetMscLambdaLimit", &G4EmParameters::SetMscLambdaLimit, py::arg("val"))
      .def("SetMscMuHadRangeFactor", &G4EmParameters::SetMscMuHadRangeFactor, py::arg("val"))
      .def("SetMscMuHadStepLimitType", &G4EmParameters::SetMscMuHadStepLimitType, py::arg("val"))
      .def("SetMscRangeFactor", &G4EmParameters::SetMscRangeFactor, py::arg("val"))
      .def("SetMscSafetyFactor", &G4EmParameters::SetMscSafetyFactor, py::arg("val"))
      .def("SetMscSkin", &G4EmParameters::SetMscSkin, py::arg("val"))
      .def("SetMscStepLimitType", &G4EmParameters::SetMscStepLimitType, py::arg("val"))
      .def("SetMscThetaLimit", &G4EmParameters::SetMscThetaLimit, py::arg("val"))
      .def("SetMuHadBremsstrahlungTh", &G4EmParameters::SetMuHadBremsstrahlungTh, py::arg("val"))
      .def("SetMuHadLateralDisplacement", &G4EmParameters::SetMuHadLateralDisplacement, py::arg("val"))
      .def("SetNuclearFormfactorType", &G4EmParameters::SetNuclearFormfactorType, py::arg("val"))
      .def("SetNumberOfBinsPerDecade", &G4EmParameters::SetNumberOfBinsPerDecade, py::arg("val"))
      .def("SetOnIsolated", &G4EmParameters::SetOnIsolated, py::arg("val"))
      .def("SetPIXECrossSectionModel", &G4EmParameters::SetPIXECrossSectionModel)
      .def("SetPIXEElectronCrossSectionModel", &G4EmParameters::SetPIXEElectronCrossSectionModel)
      .def("SetPixe", &G4EmParameters::SetPixe, py::arg("val"))
      .def("SetProcessBiasingFactor", &G4EmParameters::SetProcessBiasingFactor, py::arg("procname"), py::arg("val"),
           py::arg("wflag"))

      .def("SetQuantumEntanglement", &G4EmParameters::SetQuantumEntanglement, py::arg("v"))
      .def("SetRetrieveMuDataFromFile", &G4EmParameters::SetRetrieveMuDataFromFile, py::arg("v"))
      .def("SetScreeningFactor", &G4EmParameters::SetScreeningFactor, py::arg("val"))
      .def("SetSingleScatteringType", &G4EmParameters::SetSingleScatteringType, py::arg("val"))
      .def("SetStepFunction", &G4EmParameters::SetStepFunction, py::arg("v1"), py::arg("v2"))
      .def("SetStepFunctionIons", &G4EmParameters::SetStepFunctionIons, py::arg("v1"), py::arg("v2"))
      .def("SetStepFunctionLightIons", &G4EmParameters::SetStepFunctionLightIons, py::arg("v1"), py::arg("v2"))
      .def("SetStepFunctionMuHad", &G4EmParameters::SetStepFunctionMuHad, py::arg("v1"), py::arg("v2"))
      .def("SetSubCutRegion", &G4EmParameters::SetSubCutRegion, py::arg("region") = "")
      .def("SetUseCutAsFinalRange", &G4EmParameters::SetUseCutAsFinalRange, py::arg("val"))
      .def("SetUseICRU90Data", &G4EmParameters::SetUseICRU90Data, py::arg("val"))
      .def("SetUseMottCorrection", &G4EmParameters::SetUseMottCorrection, py::arg("val"))
      .def("SetVerbose", &G4EmParameters::SetVerbose, py::arg("val"))
      .def("SetWorkerVerbose", &G4EmParameters::SetWorkerVerbose, py::arg("val"))
      .def("SingleScatteringType", &G4EmParameters::SingleScatteringType)
      .def("StreamInfo", &G4EmParameters::StreamInfo, py::arg("os"))
      .def("TypesDNA", &G4EmParameters::TypesDNA)
      .def("TypesPAI", &G4EmParameters::TypesPAI)
      .def("TypesPhysics", &G4EmParameters::TypesPhysics)
      .def("UseAngularGeneratorForIonisation", &G4EmParameters::UseAngularGeneratorForIonisation)
      .def("UseCutAsFinalRange", &G4EmParameters::UseCutAsFinalRange)
      .def("UseICRU90Data", &G4EmParameters::UseICRU90Data)
      .def("UseMottCorrection", &G4EmParameters::UseMottCorrection)
      .def("Verbose", &G4EmParameters::Verbose)
      .def("WorkerVerbose", &G4EmParameters::WorkerVerbose)
      .def(
         "__str__",
         [](const G4EmParameters &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator());
}
