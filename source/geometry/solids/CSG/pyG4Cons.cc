#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Cons.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>
#include <G4VisAttributes.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4Cons : public G4Cons, public py::trampoline_self_life_support {
public:
   using G4Cons::G4Cons;

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4Cons, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4Cons, GetSurfaceArea, ); }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4Cons, ComputeDimensions, p, n, pRep);
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Cons, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4Cons::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pMin, G4double &pMax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4Cons, CalculateExtent, pAxis, pVoxelLimit, pTransform, pMin, pMax);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4Cons, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4Cons, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Cons, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Cons, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Cons, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Cons, DistanceToOut, p);
   }

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4Cons, GetEntityType, ); }

   G4ThreeVector GetPointOnSurface() const override { PYBIND11_OVERRIDE(G4ThreeVector, G4Cons, GetPointOnSurface, ); }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4Cons, Clone, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4Cons, StreamInfo, os);
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Cons, "DescribeYourselfTo", std::addressof(scene));
      G4Cons::DescribeYourselfTo(scene);
   }

   G4Polyhedron *CreatePolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Cons, CreatePolyhedron, ); }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Cons, GetPolyhedron, ); }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4Cons, GetExtent, ); }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4Cons, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override { PYBIND11_OVERRIDE(G4VSolid *, G4Cons, GetConstituentSolid, no); }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4Cons, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4Cons, GetDisplacedSolidPtr, );
   }
};

void export_G4Cons(py::module &m)
{
   py::class_<G4Cons, PyG4Cons, G4CSGSolid, py::nodelete>(m, "G4Cons")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double, G4double, G4double>(),
           py::arg("pName"), py::arg("pRmin1"), py::arg("pRmax1"), py::arg("pRmin2"), py::arg("pRmax2"), py::arg("pDz"),
           py::arg("pSPhi"), py::arg("pDPhi"))

      .def("__copy__", [](const PyG4Cons &self) { return PyG4Cons(self); })
      .def("__deepcopy__", [](const PyG4Cons &self, py::dict) { return PyG4Cons(self); })
      .def("GetInnerRadiusMinusZ", &G4Cons::GetInnerRadiusMinusZ)
      .def("GetOuterRadiusMinusZ", &G4Cons::GetOuterRadiusMinusZ)
      .def("GetInnerRadiusPlusZ", &G4Cons::GetInnerRadiusPlusZ)
      .def("GetOuterRadiusPlusZ", &G4Cons::GetOuterRadiusPlusZ)
      .def("GetZHalfLength", &G4Cons::GetZHalfLength)
      .def("GetStartPhiAngle", &G4Cons::GetStartPhiAngle)
      .def("GetDeltaPhiAngle", &G4Cons::GetDeltaPhiAngle)
      .def("GetSinStartPhi", &G4Cons::GetSinStartPhi)
      .def("GetCosStartPhi", &G4Cons::GetCosStartPhi)
      .def("GetSinEndPhi", &G4Cons::GetSinEndPhi)
      .def("GetCosEndPhi", &G4Cons::GetCosEndPhi)
      .def("SetInnerRadiusMinusZ", &G4Cons::SetInnerRadiusMinusZ, py::arg("Rmin1"))
      .def("SetOuterRadiusMinusZ", &G4Cons::SetOuterRadiusMinusZ, py::arg("Rmax1"))
      .def("SetInnerRadiusPlusZ", &G4Cons::SetInnerRadiusPlusZ, py::arg("Rmin2"))
      .def("SetOuterRadiusPlusZ", &G4Cons::SetOuterRadiusPlusZ, py::arg("Rmax2"))
      .def("SetZHalfLength", &G4Cons::SetZHalfLength, py::arg("newDz"))
      .def("SetStartPhiAngle", &G4Cons::SetStartPhiAngle, py::arg("newSPhi"), py::arg("trig") = true)
      .def("SetDeltaPhiAngle", &G4Cons::SetDeltaPhiAngle, py::arg("newDPhi"))
      .def("GetCubicVolume", &G4Cons::GetCubicVolume)
      .def("GetSurfaceArea", &G4Cons::GetSurfaceArea)
      .def("ComputeDimensions", &G4Cons::ComputeDimensions, py::arg("p"), py::arg("n"), py::arg("pRep"))
      .def("BoundingLimits", &G4Cons::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4Cons::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"), py::arg("pTransform"),
           py::arg("pMin"), py::arg("pMax"))

      .def("Inside", &G4Cons::Inside, py::arg("p"))
      .def("SurfaceNormal", &G4Cons::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4Cons::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4Cons::DistanceToIn, py::const_), py::arg("p"))
      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4Cons::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false,
           py::arg("validNorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4Cons::DistanceToOut, py::const_), py::arg("p"))
      .def("GetEntityType", &G4Cons::GetEntityType)
      .def("GetPointOnSurface", &G4Cons::GetPointOnSurface)
      .def("Clone", &G4Cons::Clone, py::return_value_policy::reference)
      .def("StreamInfo", &G4Cons::StreamInfo, py::arg("os"))
      .def("DescribeYourselfTo", &G4Cons::DescribeYourselfTo, py::arg("scene"))
      .def("CreatePolyhedron", &G4Cons::CreatePolyhedron, py::return_value_policy::reference);
}
