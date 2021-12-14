#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UnionSolid.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4UnionSolid : public G4UnionSolid, public py::trampoline_self_life_support {
public:
   using G4UnionSolid::G4UnionSolid;

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4UnionSolid, GetEntityType, ); }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4UnionSolid, Clone, ); }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4UnionSolid, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4UnionSolid::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pMin, G4double &pMax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4UnionSolid, CalculateExtent, pAxis, pVoxelLimit, pTransform, pMin, pMax);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4UnionSolid, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4UnionSolid, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4UnionSolid, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4UnionSolid, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4UnionSolid, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4UnionSolid, DistanceToOut, p);
   }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4UnionSolid, ComputeDimensions, p, n, pRep);
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4UnionSolid, "DescribeYourselfTo", std::addressof(scene));
      G4UnionSolid::DescribeYourselfTo(scene);
   }

   G4Polyhedron *CreatePolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4UnionSolid, CreatePolyhedron, );
   }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4UnionSolid, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4UnionSolid, GetConstituentSolid, no);
   }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4UnionSolid, GetSurfaceArea, ); }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4UnionSolid, GetPolyhedron, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4UnionSolid, StreamInfo, os);
   }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4UnionSolid, GetPointOnSurface, );
   }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4UnionSolid, GetExtent, ); }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4UnionSolid, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4UnionSolid, GetDisplacedSolidPtr, );
   }
};

void export_G4UnionSolid(py::module &m)
{
   py::class_<G4UnionSolid, PyG4UnionSolid, G4BooleanSolid, py::nodelete>(m, "G4UnionSolid")

      .def(py::init<const G4String &, G4VSolid *, G4VSolid *>(), py::arg("pName"), py::arg("pSolidA"),
           py::arg("pSolidB"))

      .def(py::init<const G4String &, G4VSolid *, G4VSolid *, G4RotationMatrix *, const G4ThreeVector &>(),
           py::arg("pName"), py::arg("pSolidA"), py::arg("pSolidB"), py::arg("rotMatrix"), py::arg("transVector"))

      .def(py::init<const G4String &, G4VSolid *, G4VSolid *, const G4Transform3D &>(), py::arg("pName"),
           py::arg("pSolidA"), py::arg("pSolidB"), py::arg("transform"))

      .def("__copy__", [](const PyG4UnionSolid &self) { return PyG4UnionSolid(self); })
      .def("__deepcopy__", [](const PyG4UnionSolid &self, py::dict) { return PyG4UnionSolid(self); })
      .def("GetEntityType", &G4UnionSolid::GetEntityType)
      .def("Clone", &G4UnionSolid::Clone, py::return_value_policy::reference)
      .def("BoundingLimits", &G4UnionSolid::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4UnionSolid::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"),
           py::arg("pTransform"), py::arg("pMin"), py::arg("pMax"))

      .def("Inside", &G4UnionSolid::Inside, py::arg("p"))
      .def("SurfaceNormal", &G4UnionSolid::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4UnionSolid::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4UnionSolid::DistanceToIn, py::const_),
           py::arg("p"))

      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4UnionSolid::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false,
           py::arg("validNorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4UnionSolid::DistanceToOut, py::const_),
           py::arg("p"))

      .def("ComputeDimensions", &G4UnionSolid::ComputeDimensions, py::arg("p"), py::arg("n"), py::arg("pRep"))
      .def("DescribeYourselfTo", &G4UnionSolid::DescribeYourselfTo, py::arg("scene"))
      .def("CreatePolyhedron", &G4UnionSolid::CreatePolyhedron, py::return_value_policy::reference);
}
