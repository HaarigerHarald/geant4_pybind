#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4MultiLevelLocator.hh>
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

class PyG4MultiLevelLocator : public G4MultiLevelLocator, public py::trampoline_self_life_support {
public:
   using G4MultiLevelLocator::G4MultiLevelLocator;

   G4bool EstimateIntersectionPoint(const G4FieldTrack &curveStartPointTangent,
                                    const G4FieldTrack &curveEndPointTangent, const G4ThreeVector &trialPoint,
                                    G4FieldTrack &intersectPointTangent, G4bool &recalculatedEndPoint,
                                    G4double &fPreviousSafety, G4ThreeVector &fPreviousSftOrigin) override
   {
      PYBIND11_OVERRIDE(G4bool, G4MultiLevelLocator, EstimateIntersectionPoint, curveStartPointTangent,
                        curveEndPointTangent, trialPoint, intersectPointTangent, recalculatedEndPoint, fPreviousSafety,
                        fPreviousSftOrigin);
   }
};

void export_G4MultiLevelLocator(py::module &m)
{
   py::class_<G4MultiLevelLocator, PyG4MultiLevelLocator, G4VIntersectionLocator>(m, "G4MultiLevelLocator")

      .def(py::init<G4Navigator *>(), py::arg("theNavigator"))
      .def("__copy__", [](const PyG4MultiLevelLocator &self) { return PyG4MultiLevelLocator(self); })
      .def("__deepcopy__", [](const PyG4MultiLevelLocator &self, py::dict) { return PyG4MultiLevelLocator(self); })
      .def("EstimateIntersectionPoint", &G4MultiLevelLocator::EstimateIntersectionPoint,
           py::arg("curveStartPointTangent"), py::arg("curveEndPointTangent"), py::arg("trialPoint"),
           py::arg("intersectPointTangent"), py::arg("recalculatedEndPoint"), py::arg("fPreviousSafety"),
           py::arg("fPreviousSftOrigin"))

      .def("ReportStatistics", &G4MultiLevelLocator::ReportStatistics)
      .def("SetMaxSteps", &G4MultiLevelLocator::SetMaxSteps, py::arg("valMax"))
      .def("SetWarnSteps", &G4MultiLevelLocator::SetWarnSteps, py::arg("valWarn"));
}
