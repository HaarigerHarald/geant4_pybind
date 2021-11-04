#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Box.hh>
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

class PyG4Box : public G4Box, public py::trampoline_self_life_support {
public:
   using G4Box::G4Box;

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4Box, ComputeDimensions, p, n, pRep);
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Box, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4Box::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pMin, G4double &pMax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4Box, CalculateExtent, pAxis, pVoxelLimit, pTransform, pMin, pMax);
   }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4Box, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4Box, GetSurfaceArea, ); }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4Box, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4Box, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Box, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(G4double, G4Box, DistanceToIn, p); }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Box, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Box, DistanceToOut, p);
   }

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4Box, GetEntityType, ); }

   G4ThreeVector GetPointOnSurface() const override { PYBIND11_OVERRIDE(G4ThreeVector, G4Box, GetPointOnSurface, ); }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4Box, Clone, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4Box, StreamInfo, os);
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Box, "DescribeYourselfTo", std::addressof(scene));
      G4Box::DescribeYourselfTo(scene);
   }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4Box, GetExtent, ); }

   G4Polyhedron *CreatePolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Box, CreatePolyhedron, ); }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Box, GetPolyhedron, ); }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4Box, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override { PYBIND11_OVERRIDE(G4VSolid *, G4Box, GetConstituentSolid, no); }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4Box, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4Box, GetDisplacedSolidPtr, );
   }
};

void export_G4Box(py::module &m)
{
   py::class_<G4Box, PyG4Box, G4CSGSolid, py::nodelete>(m, "G4Box")

      .def(py::init<const G4String &, G4double, G4double, G4double>(), py::arg("pName"), py::arg("pX"), py::arg("pY"),
           py::arg("pZ"))

      .def("__copy__", [](const PyG4Box &self) { return PyG4Box(self); })
      .def("__deepcopy__", [](const PyG4Box &self, py::dict) { return PyG4Box(self); })
      .def("ComputeDimensions", &G4Box::ComputeDimensions, py::arg("p"), py::arg("n"), py::arg("pRep"))
      .def("BoundingLimits", &G4Box::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4Box::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"), py::arg("pTransform"),
           py::arg("pMin"), py::arg("pMax"))

      .def("GetXHalfLength", &G4Box::GetXHalfLength)
      .def("GetYHalfLength", &G4Box::GetYHalfLength)
      .def("GetZHalfLength", &G4Box::GetZHalfLength)
      .def("SetXHalfLength", &G4Box::SetXHalfLength, py::arg("dx"))
      .def("SetYHalfLength", &G4Box::SetYHalfLength, py::arg("dy"))
      .def("SetZHalfLength", &G4Box::SetZHalfLength, py::arg("dz"))
      .def("GetCubicVolume", &G4Box::GetCubicVolume)
      .def("GetSurfaceArea", &G4Box::GetSurfaceArea)
      .def("Inside", &G4Box::Inside, py::arg("p"))
      .def("SurfaceNormal", &G4Box::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4Box::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4Box::DistanceToIn, py::const_), py::arg("p"))

      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4Box::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false,
           py::arg("validNorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4Box::DistanceToOut, py::const_), py::arg("p"))
      .def("GetEntityType", &G4Box::GetEntityType)
      .def("GetPointOnSurface", &G4Box::GetPointOnSurface)
      .def("Clone", &G4Box::Clone, py::return_value_policy::reference)
      .def("StreamInfo", &G4Box::StreamInfo, py::arg("os"))
      .def("DescribeYourselfTo", &G4Box::DescribeYourselfTo, py::arg("scene"))
      .def("GetExtent", &G4Box::GetExtent)
      .def("CreatePolyhedron", &G4Box::CreatePolyhedron, py::return_value_policy::reference);
}
