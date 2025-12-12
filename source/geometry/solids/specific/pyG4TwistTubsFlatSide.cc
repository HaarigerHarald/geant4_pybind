#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4TwistTubsFlatSide.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4TwistTubsFlatSide : public G4TwistTubsFlatSide, public py::trampoline_self_life_support {
public:
   using G4TwistTubsFlatSide::G4TwistTubsFlatSide;

   G4ThreeVector GetNormal(const G4ThreeVector &arg0, G4bool isGlobal) override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4TwistTubsFlatSide, GetNormal, arg0, isGlobal);
   }

   G4int DistanceToSurface(const G4ThreeVector &gp, const G4ThreeVector &gv, G4ThreeVector *gxx, G4double *distance,
                           G4int *areacode, G4bool *isvalid, G4VTwistSurface::EValidate validate) override
   {
      PYBIND11_OVERRIDE(G4int, G4TwistTubsFlatSide, DistanceToSurface, gp, gv, gxx, distance, areacode, isvalid,
                        validate);
   }

   G4int DistanceToSurface(const G4ThreeVector &gp, G4ThreeVector *gxx, G4double *distance, G4int *areacode) override
   {
      PYBIND11_OVERRIDE(G4int, G4TwistTubsFlatSide, DistanceToSurface, gp, gxx, distance, areacode);
   }

   G4int AmIOnLeftSide(const G4ThreeVector &me, const G4ThreeVector &vec, G4bool withTol) override
   {
      PYBIND11_OVERRIDE(G4int, G4TwistTubsFlatSide, AmIOnLeftSide, me, vec, withTol);
   }

   G4double DistanceToBoundary(G4int areacode, G4ThreeVector &xx, const G4ThreeVector &p) override
   {
      PYBIND11_OVERRIDE_IMPL(G4double, G4TwistTubsFlatSide, "DistanceToBoundary", areacode, std::addressof(xx), p);
      return G4TwistTubsFlatSide::DistanceToBoundary(areacode, xx, p);
   }

   G4double DistanceToIn(const G4ThreeVector &gp, const G4ThreeVector &gv, G4ThreeVector &gxxbest) override
   {
      PYBIND11_OVERRIDE_IMPL(G4double, G4TwistTubsFlatSide, "DistanceToIn", gp, gv, std::addressof(gxxbest));
      return G4TwistTubsFlatSide::DistanceToIn(gp, gv, gxxbest);
   }

   G4double DistanceToOut(const G4ThreeVector &gp, const G4ThreeVector &gv, G4ThreeVector &gxxbest) override
   {
      PYBIND11_OVERRIDE_IMPL(G4double, G4TwistTubsFlatSide, "DistanceToOut", gp, gv, std::addressof(gxxbest));
      return G4TwistTubsFlatSide::DistanceToOut(gp, gv, gxxbest);
   }

   G4double DistanceTo(const G4ThreeVector &gp, G4ThreeVector &gxx) override
   {
      PYBIND11_OVERRIDE_IMPL(G4double, G4TwistTubsFlatSide, "DistanceTo", gp, std::addressof(gxx));
      return G4TwistTubsFlatSide::DistanceTo(gp, gxx);
   }

   void GetBoundaryParameters(const G4int &areacode, G4ThreeVector &d, G4ThreeVector &x0,
                              G4int &boundarytype) const override
   {
      PYBIND11_OVERRIDE(void, G4TwistTubsFlatSide, GetBoundaryParameters, areacode, d, x0, boundarytype);
   }

   G4ThreeVector GetBoundaryAtPZ(G4int areacode, const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4TwistTubsFlatSide, GetBoundaryAtPZ, areacode, p);
   }

   void SetBoundary(const G4int &axiscode, const G4ThreeVector &direction, const G4ThreeVector &x0,
                    const G4int &boundarytype) override
   {
      PYBIND11_OVERRIDE(void, G4TwistTubsFlatSide, SetBoundary, axiscode, direction, x0, boundarytype);
   }
};

void export_G4TwistTubsFlatSide(py::module &m)
{
   py::class_<G4TwistTubsFlatSide, PyG4TwistTubsFlatSide, G4VTwistSurface>(m, "G4TwistTubsFlatSide")

      .def(py::init<const G4String &, const G4RotationMatrix &, const G4ThreeVector &, const G4ThreeVector &,
                    const EAxis, const EAxis, G4double, G4double, G4double, G4double>(),
           py::arg("name"), py::arg("rot"), py::arg("tlate"), py::arg("n"), py::arg("axis1") = kRho,
           py::arg("axis2") = kPhi, py::arg("axis0min") = -kInfinity, py::arg("axis1min") = -kInfinity,
           py::arg("axis0max") = kInfinity, py::arg("axis1max") = kInfinity)

      .def(py::init<const G4String &, G4double *, G4double *, G4double, G4double *, G4double *, G4int>(),
           py::arg("name"), py::arg("EndInnerRadius"), py::arg("EndOuterRadius"), py::arg("DPhi"), py::arg("EndPhi"),
           py::arg("EndZ"), py::arg("handedness"))

      .def("__copy__", [](const PyG4TwistTubsFlatSide &self) { return PyG4TwistTubsFlatSide(self); })
      .def("__deepcopy__", [](const PyG4TwistTubsFlatSide &self, py::dict) { return PyG4TwistTubsFlatSide(self); })
      .def("GetNormal", &G4TwistTubsFlatSide::GetNormal, py::arg("arg0"), py::arg("isGlobal") = false)
      .def("DistanceToSurface",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, G4ThreeVector *, G4double *, G4int *,
                             G4bool *, G4VTwistSurface::EValidate>(&G4TwistTubsFlatSide::DistanceToSurface),
           py::arg("gp"), py::arg("gv"), py::arg("gxx"), py::arg("distance"), py::arg("areacode"), py::arg("isvalid"),
           py::arg("validate") = G4VTwistSurface::kValidateWithTol)

      .def("DistanceToSurface",
           py::overload_cast<const G4ThreeVector &, G4ThreeVector *, G4double *, G4int *>(
              &G4TwistTubsFlatSide::DistanceToSurface),
           py::arg("gp"), py::arg("gxx"), py::arg("distance"), py::arg("areacode"));
}
