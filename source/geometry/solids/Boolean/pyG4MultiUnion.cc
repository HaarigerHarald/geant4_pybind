#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4MultiUnion.hh>
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

class PyG4MultiUnion : public G4MultiUnion, public py::trampoline_self_life_support {
public:
   using G4MultiUnion::G4MultiUnion;

   EInside Inside(const G4ThreeVector &aPoint) const override
   {
      PYBIND11_OVERRIDE(EInside, G4MultiUnion, Inside, aPoint);
   }

   G4double DistanceToIn(const G4ThreeVector &aPoint) const override
   {
      PYBIND11_OVERRIDE(G4double, G4MultiUnion, DistanceToIn, aPoint);
   }

   G4double DistanceToOut(const G4ThreeVector &aPoint) const override
   {
      PYBIND11_OVERRIDE(G4double, G4MultiUnion, DistanceToOut, aPoint);
   }

   G4double DistanceToIn(const G4ThreeVector &aPoint, const G4ThreeVector &aDirection) const override
   {
      PYBIND11_OVERRIDE(G4double, G4MultiUnion, DistanceToIn, aPoint, aDirection);
   }

   G4double DistanceToOut(const G4ThreeVector &aPoint, const G4ThreeVector &aDirection, const G4bool calcNorm,
                          G4bool *validNorm, G4ThreeVector *aNormalVector) const override
   {
      PYBIND11_OVERRIDE(G4double, G4MultiUnion, DistanceToOut, aPoint, aDirection, calcNorm, validNorm, aNormalVector);
   }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &aPoint) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4MultiUnion, SurfaceNormal, aPoint);
   }

   void BoundingLimits(G4ThreeVector &aMin, G4ThreeVector &aMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4MultiUnion, "BoundingLimits", std::addressof(aMin), std::addressof(aMax));
      G4MultiUnion::BoundingLimits(aMin, aMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pMin, G4double &pMax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4MultiUnion, CalculateExtent, pAxis, pVoxelLimit, pTransform, pMin, pMax);
   }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4MultiUnion, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4MultiUnion, GetSurfaceArea, ); }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4MultiUnion, Clone, ); }

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4MultiUnion, GetEntityType, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4MultiUnion, StreamInfo, os);
   }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4MultiUnion, GetPointOnSurface, );
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4MultiUnion, "DescribeYourselfTo", std::addressof(scene));
      G4MultiUnion::DescribeYourselfTo(scene);
   }

   G4Polyhedron *CreatePolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4MultiUnion, CreatePolyhedron, );
   }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4MultiUnion, GetPolyhedron, ); }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4MultiUnion, ComputeDimensions, p, n, pRep);
   }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4MultiUnion, GetExtent, ); }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4MultiUnion, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4MultiUnion, GetConstituentSolid, no);
   }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4MultiUnion, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4MultiUnion, GetDisplacedSolidPtr, );
   }
};

void export_G4MultiUnion(py::module &m)
{
   py::class_<G4MultiUnion, PyG4MultiUnion, G4VSolid, py::nodelete>(m, "G4MultiUnion")

      .def(py::init<>())
      .def(py::init<const G4String &>(), py::arg("name"))
      .def("__copy__", [](const PyG4MultiUnion &self) { return PyG4MultiUnion(self); })
      .def("__deepcopy__", [](const PyG4MultiUnion &self, py::dict) { return PyG4MultiUnion(self); })
      .def("AddNode", &G4MultiUnion::AddNode, py::arg("solid"), py::arg("trans"))
      .def("GetTransformation", &G4MultiUnion::GetTransformation, py::arg("index"))
      .def("GetSolid", &G4MultiUnion::GetSolid, py::arg("index"), py::return_value_policy::reference)
      .def("GetNumberOfSolids", &G4MultiUnion::GetNumberOfSolids)
      .def("Inside", &G4MultiUnion::Inside, py::arg("aPoint"))
      //.def("InsideIterator", &G4MultiUnion::InsideIterator, py::arg("aPoint"))
      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4MultiUnion::DistanceToIn, py::const_),
           py::arg("aPoint"))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4MultiUnion::DistanceToOut, py::const_),
           py::arg("aPoint"))

      .def("SetAccurateSafety", &G4MultiUnion::SetAccurateSafety, py::arg("flag"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4MultiUnion::DistanceToIn, py::const_),
           py::arg("aPoint"), py::arg("aDirection"))

      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4MultiUnion::DistanceToOut, py::const_),
           py::arg("aPoint"), py::arg("aDirection"), py::arg("calcNorm") = false,
           py::arg("validNorm")     = static_cast<G4bool *>(nullptr),
           py::arg("aNormalVector") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToInNoVoxels", &G4MultiUnion::DistanceToInNoVoxels, py::arg("aPoint"), py::arg("aDirection"))

      .def("DistanceToOutVoxels", &G4MultiUnion::DistanceToOutVoxels, py::arg("aPoint"), py::arg("aDirection"),
           py::arg("aNormalVector"))

      // .def("DistanceToOutVoxelsCore", &G4MultiUnion::DistanceToOutVoxelsCore, py::arg("aPoint"),
      // py::arg("aDirection"),
      //      py::arg("aNormalVector"), py::arg("aConvex"), py::arg("candidates"))

      .def("DistanceToOutNoVoxels", &G4MultiUnion::DistanceToOutNoVoxels, py::arg("aPoint"), py::arg("aDirection"),
           py::arg("aNormalVector"))

      .def("SurfaceNormal", &G4MultiUnion::SurfaceNormal, py::arg("aPoint"))
      .def("Extent", &G4MultiUnion::Extent, py::arg("aAxis"), py::arg("aMin"), py::arg("aMax"))
      .def("BoundingLimits", &G4MultiUnion::BoundingLimits, py::arg("aMin"), py::arg("aMax"))
      .def("CalculateExtent", &G4MultiUnion::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"),
           py::arg("pTransform"), py::arg("pMin"), py::arg("pMax"))

      .def("GetCubicVolume", &G4MultiUnion::GetCubicVolume)
      .def("GetSurfaceArea", &G4MultiUnion::GetSurfaceArea)
      .def("Clone", &G4MultiUnion::Clone, py::return_value_policy::reference)
      .def("GetEntityType", &G4MultiUnion::GetEntityType)
      .def("Voxelize", &G4MultiUnion::Voxelize)
      .def("InsideNoVoxels", &G4MultiUnion::InsideNoVoxels, py::arg("aPoint"))
      .def("GetVoxels", &G4MultiUnion::GetVoxels)
      .def("StreamInfo", &G4MultiUnion::StreamInfo, py::arg("os"))
      .def("GetPointOnSurface", &G4MultiUnion::GetPointOnSurface)
      .def("DescribeYourselfTo", &G4MultiUnion::DescribeYourselfTo, py::arg("scene"))
      .def("CreatePolyhedron", &G4MultiUnion::CreatePolyhedron, py::return_value_policy::reference)
      .def("GetPolyhedron", &G4MultiUnion::GetPolyhedron, py::return_value_policy::reference);
}
