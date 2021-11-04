#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4CSGSolid.hh>
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

class PyG4CSGSolid : public G4CSGSolid, public py::trampoline_self_life_support {
public:
   using G4CSGSolid::G4CSGSolid;

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pMin, G4double &pMax) const override
   {
      PYBIND11_OVERRIDE_PURE(G4bool, G4CSGSolid, CalculateExtent, pAxis, pVoxelLimit, pTransform, pMin, pMax);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE_PURE(EInside, G4CSGSolid, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE_PURE(G4ThreeVector, G4CSGSolid, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4CSGSolid, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4CSGSolid, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4CSGSolid, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4CSGSolid, DistanceToOut, p);
   }

   G4GeometryType GetEntityType() const override
   {
      PYBIND11_OVERRIDE_PURE(G4GeometryType, G4CSGSolid, GetEntityType, );
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_PURE(void, G4CSGSolid, DescribeYourselfTo, std::addressof(scene));
   }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4CSGSolid, StreamInfo, os);
   }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4CSGSolid, GetPolyhedron, ); }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4CSGSolid, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4CSGSolid::BoundingLimits(pMin, pMax);
   }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4CSGSolid, ComputeDimensions, p, n, pRep);
   }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4CSGSolid, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4CSGSolid, GetSurfaceArea, ); }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4CSGSolid, GetPointOnSurface, );
   }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4CSGSolid, Clone, ); }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4CSGSolid, GetExtent, ); }

   G4Polyhedron *CreatePolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4CSGSolid, CreatePolyhedron, );
   }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4CSGSolid, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4CSGSolid, GetConstituentSolid, no);
   }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4CSGSolid, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4CSGSolid, GetDisplacedSolidPtr, );
   }
};

void export_G4CSGSolid(py::module &m)
{
   py::class_<G4CSGSolid, PyG4CSGSolid, G4VSolid, py::nodelete>(m, "G4CSGSolid")

      .def(py::init<const G4String &>(), py::arg("pName"))
      .def("__copy__", [](const PyG4CSGSolid &self) { return PyG4CSGSolid(self); })
      .def("__deepcopy__", [](const PyG4CSGSolid &self, py::dict) { return PyG4CSGSolid(self); })
      .def("StreamInfo", &G4CSGSolid::StreamInfo, py::arg("os"))
      .def("GetPolyhedron", &G4CSGSolid::GetPolyhedron, py::return_value_policy::reference);
}
