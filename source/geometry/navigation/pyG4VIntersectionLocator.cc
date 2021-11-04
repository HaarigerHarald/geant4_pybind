#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VIntersectionLocator.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4ProductionCuts.hh>
#include <G4Material.hh>
#include <G4VUserRegionInformation.hh>
#include <G4MaterialCutsCouple.hh>
#include <G4UserLimits.hh>
#include <G4FieldManager.hh>
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
#include <G4MagneticField.hh>
#include <G4CachedMagneticField.hh>
#include <G4HelixHeum.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VIntersectionLocator : public G4VIntersectionLocator, public py::trampoline_self_life_support {
public:
   using G4VIntersectionLocator::G4VIntersectionLocator;

   G4bool EstimateIntersectionPoint(const G4FieldTrack &curveStartPointTangent,
                                    const G4FieldTrack &curveEndPointTangent, const G4ThreeVector &trialPoint,
                                    G4FieldTrack &intersectPointTangent, G4bool &recalculatedEndPoint,
                                    G4double &fPreviousSafety, G4ThreeVector &fPreviousSftOrigin) override
   {
      PYBIND11_OVERRIDE_PURE(G4bool, G4VIntersectionLocator, EstimateIntersectionPoint, curveStartPointTangent,
                             curveEndPointTangent, trialPoint, std::addressof(intersectPointTangent),
                             recalculatedEndPoint, fPreviousSafety, std::addressof(fPreviousSftOrigin));
   }
};

void export_G4VIntersectionLocator(py::module &m)
{
   py::class_<G4VIntersectionLocator, PyG4VIntersectionLocator>(m, "G4VIntersectionLocator")

      .def(py::init<G4Navigator *>(), py::arg("theNavigator"))
      .def("__copy__", [](const PyG4VIntersectionLocator &self) { return PyG4VIntersectionLocator(self); })
      .def("__deepcopy__",
           [](const PyG4VIntersectionLocator &self, py::dict) { return PyG4VIntersectionLocator(self); })
      .def("EstimateIntersectionPoint", &G4VIntersectionLocator::EstimateIntersectionPoint,
           py::arg("curveStartPointTangent"), py::arg("curveEndPointTangent"), py::arg("trialPoint"),
           py::arg("intersectPointTangent"), py::arg("recalculatedEndPoint"), py::arg("fPreviousSafety"),
           py::arg("fPreviousSftOrigin"))

      .def("printStatus",
           py::overload_cast<const G4FieldTrack &, const G4FieldTrack &, G4double, G4double, G4int>(
              &G4VIntersectionLocator::printStatus),
           py::arg("startFT"), py::arg("currentFT"), py::arg("requestStep"), py::arg("safety"), py::arg("stepNum"))

      .def("IntersectChord", &G4VIntersectionLocator::IntersectChord, py::arg("StartPointA"), py::arg("EndPointB"),
           py::arg("NewSafety"), py::arg("PreviousSafety"), py::arg("PreviousSftOrigin"), py::arg("LinearStepLength"),
           py::arg("IntersectionPoint"), py::arg("calledNavigator") = static_cast<G4bool *>(nullptr))

      .def("SetEpsilonStepFor", &G4VIntersectionLocator::SetEpsilonStepFor, py::arg("EpsilonStep"))
      .def("SetDeltaIntersectionFor", &G4VIntersectionLocator::SetDeltaIntersectionFor, py::arg("deltaIntersection"))
      .def("SetNavigatorFor", &G4VIntersectionLocator::SetNavigatorFor, py::arg("fNavigator"))
      .def("SetChordFinderFor", &G4VIntersectionLocator::SetChordFinderFor, py::arg("fCFinder"))
      .def("SetVerboseFor", &G4VIntersectionLocator::SetVerboseFor, py::arg("fVerbose"))
      .def("GetVerboseFor", &G4VIntersectionLocator::GetVerboseFor)
      .def("GetDeltaIntersectionFor", &G4VIntersectionLocator::GetDeltaIntersectionFor)
      .def("GetEpsilonStepFor", &G4VIntersectionLocator::GetEpsilonStepFor)
      .def("GetNavigatorFor", &G4VIntersectionLocator::GetNavigatorFor, py::return_value_policy::reference)
      .def("GetChordFinderFor", &G4VIntersectionLocator::GetChordFinderFor, py::return_value_policy::reference)
      .def("SetSafetyParametersFor", &G4VIntersectionLocator::SetSafetyParametersFor, py::arg("UseSafety"))
      .def("AddAdjustementOfFoundIntersection", &G4VIntersectionLocator::AddAdjustementOfFoundIntersection,
           py::arg("UseCorrection"))

      .def("GetAdjustementOfFoundIntersection", &G4VIntersectionLocator::GetAdjustementOfFoundIntersection)
      //.def("AdjustIntersections", &G4VIntersectionLocator::AdjustIntersections, py::arg("UseCorrection"))
      .def("AreIntersectionsAdjusted", &G4VIntersectionLocator::AreIntersectionsAdjusted)
      .def_static("printStatus_",
                  py::overload_cast<G4FieldTrack const &, G4FieldTrack const &, G4double, G4double, G4int,
                                    std::ostream &, G4int>(&G4VIntersectionLocator::printStatus),
                  py::arg("startFT"), py::arg("currentFT"), py::arg("requestStep"), py::arg("safety"),
                  py::arg("stepNum"), py::arg("oss"), py::arg("verboseLevel"))

      .def("SetCheckMode", &G4VIntersectionLocator::SetCheckMode, py::arg("value"))
      .def("GetCheckMode", &G4VIntersectionLocator::GetCheckMode);
}
