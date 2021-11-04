#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Paraboloid.hh>
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

class PyG4Paraboloid : public G4Paraboloid, public py::trampoline_self_life_support {
public:
   using G4Paraboloid::G4Paraboloid;

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4Paraboloid, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4Paraboloid, GetSurfaceArea, ); }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Paraboloid, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4Paraboloid::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pmin, G4double &pmax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4Paraboloid, CalculateExtent, pAxis, pVoxelLimit, pTransform, pmin, pmax);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4Paraboloid, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4Paraboloid, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Paraboloid, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Paraboloid, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Paraboloid, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Paraboloid, DistanceToOut, p);
   }

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4Paraboloid, GetEntityType, ); }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4Paraboloid, Clone, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4Paraboloid, StreamInfo, os);
   }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4Paraboloid, GetPointOnSurface, );
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Paraboloid, "DescribeYourselfTo", std::addressof(scene));
      G4Paraboloid::DescribeYourselfTo(scene);
   }

   G4Polyhedron *CreatePolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4Paraboloid, CreatePolyhedron, );
   }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Paraboloid, GetPolyhedron, ); }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4Paraboloid, ComputeDimensions, p, n, pRep);
   }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4Paraboloid, GetExtent, ); }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4Paraboloid, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4Paraboloid, GetConstituentSolid, no);
   }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4Paraboloid, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4Paraboloid, GetDisplacedSolidPtr, );
   }
};

void export_G4Paraboloid(py::module &m)
{
   py::class_<G4Paraboloid, PyG4Paraboloid, G4VSolid, py::nodelete>(m, "G4Paraboloid")

      .def(py::init<const G4String &, G4double, G4double, G4double>(), py::arg("pName"), py::arg("pDz"), py::arg("pR1"),
           py::arg("pR2"))

      .def("__copy__", [](const PyG4Paraboloid &self) { return PyG4Paraboloid(self); })
      .def("__deepcopy__", [](const PyG4Paraboloid &self, py::dict) { return PyG4Paraboloid(self); })
      .def("GetZHalfLength", &G4Paraboloid::GetZHalfLength)
      .def("GetRadiusMinusZ", &G4Paraboloid::GetRadiusMinusZ)
      .def("GetRadiusPlusZ", &G4Paraboloid::GetRadiusPlusZ)
      .def("GetCubicVolume", &G4Paraboloid::GetCubicVolume)
      .def("GetSurfaceArea", &G4Paraboloid::GetSurfaceArea)
      .def("CalculateSurfaceArea", &G4Paraboloid::CalculateSurfaceArea)
      .def("SetZHalfLength", &G4Paraboloid::SetZHalfLength, py::arg("dz"))
      .def("SetRadiusMinusZ", &G4Paraboloid::SetRadiusMinusZ, py::arg("R1"))
      .def("SetRadiusPlusZ", &G4Paraboloid::SetRadiusPlusZ, py::arg("R2"))
      .def("BoundingLimits", &G4Paraboloid::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4Paraboloid::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"),
           py::arg("pTransform"), py::arg("pmin"), py::arg("pmax"))

      .def("Inside", &G4Paraboloid::Inside, py::arg("p"))
      .def("SurfaceNormal", &G4Paraboloid::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4Paraboloid::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4Paraboloid::DistanceToIn, py::const_),
           py::arg("p"))

      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4Paraboloid::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false,
           py::arg("validNorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4Paraboloid::DistanceToOut, py::const_),
           py::arg("p"))

      .def("GetEntityType", &G4Paraboloid::GetEntityType)
      .def("Clone", &G4Paraboloid::Clone, py::return_value_policy::reference)
      .def("StreamInfo", &G4Paraboloid::StreamInfo, py::arg("os"))
      .def("GetPointOnSurface", &G4Paraboloid::GetPointOnSurface)
      .def("DescribeYourselfTo", &G4Paraboloid::DescribeYourselfTo, py::arg("scene"))
      .def("CreatePolyhedron", &G4Paraboloid::CreatePolyhedron, py::return_value_policy::reference)
      .def("GetPolyhedron", &G4Paraboloid::GetPolyhedron, py::return_value_policy::reference);
}
