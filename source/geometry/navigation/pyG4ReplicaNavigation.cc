#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ReplicaNavigation.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4VPVParameterisation.hh>
#include <G4ProductionCuts.hh>
#include <G4Material.hh>
#include <G4VUserRegionInformation.hh>
#include <G4MaterialCutsCouple.hh>
#include <G4UserLimits.hh>
#include <G4FieldManager.hh>
#include <G4FastSimulationManager.hh>
#include <G4UserSteppingAction.hh>
#include <G4VSensitiveDetector.hh>
#include <G4VSolid.hh>
#include <G4VisAttributes.hh>
#include <G4VoxelLimits.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4ReplicaNavigation(py::module &m)
{
   py::class_<G4ExitNormal> mG4ExitNormal(m, "G4ExitNormal");

   py::enum_<G4ExitNormal::ESide>(mG4ExitNormal, "ESide")
      .value("kNull", G4ExitNormal::kNull)
      .value("kRMin", G4ExitNormal::kRMin)
      .value("kRMax", G4ExitNormal::kRMax)
      .value("kSPhi", G4ExitNormal::kSPhi)
      .value("kEPhi", G4ExitNormal::kEPhi)
      .value("kPX", G4ExitNormal::kPX)
      .value("kMX", G4ExitNormal::kMX)
      .value("kPY", G4ExitNormal::kPY)
      .value("kMY", G4ExitNormal::kMY)
      .value("kPZ", G4ExitNormal::kPZ)
      .value("kMZ", G4ExitNormal::kMZ)
      .value("kMother", G4ExitNormal::kMother)
      .export_values();

   mG4ExitNormal
      .def(py::init<G4ThreeVector, G4bool, G4bool, G4ExitNormal::ESide>(), py::arg("norm") = G4ThreeVector(0., 0., 0.),
           py::arg("calc") = false, py::arg("valid") = false, py::arg("side") = G4ExitNormal::kNull)

      .def("__copy__", [](const G4ExitNormal &self) { return G4ExitNormal(self); })
      .def("__deepcopy__", [](const G4ExitNormal &self, py::dict) { return G4ExitNormal(self); })
      .def_readwrite("exitNormal", &G4ExitNormal::exitNormal)
      .def_readwrite("calculated", &G4ExitNormal::calculated)
      .def_readwrite("validConvex", &G4ExitNormal::validConvex)
      .def_readwrite("exitSide", &G4ExitNormal::exitSide);

   py::class_<G4ReplicaNavigation>(m, "G4ReplicaNavigation")

      .def(py::init<>())
      .def("__copy__", [](const G4ReplicaNavigation &self) { return G4ReplicaNavigation(self); })
      .def("__deepcopy__", [](const G4ReplicaNavigation &self, py::dict) { return G4ReplicaNavigation(self); })
      .def("LevelLocate", &G4ReplicaNavigation::LevelLocate, py::arg("history"), py::arg("blockedVol"),
           py::arg("blockedNum"), py::arg("globalPoint"), py::arg("globalDirection"), py::arg("pLocatedOnEdge"),
           py::arg("localPoint"))

      //  .def("ComputeStep", &G4ReplicaNavigation::ComputeStep, py::arg("globalPoint"), py::arg("globalDirection"),
      //       py::arg("localPoint"), py::arg("localDirection"), py::arg("currentProposedStepLength"),
      //       py::arg("newSafety"), py::arg("history"), py::arg("validExitNormal"), py::arg("calculatedExitNormal"),
      //       py::arg("exitNormal"), py::arg("exiting"), py::arg("entering"), py::arg("pBlockedPhysical"),
      //       py::arg("blockedReplicaNo"))

      .def("ComputeSafety", &G4ReplicaNavigation::ComputeSafety, py::arg("globalPoint"), py::arg("localPoint"),
           py::arg("history"), py::arg("pProposedMaxLength") = DBL_MAX)

      .def("BackLocate", &G4ReplicaNavigation::BackLocate, py::arg("history"), py::arg("globalPoint"),
           py::arg("localPoint"), py::arg("exiting"), py::arg("notKnownInside"))

      .def("ComputeTransformation",
           py::overload_cast<const G4int, G4VPhysicalVolume *, G4ThreeVector &>(
              &G4ReplicaNavigation::ComputeTransformation, py::const_),
           py::arg("replicaNo"), py::arg("pVol"), py::arg("point"))

      .def("ComputeTransformation",
           py::overload_cast<const G4int, G4VPhysicalVolume *>(&G4ReplicaNavigation::ComputeTransformation, py::const_),
           py::arg("replicaNo"), py::arg("pVol"))

      .def("Inside", &G4ReplicaNavigation::Inside, py::arg("pVol"), py::arg("replicaNo"), py::arg("localPoint"))
      .def("DistanceToOut",
           py::overload_cast<const G4VPhysicalVolume *, const G4int, const G4ThreeVector &>(
              &G4ReplicaNavigation::DistanceToOut, py::const_),
           py::arg("pVol"), py::arg("replicaNo"), py::arg("localPoint"))

      .def("DistanceToOut",
           py::overload_cast<const G4VPhysicalVolume *, const G4int, const G4ThreeVector &, const G4ThreeVector &,
                             G4ExitNormal &>(&G4ReplicaNavigation::DistanceToOut, py::const_),
           py::arg("pVol"), py::arg("replicaNo"), py::arg("localPoint"), py::arg("localDirection"),
           py::arg("candidateNormal"))

      .def("GetVerboseLevel", &G4ReplicaNavigation::GetVerboseLevel)
      .def("SetVerboseLevel", &G4ReplicaNavigation::SetVerboseLevel, py::arg("level"))
      .def("CheckMode", &G4ReplicaNavigation::CheckMode, py::arg("mode"));
}
