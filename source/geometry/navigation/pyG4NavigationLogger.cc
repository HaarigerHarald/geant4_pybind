#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4NavigationLogger.hh>
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
#include <G4SmartVoxelHeader.hh>
#include <G4VisAttributes.hh>
#include <G4VoxelLimits.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4NavigationLogger(py::module &m)
{
   py::class_<G4NavigationLogger>(m, "G4NavigationLogger")

      .def(py::init<const G4String &>(), py::arg("id"))
      .def("__copy__", [](const G4NavigationLogger &self) { return G4NavigationLogger(self); })
      .def("__deepcopy__", [](const G4NavigationLogger &self, py::dict) { return G4NavigationLogger(self); })
      .def("PreComputeStepLog", &G4NavigationLogger::PreComputeStepLog, py::arg("motherPhysical"),
           py::arg("motherSafety"), py::arg("localPoint"))

      .def("AlongComputeStepLog", &G4NavigationLogger::AlongComputeStepLog, py::arg("sampleSolid"),
           py::arg("samplePoint"), py::arg("sampleDirection"), py::arg("localDirection"), py::arg("sampleSafety"),
           py::arg("sampleStep"))

      .def("CheckDaughterEntryPoint", &G4NavigationLogger::CheckDaughterEntryPoint, py::arg("sampleSolid"),
           py::arg("samplePoint"), py::arg("sampleDirection"), py::arg("motherSolid"), py::arg("localPoint"),
           py::arg("localDirection"), py::arg("motherStep"), py::arg("sampleStep"))

      .def("PostComputeStepLog", &G4NavigationLogger::PostComputeStepLog, py::arg("motherSolid"), py::arg("localPoint"),
           py::arg("localDirection"), py::arg("motherStep"), py::arg("motherSafety"))

      .def("ComputeSafetyLog", &G4NavigationLogger::ComputeSafetyLog, py::arg("solid"), py::arg("point"),
           py::arg("safety"), py::arg("isMotherVolume"), py::arg("banner") = -1)

      .def("PrintDaughterLog", &G4NavigationLogger::PrintDaughterLog, py::arg("sampleSolid"), py::arg("samplePoint"),
           py::arg("sampleSafety"), py::arg("onlySafety"), py::arg("sampleDirection"), py::arg("sampleStep"))

      .def("CheckAndReportBadNormal",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4ThreeVector &, G4double,
                             const G4VSolid *, const char *>(&G4NavigationLogger::CheckAndReportBadNormal, py::const_),
           py::arg("unitNormal"), py::arg("localPoint"), py::arg("localDirection"), py::arg("step"), py::arg("solid"),
           py::arg("msg"))

      .def("CheckAndReportBadNormal",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4RotationMatrix &, const char *>(
              &G4NavigationLogger::CheckAndReportBadNormal, py::const_),
           py::arg("unitNormal"), py::arg("originalNormal"), py::arg("rotationM"), py::arg("msg"))

      .def("ReportOutsideMother", &G4NavigationLogger::ReportOutsideMother, py::arg("localPoint"),
           py::arg("localDirection"), py::arg("motherPV"), py::arg("tDist") = 30. * CLHEP::cm)

      .def("ReportVolumeAndIntersection", &G4NavigationLogger::ReportVolumeAndIntersection, py::arg("ostrm"),
           py::arg("localPoint"), py::arg("localDirection"), py::arg("physical"))

      .def("GetVerboseLevel", &G4NavigationLogger::GetVerboseLevel)
      .def("SetVerboseLevel", &G4NavigationLogger::SetVerboseLevel, py::arg("level"))
      .def("GetMinTriggerDistance", &G4NavigationLogger::GetMinTriggerDistance)
      .def("SetMinTriggerDistance", &G4NavigationLogger::SetMinTriggerDistance, py::arg("d"))
      .def("GetReportSoftWarnings", &G4NavigationLogger::GetReportSoftWarnings)
      .def("SetReportSoftWarnings", &G4NavigationLogger::SetReportSoftWarnings, py::arg("b"));
}
