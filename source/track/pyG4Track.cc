#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Track.hh>
#include <G4GeomSplitter.hh>
#include <G4ProductionCuts.hh>
#include <G4VUserRegionInformation.hh>
#include <G4MaterialCutsCouple.hh>
#include <G4UserLimits.hh>
#include <G4FieldManager.hh>
#include <G4FastSimulationManager.hh>
#include <G4UserSteppingAction.hh>
#include <G4VPVParameterisation.hh>
#include <G4VSensitiveDetector.hh>
#include <G4VSolid.hh>
#include <G4SmartVoxelHeader.hh>
#include <G4VisAttributes.hh>
#include <G4ProcessManager.hh>
#include <G4VTrackingManager.hh>
#include <G4DecayTable.hh>
#include <G4ParticleTable.hh>
#include <G4ParticlePropertyTable.hh>
#include <G4PrimaryParticle.hh>
#include <G4DecayProducts.hh>
#include <G4NavigationHistory.hh>
#include <G4ReferenceCountedHandle.hh>
#include <G4DensityEffectData.hh>
#include <G4DensityEffectCalculator.hh>
#include <G4Run.hh>
#include <G4Event.hh>
#include <G4VAuxiliaryTrackInformation.hh>
#include <G4VProcess.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Track(py::module &m)
{
   py::class_<G4Track>(m, "G4Track")

      .def(py::init<>())
      .def(py::init<G4DynamicParticle *, G4double, const G4ThreeVector &>(), py::arg("apValueDynamicParticle"),
           py::arg("aValueTime"), py::arg("aValuePosition"))

      .def("__copy__", [](const G4Track &self) { return new G4Track(self); })
      .def("__deepcopy__", [](const G4Track &self, py::dict) { return new G4Track(self); })
      .def("AddTrackLength", &G4Track::AddTrackLength, py::arg("aValue"))
      .def("CalculateVelocity", &G4Track::CalculateVelocity)
      .def("CalculateVelocityForOpticalPhoton", &G4Track::CalculateVelocityForOpticalPhoton)
      .def("CopyTrackInfo", &G4Track::CopyTrackInfo)
      .def("GetAuxiliaryTrackInformation", &G4Track::GetAuxiliaryTrackInformation, py::arg("id"),
           py::return_value_policy::reference)

      .def("GetAuxiliaryTrackInformationMap", &G4Track::GetAuxiliaryTrackInformationMap,
           py::return_value_policy::reference)

      .def("GetCreatorModelID", &G4Track::GetCreatorModelID)
      .def("GetCreatorModelIndex", &G4Track::GetCreatorModelIndex)
      .def("GetCreatorModelName", &G4Track::GetCreatorModelName)
      .def("GetCreatorProcess", &G4Track::GetCreatorProcess, py::return_value_policy::reference)
      .def("GetCurrentStepNumber", &G4Track::GetCurrentStepNumber)
      .def("GetDefinition", &G4Track::GetDefinition, py::return_value_policy::reference)
      .def("GetDynamicParticle", &G4Track::GetDynamicParticle, py::return_value_policy::reference)
      .def("GetGlobalTime", &G4Track::GetGlobalTime)
      .def("GetKineticEnergy", &G4Track::GetKineticEnergy)
      .def("GetLocalTime", &G4Track::GetLocalTime)
      .def("GetLogicalVolumeAtVertex", &G4Track::GetLogicalVolumeAtVertex, py::return_value_policy::reference)
      .def("GetMaterial", &G4Track::GetMaterial, py::return_value_policy::reference)
      .def("GetMaterialCutsCouple", &G4Track::GetMaterialCutsCouple, py::return_value_policy::reference)
      .def("GetMomentum", &G4Track::GetMomentum)
      .def("GetMomentumDirection", &G4Track::GetMomentumDirection)
      .def("GetNextMaterial", &G4Track::GetNextMaterial, py::return_value_policy::reference)
      .def("GetNextMaterialCutsCouple", &G4Track::GetNextMaterialCutsCouple, py::return_value_policy::reference)
      .def("GetNextTouchable", &G4Track::GetNextTouchable, py::return_value_policy::reference)
      .def("GetNextTouchableHandle", &G4Track::GetNextTouchableHandle)
      .def("GetNextVolume", &G4Track::GetNextVolume, py::return_value_policy::reference)
      .def("GetOriginTouchable", &G4Track::GetOriginTouchable, py::return_value_policy::reference)
      .def("GetOriginTouchableHandle", &G4Track::GetOriginTouchableHandle)
      .def("GetParentID", &G4Track::GetParentID)
      .def("GetParticleDefinition", &G4Track::GetParticleDefinition, py::return_value_policy::reference)
      .def("GetPolarization", &G4Track::GetPolarization)
      .def("GetPosition", &G4Track::GetPosition)
      .def("GetProperTime", &G4Track::GetProperTime)
      .def("GetStep", &G4Track::GetStep, py::return_value_policy::reference)
      .def("GetStepLength", &G4Track::GetStepLength)
      .def("GetTotalEnergy", &G4Track::GetTotalEnergy)
      .def("GetTouchable", &G4Track::GetTouchable, py::return_value_policy::reference)
      .def("GetTouchableHandle", &G4Track::GetTouchableHandle)
      .def("GetTrackID", &G4Track::GetTrackID)
      .def("GetTrackLength", &G4Track::GetTrackLength)
      .def("GetTrackStatus", &G4Track::GetTrackStatus)
      .def("GetUserInformation", &G4Track::GetUserInformation, py::return_value_policy::reference)
      .def("GetVelocity", &G4Track::GetVelocity)
      .def("GetVertexKineticEnergy", &G4Track::GetVertexKineticEnergy)
      .def("GetVertexMomentumDirection", &G4Track::GetVertexMomentumDirection)
      .def("GetVertexPosition", &G4Track::GetVertexPosition)
      .def("GetVolume", &G4Track::GetVolume, py::return_value_policy::reference)
      .def("GetWeight", &G4Track::GetWeight)
      .def("IncrementCurrentStepNumber", &G4Track::IncrementCurrentStepNumber)
      .def("IsBelowThreshold", &G4Track::IsBelowThreshold)
      .def("IsGoodForTracking", &G4Track::IsGoodForTracking)
      .def("RemoveAuxiliaryTrackInformation", py::overload_cast<G4int>(&G4Track::RemoveAuxiliaryTrackInformation),
           py::arg("id"))

      .def(
         "RemoveAuxiliaryTrackInformation",
         [](G4Track &self, G4String &name) {
            self.RemoveAuxiliaryTrackInformation(name);
            return name;
         },
         py::arg("name"))

      .def("SetAuxiliaryTrackInformation", &G4Track::SetAuxiliaryTrackInformation, py::arg("id"), py::arg("info"))
      .def("SetBelowThresholdFlag", &G4Track::SetBelowThresholdFlag, py::arg("value") = true)
      .def("SetCreatorModelID", &G4Track::SetCreatorModelID, py::arg("id"))
      .def("SetCreatorProcess", &G4Track::SetCreatorProcess, py::arg("aValue"))
      .def("SetGlobalTime", &G4Track::SetGlobalTime, py::arg("aValue"))
      .def("SetGoodForTrackingFlag", &G4Track::SetGoodForTrackingFlag, py::arg("value") = true)
      .def("SetKineticEnergy", &G4Track::SetKineticEnergy, py::arg("aValue"))
      .def("SetLocalTime", &G4Track::SetLocalTime, py::arg("aValue"))
      .def("SetLogicalVolumeAtVertex", &G4Track::SetLogicalVolumeAtVertex)
      .def("SetMomentumDirection", &G4Track::SetMomentumDirection, py::arg("aValue"))
      .def("SetNextTouchableHandle", &G4Track::SetNextTouchableHandle, py::arg("apValue"))
      .def("SetOriginTouchableHandle", &G4Track::SetOriginTouchableHandle, py::arg("apValue"))
      .def("SetParentID", &G4Track::SetParentID, py::arg("aValue"))
      .def("SetPolarization", &G4Track::SetPolarization, py::arg("aValue"))
      .def("SetPosition", &G4Track::SetPosition, py::arg("aValue"))
      .def("SetProperTime", &G4Track::SetProperTime, py::arg("aValue"))
      .def("SetStep", &G4Track::SetStep, py::arg("aValue"))
      .def("SetStepLength", &G4Track::SetStepLength, py::arg("value"))
      .def("SetTouchableHandle", &G4Track::SetTouchableHandle, py::arg("apValue"))
      .def("SetTrackID", &G4Track::SetTrackID, py::arg("aValue"))
      .def("SetTrackStatus", &G4Track::SetTrackStatus, py::arg("aTrackStatus"))
      .def("SetUserInformation", &G4Track::SetUserInformation, py::arg("aValue"))
      .def("SetVelocity", &G4Track::SetVelocity, py::arg("val"))
      .def("SetVertexKineticEnergy", &G4Track::SetVertexKineticEnergy, py::arg("aValue"))
      .def("SetVertexMomentumDirection", &G4Track::SetVertexMomentumDirection, py::arg("aValue"))
      .def("SetVertexPosition", &G4Track::SetVertexPosition, py::arg("aValue"))
      .def("SetWeight", &G4Track::SetWeight, py::arg("aValue"))
      .def("UseGivenVelocity", py::overload_cast<>(&G4Track::UseGivenVelocity, py::const_))
      .def("UseGivenVelocity", py::overload_cast<G4bool>(&G4Track::UseGivenVelocity), py::arg("val"));
}
