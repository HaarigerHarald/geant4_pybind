#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Hype.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>
#include <G4VisAttributes.hh>
#include <G4SolidExtentList.hh>
#include <G4ClippablePolygon.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4Hype : public G4Hype, public py::trampoline_self_life_support {
public:
   using G4Hype::G4Hype;

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4Hype, ComputeDimensions, p, n, pRep);
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Hype, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4Hype::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pMin, G4double &pMax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4Hype, CalculateExtent, pAxis, pVoxelLimit, pTransform, pMin, pMax);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4Hype, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4Hype, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Hype, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Hype, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Hype, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Hype, DistanceToOut, p);
   }

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4Hype, GetEntityType, ); }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4Hype, Clone, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4Hype, StreamInfo, os);
   }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4Hype, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4Hype, GetSurfaceArea, ); }

   G4ThreeVector GetPointOnSurface() const override { PYBIND11_OVERRIDE(G4ThreeVector, G4Hype, GetPointOnSurface, ); }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Hype, "DescribeYourselfTo", std::addressof(scene));
      G4Hype::DescribeYourselfTo(scene);
   }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4Hype, GetExtent, ); }

   G4Polyhedron *CreatePolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Hype, CreatePolyhedron, ); }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Hype, GetPolyhedron, ); }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4Hype, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override { PYBIND11_OVERRIDE(G4VSolid *, G4Hype, GetConstituentSolid, no); }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4Hype, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4Hype, GetDisplacedSolidPtr, );
   }
};

void export_G4Hype(py::module &m)
{
   py::class_<G4Hype, PyG4Hype, G4VSolid, py::nodelete>(m, "G4Hype")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double>(), py::arg("pName"),
           py::arg("newInnerRadius"), py::arg("newOuterRadius"), py::arg("newInnerStereo"), py::arg("newOuterStereo"),
           py::arg("newHalfLenZ"))

      .def("__copy__", [](const PyG4Hype &self) { return PyG4Hype(self); })
      .def("__deepcopy__", [](const PyG4Hype &self, py::dict) { return PyG4Hype(self); })
      .def("ComputeDimensions", &G4Hype::ComputeDimensions, py::arg("p"), py::arg("n"), py::arg("pRep"))

      .def("BoundingLimits", &G4Hype::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4Hype::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"), py::arg("pTransform"),
           py::arg("pMin"), py::arg("pMax"))

      .def("GetInnerRadius", &G4Hype::GetInnerRadius)
      .def("GetOuterRadius", &G4Hype::GetOuterRadius)
      .def("GetZHalfLength", &G4Hype::GetZHalfLength)
      .def("GetInnerStereo", &G4Hype::GetInnerStereo)
      .def("GetOuterStereo", &G4Hype::GetOuterStereo)
      .def("SetInnerRadius", &G4Hype::SetInnerRadius, py::arg("newIRad"))
      .def("SetOuterRadius", &G4Hype::SetOuterRadius, py::arg("newORad"))
      .def("SetZHalfLength", &G4Hype::SetZHalfLength, py::arg("newHLZ"))
      .def("SetInnerStereo", &G4Hype::SetInnerStereo, py::arg("newISte"))
      .def("SetOuterStereo", &G4Hype::SetOuterStereo, py::arg("newOSte"))
      .def("Inside", &G4Hype::Inside, py::arg("p"))
      .def("SurfaceNormal", &G4Hype::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4Hype::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4Hype::DistanceToIn, py::const_), py::arg("p"))

      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4Hype::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false,
           py::arg("validNorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4Hype::DistanceToOut, py::const_), py::arg("p"))

      .def("GetEntityType", &G4Hype::GetEntityType)
      .def("Clone", &G4Hype::Clone, py::return_value_policy::reference)
      .def("StreamInfo", &G4Hype::StreamInfo, py::arg("os"))
      .def("GetCubicVolume", &G4Hype::GetCubicVolume)
      .def("GetSurfaceArea", &G4Hype::GetSurfaceArea)
      .def("GetPointOnSurface", &G4Hype::GetPointOnSurface)
      .def("DescribeYourselfTo", &G4Hype::DescribeYourselfTo, py::arg("scene"))
      .def("GetExtent", &G4Hype::GetExtent)
      .def("CreatePolyhedron", &G4Hype::CreatePolyhedron, py::return_value_policy::reference)
      .def("GetPolyhedron", &G4Hype::GetPolyhedron, py::return_value_policy::reference);
}
