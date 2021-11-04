#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4IntersectionSolid.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4IntersectionSolid : public G4IntersectionSolid, public py::trampoline_self_life_support {
public:
   using G4IntersectionSolid::G4IntersectionSolid;

   G4GeometryType GetEntityType() const override
   {
      PYBIND11_OVERRIDE(G4GeometryType, G4IntersectionSolid, GetEntityType, );
   }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4IntersectionSolid, Clone, ); }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4IntersectionSolid, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4IntersectionSolid::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pMin, G4double &pMax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4IntersectionSolid, CalculateExtent, pAxis, pVoxelLimit, pTransform, pMin, pMax);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4IntersectionSolid, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4IntersectionSolid, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4IntersectionSolid, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4IntersectionSolid, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4IntersectionSolid, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4IntersectionSolid, DistanceToOut, p);
   }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4IntersectionSolid, ComputeDimensions, p, n, pRep);
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4IntersectionSolid, "DescribeYourselfTo", std::addressof(scene));
      G4IntersectionSolid::DescribeYourselfTo(scene);
   }

   G4Polyhedron *CreatePolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4IntersectionSolid, CreatePolyhedron, );
   }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4IntersectionSolid, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4IntersectionSolid, GetConstituentSolid, no);
   }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4IntersectionSolid, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4IntersectionSolid, GetSurfaceArea, ); }

   G4Polyhedron *GetPolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4IntersectionSolid, GetPolyhedron, );
   }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4IntersectionSolid, StreamInfo, os);
   }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4IntersectionSolid, GetPointOnSurface, );
   }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4IntersectionSolid, GetExtent, ); }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4IntersectionSolid, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4IntersectionSolid, GetDisplacedSolidPtr, );
   }
};

void export_G4IntersectionSolid(py::module &m)
{
   py::class_<G4IntersectionSolid, PyG4IntersectionSolid, G4BooleanSolid, py::nodelete>(m, "G4IntersectionSolid")

      .def(py::init<const G4String &, G4VSolid *, G4VSolid *>(), py::arg("pName"), py::arg("pSolidA"),
           py::arg("pSolidB"))

      .def(py::init<const G4String &, G4VSolid *, G4VSolid *, G4RotationMatrix *, const G4ThreeVector &>(),
           py::arg("pName"), py::arg("pSolidA"), py::arg("pSolidB"), py::arg("rotMatrix"), py::arg("transVector"))

      .def(py::init<const G4String &, G4VSolid *, G4VSolid *, const G4Transform3D &>(), py::arg("pName"),
           py::arg("pSolidA"), py::arg("pSolidB"), py::arg("transform"))

      .def("__copy__", [](const PyG4IntersectionSolid &self) { return PyG4IntersectionSolid(self); })
      .def("__deepcopy__", [](const PyG4IntersectionSolid &self, py::dict) { return PyG4IntersectionSolid(self); })
      .def("GetEntityType", &G4IntersectionSolid::GetEntityType)
      .def("Clone", &G4IntersectionSolid::Clone, py::return_value_policy::reference)
      .def("BoundingLimits", &G4IntersectionSolid::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4IntersectionSolid::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"),
           py::arg("pTransform"), py::arg("pMin"), py::arg("pMax"))

      .def("Inside", &G4IntersectionSolid::Inside, py::arg("p"))
      .def("SurfaceNormal", &G4IntersectionSolid::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4IntersectionSolid::DistanceToIn,
                                                                           py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4IntersectionSolid::DistanceToIn, py::const_),
           py::arg("p"))

      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4IntersectionSolid::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false, py::arg("validNorm") = static_cast<G4bool *>(0),
           py::arg("n") = static_cast<G4ThreeVector *>(0))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4IntersectionSolid::DistanceToOut, py::const_),
           py::arg("p"))

      .def("ComputeDimensions", &G4IntersectionSolid::ComputeDimensions, py::arg("p"), py::arg("n"), py::arg("pRep"))
      .def("DescribeYourselfTo", &G4IntersectionSolid::DescribeYourselfTo, py::arg("scene"))
      .def("CreatePolyhedron", &G4IntersectionSolid::CreatePolyhedron, py::return_value_policy::reference);
}
