#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4TessellatedSolid.hh>
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

class PyG4TessellatedSolid : public G4TessellatedSolid, public py::trampoline_self_life_support {
public:
   using G4TessellatedSolid::G4TessellatedSolid;

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4TessellatedSolid, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4TessellatedSolid, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4TessellatedSolid, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4TessellatedSolid, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4TessellatedSolid, DistanceToOut, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *norm) const override
   {
      PYBIND11_OVERRIDE(G4double, G4TessellatedSolid, DistanceToOut, p, v, calcNorm, validNorm, norm);
   }

   G4bool Normal(const G4ThreeVector &p, G4ThreeVector &n) const override
   {
      PYBIND11_OVERRIDE_IMPL(G4bool, G4TessellatedSolid, "Normal", p, std::addressof(n));
      return G4TessellatedSolid::Normal(p, n);
   }

   G4double SafetyFromOutside(const G4ThreeVector &p, G4bool aAccurate) const override
   {
      PYBIND11_OVERRIDE(G4double, G4TessellatedSolid, SafetyFromOutside, p, aAccurate);
   }

   G4double SafetyFromInside(const G4ThreeVector &p, G4bool aAccurate) const override
   {
      PYBIND11_OVERRIDE(G4double, G4TessellatedSolid, SafetyFromInside, p, aAccurate);
   }

   G4GeometryType GetEntityType() const override
   {
      PYBIND11_OVERRIDE(G4GeometryType, G4TessellatedSolid, GetEntityType, );
   }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4TessellatedSolid, StreamInfo, os);
   }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4TessellatedSolid, Clone, ); }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4TessellatedSolid, GetPointOnSurface, );
   }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4TessellatedSolid, GetSurfaceArea, ); }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4TessellatedSolid, GetCubicVolume, ); }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pMin, G4double &pMax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4TessellatedSolid, CalculateExtent, pAxis, pVoxelLimit, pTransform, pMin, pMax);
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4TessellatedSolid, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4TessellatedSolid::BoundingLimits(pMin, pMax);
   }

   G4Polyhedron *CreatePolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4TessellatedSolid, CreatePolyhedron, );
   }

   G4Polyhedron *GetPolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4TessellatedSolid, GetPolyhedron, );
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4TessellatedSolid, "DescribeYourselfTo", std::addressof(scene));
      G4TessellatedSolid::DescribeYourselfTo(scene);
   }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4TessellatedSolid, GetExtent, ); }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4TessellatedSolid, ComputeDimensions, p, n, pRep);
   }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4TessellatedSolid, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4TessellatedSolid, GetConstituentSolid, no);
   }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4TessellatedSolid, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4TessellatedSolid, GetDisplacedSolidPtr, );
   }
};

void export_G4TessellatedSolid(py::module &m)
{
   py::class_<G4VertexInfo>(m, "G4VertexInfo")

      .def(py::init<>())
      .def("__copy__", [](const G4VertexInfo &self) { return G4VertexInfo(self); })
      .def("__deepcopy__", [](const G4VertexInfo &self, py::dict) { return G4VertexInfo(self); })
      .def_readwrite("id", &G4VertexInfo::id)
      .def_readwrite("mag2", &G4VertexInfo::mag2);

   py::class_<G4VertexComparator>(m, "G4VertexComparator")

      .def("__copy__", [](const G4VertexComparator &self) { return G4VertexComparator(self); })
      .def("__deepcopy__", [](const G4VertexComparator &self, py::dict) { return G4VertexComparator(self); })
      .def(py::init<>())
      .def("__call__", &G4VertexComparator::operator(), py::arg("l"), py::arg("r"), py::is_operator());

   py::class_<G4TessellatedSolid, PyG4TessellatedSolid, G4VSolid, py::nodelete>(m, "G4TessellatedSolid")

      .def(py::init<>())
      .def(py::init<const G4String &>(), py::arg("name"))
      .def("__copy__", [](const PyG4TessellatedSolid &self) { return PyG4TessellatedSolid(self); })
      .def("__deepcopy__", [](const PyG4TessellatedSolid &self, py::dict) { return PyG4TessellatedSolid(self); })

      .def(py::self += py::self)
      .def("AddFacet", &G4TessellatedSolid::AddFacet, py::arg("aFacet"))
      .def("GetFacet", &G4TessellatedSolid::GetFacet, py::arg("i"), py::return_value_policy::reference)
      .def("GetNumberOfFacets", &G4TessellatedSolid::GetNumberOfFacets)
      .def("Inside", &G4TessellatedSolid::Inside, py::arg("p"))
      .def("SurfaceNormal", &G4TessellatedSolid::SurfaceNormal, py::arg("p"))
      .def(
         "DistanceToIn",
         py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4TessellatedSolid::DistanceToIn, py::const_),
         py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4TessellatedSolid::DistanceToIn, py::const_),
           py::arg("p"))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4TessellatedSolid::DistanceToOut, py::const_),
           py::arg("p"))

      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4TessellatedSolid::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm"), py::arg("validNorm"), py::arg("norm"))

      .def("Normal", &G4TessellatedSolid::Normal, py::arg("p"), py::arg("n"))
      .def("SafetyFromOutside", &G4TessellatedSolid::SafetyFromOutside, py::arg("p"), py::arg("aAccurate") = false)
      .def("SafetyFromInside", &G4TessellatedSolid::SafetyFromInside, py::arg("p"), py::arg("aAccurate") = false)
      .def("GetEntityType", &G4TessellatedSolid::GetEntityType)
      .def("StreamInfo", &G4TessellatedSolid::StreamInfo, py::arg("os"))
      .def("Clone", &G4TessellatedSolid::Clone, py::return_value_policy::reference)
      .def("GetPointOnSurface", &G4TessellatedSolid::GetPointOnSurface)
      .def("GetSurfaceArea", &G4TessellatedSolid::GetSurfaceArea)
      .def("GetCubicVolume", &G4TessellatedSolid::GetCubicVolume)
      .def("SetSolidClosed", &G4TessellatedSolid::SetSolidClosed, py::arg("t"))
      .def("GetSolidClosed", &G4TessellatedSolid::GetSolidClosed)
      .def("SetMaxVoxels", &G4TessellatedSolid::SetMaxVoxels, py::arg("max"))
      .def("GetVoxels", &G4TessellatedSolid::GetVoxels)
      .def("CalculateExtent", &G4TessellatedSolid::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"),
           py::arg("pTransform"), py::arg("pMin"), py::arg("pMax"))

      .def("BoundingLimits", &G4TessellatedSolid::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("GetMinXExtent", &G4TessellatedSolid::GetMinXExtent)
      .def("GetMaxXExtent", &G4TessellatedSolid::GetMaxXExtent)
      .def("GetMinYExtent", &G4TessellatedSolid::GetMinYExtent)
      .def("GetMaxYExtent", &G4TessellatedSolid::GetMaxYExtent)
      .def("GetMinZExtent", &G4TessellatedSolid::GetMinZExtent)
      .def("GetMaxZExtent", &G4TessellatedSolid::GetMaxZExtent)
      .def("CreatePolyhedron", &G4TessellatedSolid::CreatePolyhedron, py::return_value_policy::reference)
      .def("GetPolyhedron", &G4TessellatedSolid::GetPolyhedron, py::return_value_policy::reference)
      .def("DescribeYourselfTo", &G4TessellatedSolid::DescribeYourselfTo, py::arg("scene"))
      .def("GetExtent", &G4TessellatedSolid::GetExtent)
      .def("AllocatedMemoryWithoutVoxels", &G4TessellatedSolid::AllocatedMemoryWithoutVoxels)
      .def("AllocatedMemory", &G4TessellatedSolid::AllocatedMemory)
      .def("DisplayAllocatedMemory", &G4TessellatedSolid::DisplayAllocatedMemory);
}
