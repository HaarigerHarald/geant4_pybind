#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Step.hh>
#include <G4GeomSplitter.hh>
#include <G4VPVParameterisation.hh>
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

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Step(py::module &m)
{
   py::class_<G4Step>(m, "G4Step")

      .def(py::init<>())
      .def("__copy__", [](const G4Step &self) { return new G4Step(self); })
      .def("__deepcopy__", [](const G4Step &self, py::dict) { return new G4Step(self); })
      .def("AddNonIonizingEnergyDeposit", &G4Step::AddNonIonizingEnergyDeposit, py::arg("value"))
      .def("AddTotalEnergyDeposit", &G4Step::AddTotalEnergyDeposit, py::arg("value"))
      .def("ClearFirstStepFlag", &G4Step::ClearFirstStepFlag)
      .def("ClearLastStepFlag", &G4Step::ClearLastStepFlag)
      .def("CopyPostToPreStepPoint", &G4Step::CopyPostToPreStepPoint)
      .def("DeleteSecondaryVector", &G4Step::DeleteSecondaryVector)
      .def("GetControlFlag", &G4Step::GetControlFlag)
      .def("GetDeltaEnergy", &G4Step::GetDeltaEnergy)
      .def("GetDeltaMomentum", &G4Step::GetDeltaMomentum)
      .def("GetDeltaPosition", &G4Step::GetDeltaPosition)
      .def("GetDeltaTime", &G4Step::GetDeltaTime)
      .def("GetNonIonizingEnergyDeposit", &G4Step::GetNonIonizingEnergyDeposit)
      .def("GetNumberOfSecondariesInCurrentStep", &G4Step::GetNumberOfSecondariesInCurrentStep)
      .def("GetPointerToVectorOfAuxiliaryPoints", &G4Step::GetPointerToVectorOfAuxiliaryPoints,
           py::return_value_policy::reference)

      .def("GetPostStepPoint", &G4Step::GetPostStepPoint, py::return_value_policy::reference)
      .def("GetPreStepPoint", &G4Step::GetPreStepPoint, py::return_value_policy::reference)
      .def("GetSecondary", &G4Step::GetSecondary, py::return_value_policy::reference)
      .def("GetSecondaryInCurrentStep", &G4Step::GetSecondaryInCurrentStep, py::return_value_policy::reference)
      .def("GetStepLength", &G4Step::GetStepLength)
      .def("GetTotalEnergyDeposit", &G4Step::GetTotalEnergyDeposit)
      .def("GetTrack", &G4Step::GetTrack, py::return_value_policy::reference)
      .def("GetfSecondary", &G4Step::GetfSecondary, py::return_value_policy::reference)
      .def("InitializeStep", &G4Step::InitializeStep, py::arg("aValue"))
      .def("IsFirstStepInVolume", &G4Step::IsFirstStepInVolume)
      .def("IsLastStepInVolume", &G4Step::IsLastStepInVolume)
      .def("NewSecondaryVector", &G4Step::NewSecondaryVector, py::return_value_policy::reference)
      .def("ResetNonIonizingEnergyDeposit", &G4Step::ResetNonIonizingEnergyDeposit)
      .def("ResetTotalEnergyDeposit", &G4Step::ResetTotalEnergyDeposit)
      .def("SetControlFlag", &G4Step::SetControlFlag, py::arg("StepControlFlag"))
      .def("SetFirstStepFlag", &G4Step::SetFirstStepFlag)
      .def("SetLastStepFlag", &G4Step::SetLastStepFlag)
      .def("SetNonIonizingEnergyDeposit", &G4Step::SetNonIonizingEnergyDeposit, py::arg("value"))
      .def("SetPointerToVectorOfAuxiliaryPoints", &G4Step::SetPointerToVectorOfAuxiliaryPoints, py::arg("vec"))
      .def("SetPostStepPoint", &G4Step::SetPostStepPoint, py::arg("value"))
      .def("SetPreStepPoint", &G4Step::SetPreStepPoint, py::arg("value"))
      .def("SetSecondary", &G4Step::SetSecondary, py::arg("value"))
      .def("SetStepLength", &G4Step::SetStepLength, py::arg("value"))
      .def("SetTotalEnergyDeposit", &G4Step::SetTotalEnergyDeposit, py::arg("value"))
      .def("SetTrack", &G4Step::SetTrack, py::arg("value"))
      .def("UpdateTrack", &G4Step::UpdateTrack);
}
