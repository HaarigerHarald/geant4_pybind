#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4SimpleLocator.hh>
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

class PyG4SimpleLocator : public G4SimpleLocator, public py::trampoline_self_life_support {
public:
   using G4SimpleLocator::G4SimpleLocator;

   G4bool EstimateIntersectionPoint(const G4FieldTrack &curveStartPointTangent,
                                    const G4FieldTrack &curveEndPointTangent, const G4ThreeVector &trialPoint,
                                    G4FieldTrack &intersectPointTangent, G4bool &recalculatedEndPoint,
                                    G4double &fPreviousSafety, G4ThreeVector &fPreviousSftOrigin) override
   {
      PYBIND11_OVERRIDE(G4bool, G4SimpleLocator, EstimateIntersectionPoint, curveStartPointTangent,
                        curveEndPointTangent, trialPoint, intersectPointTangent, recalculatedEndPoint, fPreviousSafety,
                        fPreviousSftOrigin);
   }
};

void export_G4SimpleLocator(py::module &m)
{
   py::class_<G4SimpleLocator, PyG4SimpleLocator, G4VIntersectionLocator>(m, "G4SimpleLocator")

      .def(py::init<G4Navigator *>(), py::arg("aNavigator"))
      .def("__copy__", [](const PyG4SimpleLocator &self) { return PyG4SimpleLocator(self); })
      .def("__deepcopy__", [](const PyG4SimpleLocator &self, py::dict) { return PyG4SimpleLocator(self); })
      .def("EstimateIntersectionPoint", &G4SimpleLocator::EstimateIntersectionPoint, py::arg("curveStartPointTangent"),
           py::arg("curveEndPointTangent"), py::arg("trialPoint"), py::arg("intersectPointTangent"),
           py::arg("recalculatedEndPoint"), py::arg("fPreviousSafety"), py::arg("fPreviousSftOrigin"));
}
