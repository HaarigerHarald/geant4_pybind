#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Trd.hh>
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

class PyG4Trd : public G4Trd, public py::trampoline_self_life_support {
public:
   using G4Trd::G4Trd;

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4Trd, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4Trd, GetSurfaceArea, ); }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4Trd, ComputeDimensions, p, n, pRep);
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Trd, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4Trd::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pMin, G4double &pMax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4Trd, CalculateExtent, pAxis, pVoxelLimit, pTransform, pMin, pMax);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4Trd, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4Trd, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Trd, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(G4double, G4Trd, DistanceToIn, p); }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Trd, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Trd, DistanceToOut, p);
   }

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4Trd, GetEntityType, ); }

   G4ThreeVector GetPointOnSurface() const override { PYBIND11_OVERRIDE(G4ThreeVector, G4Trd, GetPointOnSurface, ); }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4Trd, Clone, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4Trd, StreamInfo, os);
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Trd, "DescribeYourselfTo", std::addressof(scene));
      G4Trd::DescribeYourselfTo(scene);
   }

   G4Polyhedron *CreatePolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Trd, CreatePolyhedron, ); }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Trd, GetPolyhedron, ); }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4Trd, GetExtent, ); }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4Trd, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override { PYBIND11_OVERRIDE(G4VSolid *, G4Trd, GetConstituentSolid, no); }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4Trd, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4Trd, GetDisplacedSolidPtr, );
   }
};

void export_G4Trd(py::module &m)
{
   py::class_<G4Trd, PyG4Trd, G4CSGSolid, py::nodelete>(m, "G4Trd")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double>(), py::arg("pName"),
           py::arg("pdx1"), py::arg("pdx2"), py::arg("pdy1"), py::arg("pdy2"), py::arg("pdz"))

      .def("__copy__", [](const PyG4Trd &self) { return PyG4Trd(self); })
      .def("__deepcopy__", [](const PyG4Trd &self, py::dict) { return PyG4Trd(self); })
      .def("GetXHalfLength1", &G4Trd::GetXHalfLength1)
      .def("GetXHalfLength2", &G4Trd::GetXHalfLength2)
      .def("GetYHalfLength1", &G4Trd::GetYHalfLength1)
      .def("GetYHalfLength2", &G4Trd::GetYHalfLength2)
      .def("GetZHalfLength", &G4Trd::GetZHalfLength)
      .def("SetXHalfLength1", &G4Trd::SetXHalfLength1, py::arg("val"))
      .def("SetXHalfLength2", &G4Trd::SetXHalfLength2, py::arg("val"))
      .def("SetYHalfLength1", &G4Trd::SetYHalfLength1, py::arg("val"))
      .def("SetYHalfLength2", &G4Trd::SetYHalfLength2, py::arg("val"))
      .def("SetZHalfLength", &G4Trd::SetZHalfLength, py::arg("val"))
      .def("SetAllParameters", &G4Trd::SetAllParameters, py::arg("pdx1"), py::arg("pdx2"), py::arg("pdy1"),
           py::arg("pdy2"), py::arg("pdz"))

      .def("GetCubicVolume", &G4Trd::GetCubicVolume)
      .def("GetSurfaceArea", &G4Trd::GetSurfaceArea)
      .def("ComputeDimensions", &G4Trd::ComputeDimensions, py::arg("p"), py::arg("n"), py::arg("pRep"))
      .def("BoundingLimits", &G4Trd::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4Trd::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"), py::arg("pTransform"),
           py::arg("pMin"), py::arg("pMax"))

      .def("Inside", &G4Trd::Inside, py::arg("p"))
      .def("SurfaceNormal", &G4Trd::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4Trd::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4Trd::DistanceToIn, py::const_), py::arg("p"))

      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4Trd::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false,
           py::arg("validNorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4Trd::DistanceToOut, py::const_), py::arg("p"))
      .def("GetEntityType", &G4Trd::GetEntityType)
      .def("GetPointOnSurface", &G4Trd::GetPointOnSurface)
      .def("Clone", &G4Trd::Clone, py::return_value_policy::reference)
      .def("StreamInfo", &G4Trd::StreamInfo, py::arg("os"))
      .def("DescribeYourselfTo", &G4Trd::DescribeYourselfTo, py::arg("scene"))
      .def("CreatePolyhedron", &G4Trd::CreatePolyhedron, py::return_value_policy::reference);
}
