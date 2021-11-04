#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4PropagatorInField.hh>
#include <G4MagneticField.hh>
#include <G4Track.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4ProductionCuts.hh>
#include <G4Material.hh>
#include <G4VUserRegionInformation.hh>
#include <G4MaterialCutsCouple.hh>
#include <G4UserLimits.hh>
#include <G4FastSimulationManager.hh>
#include <G4UserSteppingAction.hh>
#include <G4VSensitiveDetector.hh>
#include <G4VisAttributes.hh>
#include <G4Allocator.hh>
#include <G4ReferenceCountedHandle.hh>
#include <G4VoxelLimits.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>
#include <G4VoxelSafety.hh>
#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4Trd.hh>
#include <G4Trap.hh>
#include <G4Cons.hh>
#include <G4Sphere.hh>
#include <G4Orb.hh>
#include <G4Ellipsoid.hh>
#include <G4Torus.hh>
#include <G4Para.hh>
#include <G4Polycone.hh>
#include <G4Polyhedra.hh>
#include <G4Hype.hh>
#include <G4VFSALIntegrationStepper.hh>
#include <G4CachedMagneticField.hh>
#include <G4HelixHeum.hh>
#include <G4VCurvedTrajectoryFilter.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4PropagatorInField(py::module &m)
{
   py::class_<G4PropagatorInField>(m, "G4PropagatorInField")

      .def(py::init<G4Navigator *, G4FieldManager *, G4VIntersectionLocator *>(), py::arg("theNavigator"),
           py::arg("detectorFieldMgr"), py::arg("vLocator") = static_cast<G4VIntersectionLocator *>(nullptr))

      .def("__copy__", [](const G4PropagatorInField &self) { return G4PropagatorInField(self); })
      .def("__deepcopy__", [](const G4PropagatorInField &self, py::dict) { return G4PropagatorInField(self); })

      .def("ComputeStep", &G4PropagatorInField::ComputeStep, py::arg("pFieldTrack"),
           py::arg("pCurrentProposedStepLength"), py::arg("pNewSafety"),
           py::arg("pPhysVol") = static_cast<G4VPhysicalVolume *>(nullptr), py::arg("canRelaxDeltaChord") = false)

      .def("EndPosition", &G4PropagatorInField::EndPosition)
      .def("EndMomentumDir", &G4PropagatorInField::EndMomentumDir)
      .def("IsParticleLooping", &G4PropagatorInField::IsParticleLooping)
      .def("GetEpsilonStep", &G4PropagatorInField::GetEpsilonStep)
      .def("SetEpsilonStep", &G4PropagatorInField::SetEpsilonStep, py::arg("newEps"))
      .def("FindAndSetFieldManager", &G4PropagatorInField::FindAndSetFieldManager, py::arg("pCurrentPhysVol"),
           py::return_value_policy::reference)

      .def("GetChordFinder", &G4PropagatorInField::GetChordFinder, py::return_value_policy::reference)
      .def("SetVerboseLevel", &G4PropagatorInField::SetVerboseLevel, py::arg("verbose"))
      .def("GetVerboseLevel", &G4PropagatorInField::GetVerboseLevel)
      .def("Verbose", &G4PropagatorInField::Verbose)
      .def("CheckMode", &G4PropagatorInField::CheckMode, py::arg("mode"))
      .def("SetVerboseTrace", &G4PropagatorInField::SetVerboseTrace, py::arg("enable"))
      .def("GetVerboseTrace", &G4PropagatorInField::GetVerboseTrace)
      .def("GetMaxLoopCount", &G4PropagatorInField::GetMaxLoopCount)
      .def("SetMaxLoopCount", &G4PropagatorInField::SetMaxLoopCount, py::arg("new_max"))
      .def("printStatus", &G4PropagatorInField::printStatus, py::arg("startFT"), py::arg("currentFT"),
           py::arg("requestStep"), py::arg("safety"), py::arg("step"), py::arg("startVolume"))

      .def("GetEndState", &G4PropagatorInField::GetEndState)
      .def("GetMinimumEpsilonStep", &G4PropagatorInField::GetMinimumEpsilonStep)
      .def("SetMinimumEpsilonStep", &G4PropagatorInField::SetMinimumEpsilonStep, py::arg("newEpsMin"))
      .def("GetMaximumEpsilonStep", &G4PropagatorInField::GetMaximumEpsilonStep)
      .def("SetMaximumEpsilonStep", &G4PropagatorInField::SetMaximumEpsilonStep, py::arg("newEpsMax"))
      .def("SetLargestAcceptableStep", &G4PropagatorInField::SetLargestAcceptableStep, py::arg("newBigDist"))
      .def("GetLargestAcceptableStep", &G4PropagatorInField::GetLargestAcceptableStep)
      .def("SetTrajectoryFilter", &G4PropagatorInField::SetTrajectoryFilter, py::arg("filter"))
      .def("GimmeTrajectoryVectorAndForgetIt", &G4PropagatorInField::GimmeTrajectoryVectorAndForgetIt,
           py::return_value_policy::reference)

      .def("ClearPropagatorState", &G4PropagatorInField::ClearPropagatorState)
      .def("SetDetectorFieldManager", &G4PropagatorInField::SetDetectorFieldManager, py::arg("newGlobalFieldManager"))
      .def("SetUseSafetyForOptimization", &G4PropagatorInField::SetUseSafetyForOptimization)
      .def("GetUseSafetyForOptimization", &G4PropagatorInField::GetUseSafetyForOptimization)
      .def("IntersectChord", &G4PropagatorInField::IntersectChord, py::arg("StartPointA"), py::arg("EndPointB"),
           py::arg("NewSafety"), py::arg("LinearStepLength"), py::arg("IntersectionPoint"))

      .def("IsFirstStepInVolume", &G4PropagatorInField::IsFirstStepInVolume)
      .def("IsLastStepInVolume", &G4PropagatorInField::IsLastStepInVolume)
      .def("PrepareNewTrack", &G4PropagatorInField::PrepareNewTrack)
      .def("GetIntersectionLocator", &G4PropagatorInField::GetIntersectionLocator, py::return_value_policy::reference)
      .def("SetIntersectionLocator", &G4PropagatorInField::SetIntersectionLocator, py::arg("pLocator"))
      .def("GetIterationsToIncreaseChordDistance", &G4PropagatorInField::GetIterationsToIncreaseChordDistance)
      .def("SetIterationsToIncreaseChordDistance", &G4PropagatorInField::SetIterationsToIncreaseChordDistance,
           py::arg("numIters"))

      .def("GetDeltaIntersection", &G4PropagatorInField::GetDeltaIntersection)
      .def("GetDeltaOneStep", &G4PropagatorInField::GetDeltaOneStep)
      .def("GetCurrentFieldManager", &G4PropagatorInField::GetCurrentFieldManager, py::return_value_policy::reference)
      .def("GetCurrentEquationOfMotion", &G4PropagatorInField::GetCurrentEquationOfMotion,
           py::return_value_policy::reference)

      .def("SetNavigatorForPropagating", &G4PropagatorInField::SetNavigatorForPropagating,
           py::arg("SimpleOrMultiNavigator"))

      .def("GetNavigatorForPropagating", &G4PropagatorInField::GetNavigatorForPropagating,
           py::return_value_policy::reference)

      .def("SetThresholdNoZeroStep", &G4PropagatorInField::SetThresholdNoZeroStep, py::arg("noAct"), py::arg("noHarsh"),
           py::arg("noAbandon"))

      .def("GetThresholdNoZeroSteps", &G4PropagatorInField::GetThresholdNoZeroSteps, py::arg("i"))
      .def("GetZeroStepThreshold", &G4PropagatorInField::GetZeroStepThreshold)
      .def("SetZeroStepThreshold", &G4PropagatorInField::SetZeroStepThreshold, py::arg("newLength"))
      .def("RefreshIntersectionLocator", &G4PropagatorInField::RefreshIntersectionLocator);
}
