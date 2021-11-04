#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Orb.hh>
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

class PyG4Orb : public G4Orb, public py::trampoline_self_life_support {
public:
   using G4Orb::G4Orb;

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4Orb, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4Orb, GetSurfaceArea, ); }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4Orb, ComputeDimensions, p, n, pRep);
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Orb, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4Orb::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pmin, G4double &pmax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4Orb, CalculateExtent, pAxis, pVoxelLimit, pTransform, pmin, pmax);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4Orb, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4Orb, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Orb, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(G4double, G4Orb, DistanceToIn, p); }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Orb, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Orb, DistanceToOut, p);
   }

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4Orb, GetEntityType, ); }

   G4ThreeVector GetPointOnSurface() const override { PYBIND11_OVERRIDE(G4ThreeVector, G4Orb, GetPointOnSurface, ); }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4Orb, Clone, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4Orb, StreamInfo, os);
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Orb, "DescribeYourselfTo", std::addressof(scene));
      G4Orb::DescribeYourselfTo(scene);
   }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4Orb, GetExtent, ); }

   G4Polyhedron *CreatePolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Orb, CreatePolyhedron, ); }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Orb, GetPolyhedron, ); }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4Orb, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override { PYBIND11_OVERRIDE(G4VSolid *, G4Orb, GetConstituentSolid, no); }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4Orb, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4Orb, GetDisplacedSolidPtr, );
   }
};

void export_G4Orb(py::module &m)
{
   py::class_<G4Orb, PyG4Orb, G4CSGSolid, py::nodelete>(m, "G4Orb")

      .def(py::init<const G4String &, G4double>(), py::arg("pName"), py::arg("pRmax"))
      .def("__copy__", [](const PyG4Orb &self) { return PyG4Orb(self); })
      .def("__deepcopy__", [](const PyG4Orb &self, py::dict) { return PyG4Orb(self); })
      .def("GetRadius", &G4Orb::GetRadius)
      .def("GetRadialTolerance", &G4Orb::GetRadialTolerance)
      .def("SetRadius", &G4Orb::SetRadius, py::arg("newRmax"))
      .def("GetCubicVolume", &G4Orb::GetCubicVolume)
      .def("GetSurfaceArea", &G4Orb::GetSurfaceArea)
      .def("ComputeDimensions", &G4Orb::ComputeDimensions, py::arg("p"), py::arg("n"), py::arg("pRep"))
      .def("BoundingLimits", &G4Orb::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4Orb::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"), py::arg("pTransform"),
           py::arg("pmin"), py::arg("pmax"))

      .def("Inside", &G4Orb::Inside, py::arg("p"))
      .def("SurfaceNormal", &G4Orb::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4Orb::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4Orb::DistanceToIn, py::const_), py::arg("p"))
      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4Orb::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false,
           py::arg("validNorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4Orb::DistanceToOut, py::const_), py::arg("p"))
      .def("GetEntityType", &G4Orb::GetEntityType)
      .def("GetPointOnSurface", &G4Orb::GetPointOnSurface)
      .def("Clone", &G4Orb::Clone, py::return_value_policy::reference)
      .def("StreamInfo", &G4Orb::StreamInfo, py::arg("os"))
      .def("DescribeYourselfTo", &G4Orb::DescribeYourselfTo, py::arg("scene"))
      .def("GetExtent", &G4Orb::GetExtent)
      .def("CreatePolyhedron", &G4Orb::CreatePolyhedron, py::return_value_policy::reference);
}
