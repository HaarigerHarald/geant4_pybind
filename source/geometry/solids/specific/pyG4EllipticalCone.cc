#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4EllipticalCone.hh>
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

class PyG4EllipticalCone : public G4EllipticalCone, public py::trampoline_self_life_support {
public:
   using G4EllipticalCone::G4EllipticalCone;

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4EllipticalCone, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4EllipticalCone, GetSurfaceArea, ); }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4EllipticalCone, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4EllipticalCone::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pMin, G4double &pMax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4EllipticalCone, CalculateExtent, pAxis, pVoxelLimit, pTransform, pMin, pMax);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4EllipticalCone, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4EllipticalCone, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4EllipticalCone, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4EllipticalCone, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4EllipticalCone, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4EllipticalCone, DistanceToOut, p);
   }

   G4GeometryType GetEntityType() const override
   {
      PYBIND11_OVERRIDE(G4GeometryType, G4EllipticalCone, GetEntityType, );
   }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4EllipticalCone, Clone, ); }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4EllipticalCone, GetPointOnSurface, );
   }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4EllipticalCone, StreamInfo, os);
   }

   G4Polyhedron *GetPolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4EllipticalCone, GetPolyhedron, );
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4EllipticalCone, "DescribeYourselfTo", std::addressof(scene));
      G4EllipticalCone::DescribeYourselfTo(scene);
   }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4EllipticalCone, GetExtent, ); }

   G4Polyhedron *CreatePolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4EllipticalCone, CreatePolyhedron, );
   }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4EllipticalCone, ComputeDimensions, p, n, pRep);
   }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4EllipticalCone, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4EllipticalCone, GetConstituentSolid, no);
   }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4EllipticalCone, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4EllipticalCone, GetDisplacedSolidPtr, );
   }
};

void export_G4EllipticalCone(py::module &m)
{
   py::class_<G4EllipticalCone, PyG4EllipticalCone, G4VSolid, py::nodelete>(m, "G4EllipticalCone")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double>(), py::arg("pName"),
           py::arg("pxSemiAxis"), py::arg("pySemiAxis"), py::arg("zMax"), py::arg("pzTopCut"))

      .def("__copy__", [](const PyG4EllipticalCone &self) { return PyG4EllipticalCone(self); })
      .def("__deepcopy__", [](const PyG4EllipticalCone &self, py::dict) { return PyG4EllipticalCone(self); })

      .def("GetSemiAxisMin", &G4EllipticalCone::GetSemiAxisMin)
      .def("GetSemiAxisMax", &G4EllipticalCone::GetSemiAxisMax)
      .def("GetSemiAxisX", &G4EllipticalCone::GetSemiAxisX)
      .def("GetSemiAxisY", &G4EllipticalCone::GetSemiAxisY)
      .def("GetZMax", &G4EllipticalCone::GetZMax)
      .def("GetZTopCut", &G4EllipticalCone::GetZTopCut)
      .def("SetSemiAxis", &G4EllipticalCone::SetSemiAxis, py::arg("x"), py::arg("y"), py::arg("z"))
      .def("SetZCut", &G4EllipticalCone::SetZCut, py::arg("newzTopCut"))
      .def("GetCubicVolume", &G4EllipticalCone::GetCubicVolume)
      .def("GetSurfaceArea", &G4EllipticalCone::GetSurfaceArea)
      .def("BoundingLimits", &G4EllipticalCone::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4EllipticalCone::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"),
           py::arg("pTransform"), py::arg("pMin"), py::arg("pMax"))

      .def("Inside", &G4EllipticalCone::Inside, py::arg("p"))
      .def("SurfaceNormal", &G4EllipticalCone::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4EllipticalCone::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4EllipticalCone::DistanceToIn, py::const_),
           py::arg("p"))

      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4EllipticalCone::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false,
           py::arg("validNorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4EllipticalCone::DistanceToOut, py::const_),
           py::arg("p"))

      .def("GetEntityType", &G4EllipticalCone::GetEntityType)
      .def("Clone", &G4EllipticalCone::Clone, py::return_value_policy::reference)
      .def("GetPointOnSurface", &G4EllipticalCone::GetPointOnSurface)
      .def("StreamInfo", &G4EllipticalCone::StreamInfo, py::arg("os"))
      .def("GetPolyhedron", &G4EllipticalCone::GetPolyhedron, py::return_value_policy::reference)
      .def("DescribeYourselfTo", &G4EllipticalCone::DescribeYourselfTo, py::arg("scene"))
      .def("GetExtent", &G4EllipticalCone::GetExtent)
      .def("CreatePolyhedron", &G4EllipticalCone::CreatePolyhedron, py::return_value_policy::reference);
}
