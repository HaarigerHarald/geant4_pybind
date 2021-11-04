#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4TwistedTrd.hh>
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

class PyG4TwistedTrd : public G4TwistedTrd, public py::trampoline_self_life_support {
public:
   using G4TwistedTrd::G4TwistedTrd;

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4TwistedTrd, GetEntityType, ); }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4TwistedTrd, Clone, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4TwistedTrd, StreamInfo, os);
   }

   void ComputeDimensions(G4VPVParameterisation *arg0, const G4int arg1, const G4VPhysicalVolume *arg2) override
   {
      PYBIND11_OVERRIDE(void, G4TwistedTrd, ComputeDimensions, arg0, arg1, arg2);
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4TwistedTrd, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4TwistedTrd::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pMin, G4double &pMax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4TwistedTrd, CalculateExtent, pAxis, pVoxelLimit, pTransform, pMin, pMax);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4TwistedTrd, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4TwistedTrd, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcnorm, G4bool *validnorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4TwistedTrd, DistanceToOut, p, v, calcnorm, validnorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4TwistedTrd, DistanceToOut, p);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4TwistedTrd, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4TwistedTrd, SurfaceNormal, p);
   }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4TwistedTrd, GetPointOnSurface, );
   }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4TwistedTrd, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4TwistedTrd, GetSurfaceArea, ); }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4TwistedTrd, "DescribeYourselfTo", std::addressof(scene));
      G4TwistedTrd::DescribeYourselfTo(scene);
   }

   G4Polyhedron *CreatePolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4TwistedTrd, CreatePolyhedron, );
   }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4TwistedTrd, GetPolyhedron, ); }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4TwistedTrd, GetExtent, ); }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4TwistedTrd, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4TwistedTrd, GetConstituentSolid, no);
   }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4TwistedTrd, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4TwistedTrd, GetDisplacedSolidPtr, );
   }
};

void export_G4TwistedTrd(py::module &m)
{
   py::class_<G4TwistedTrd, PyG4TwistedTrd, G4VTwistedFaceted>(m, "G4TwistedTrd")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double, G4double>(), py::arg("pName"),
           py::arg("pDx1"), py::arg("pDx2"), py::arg("pDy1"), py::arg("pDy2"), py::arg("pDz"), py::arg("pPhiTwist"))

      .def("__copy__", [](const PyG4TwistedTrd &self) { return PyG4TwistedTrd(self); })
      .def("__deepcopy__", [](const PyG4TwistedTrd &self, py::dict) { return PyG4TwistedTrd(self); })
      .def("GetX1HalfLength", &G4TwistedTrd::GetX1HalfLength)
      .def("GetX2HalfLength", &G4TwistedTrd::GetX2HalfLength)
      .def("GetY1HalfLength", &G4TwistedTrd::GetY1HalfLength)
      .def("GetY2HalfLength", &G4TwistedTrd::GetY2HalfLength)
      .def("GetZHalfLength", &G4TwistedTrd::GetZHalfLength)
      .def("GetPhiTwist", &G4TwistedTrd::GetPhiTwist)
      .def("GetEntityType", &G4TwistedTrd::GetEntityType)
      .def("Clone", &G4TwistedTrd::Clone, py::return_value_policy::reference)
      .def("StreamInfo", &G4TwistedTrd::StreamInfo, py::arg("os"));
}
