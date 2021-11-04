#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4TwistedTrap.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>
#include <G4SolidExtentList.hh>
#include <G4ClippablePolygon.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4TwistedTrap : public G4TwistedTrap, public py::trampoline_self_life_support {
public:
   using G4TwistedTrap::G4TwistedTrap;

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4TwistedTrap, GetEntityType, ); }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4TwistedTrap, Clone, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4TwistedTrap, StreamInfo, os);
   }

   void ComputeDimensions(G4VPVParameterisation *arg0, const G4int arg1, const G4VPhysicalVolume *arg2) override
   {
      PYBIND11_OVERRIDE(void, G4TwistedTrap, ComputeDimensions, arg0, arg1, arg2);
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4TwistedTrap, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4TwistedTrap::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pMin, G4double &pMax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4TwistedTrap, CalculateExtent, pAxis, pVoxelLimit, pTransform, pMin, pMax);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4TwistedTrap, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4TwistedTrap, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcnorm, G4bool *validnorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4TwistedTrap, DistanceToOut, p, v, calcnorm, validnorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4TwistedTrap, DistanceToOut, p);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4TwistedTrap, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4TwistedTrap, SurfaceNormal, p);
   }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4TwistedTrap, GetPointOnSurface, );
   }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4TwistedTrap, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4TwistedTrap, GetSurfaceArea, ); }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4TwistedTrap, "DescribeYourselfTo", std::addressof(scene));
      G4TwistedTrap::DescribeYourselfTo(scene);
   }

   G4Polyhedron *CreatePolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4TwistedTrap, CreatePolyhedron, );
   }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4TwistedTrap, GetPolyhedron, ); }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4TwistedTrap, GetExtent, ); }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4TwistedTrap, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4TwistedTrap, GetConstituentSolid, no);
   }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4TwistedTrap, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4TwistedTrap, GetDisplacedSolidPtr, );
   }
};

void export_G4TwistedTrap(py::module &m)
{
   py::class_<G4TwistedTrap, PyG4TwistedTrap, G4VTwistedFaceted>(m, "G4TwistedTrap")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double>(), py::arg("pName"),
           py::arg("pPhiTwist"), py::arg("pDx1"), py::arg("pDx2"), py::arg("pDy"), py::arg("pDz"))

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double, G4double, G4double, G4double,
                    G4double, G4double, G4double>(),
           py::arg("pName"), py::arg("pPhiTwist"), py::arg("pDz"), py::arg("pTheta"), py::arg("pPhi"), py::arg("pDy1"),
           py::arg("pDx1"), py::arg("pDx2"), py::arg("pDy2"), py::arg("pDx3"), py::arg("pDx4"), py::arg("pAlph"))

      .def("__copy__", [](const PyG4TwistedTrap &self) { return PyG4TwistedTrap(self); })
      .def("__deepcopy__", [](const PyG4TwistedTrap &self, py::dict) { return PyG4TwistedTrap(self); })
      .def("GetY1HalfLength", &G4TwistedTrap::GetY1HalfLength)
      .def("GetX1HalfLength", &G4TwistedTrap::GetX1HalfLength)
      .def("GetX2HalfLength", &G4TwistedTrap::GetX2HalfLength)
      .def("GetY2HalfLength", &G4TwistedTrap::GetY2HalfLength)
      .def("GetX3HalfLength", &G4TwistedTrap::GetX3HalfLength)
      .def("GetX4HalfLength", &G4TwistedTrap::GetX4HalfLength)
      .def("GetZHalfLength", &G4TwistedTrap::GetZHalfLength)
      .def("GetPhiTwist", &G4TwistedTrap::GetPhiTwist)
      .def("GetTiltAngleAlpha", &G4TwistedTrap::GetTiltAngleAlpha)
      .def("GetPolarAngleTheta", &G4TwistedTrap::GetPolarAngleTheta)
      .def("GetAzimuthalAnglePhi", &G4TwistedTrap::GetAzimuthalAnglePhi)
      .def("GetEntityType", &G4TwistedTrap::GetEntityType)
      .def("Clone", &G4TwistedTrap::Clone, py::return_value_policy::reference)
      .def("StreamInfo", &G4TwistedTrap::StreamInfo, py::arg("os"));
}
