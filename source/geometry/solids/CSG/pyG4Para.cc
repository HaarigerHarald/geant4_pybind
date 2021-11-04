#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Para.hh>
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

class PyG4Para : public G4Para, public py::trampoline_self_life_support {
public:
   using G4Para::G4Para;

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4Para, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4Para, GetSurfaceArea, ); }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4Para, ComputeDimensions, p, n, pRep);
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Para, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4Para::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pMin, G4double &pMax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4Para, CalculateExtent, pAxis, pVoxelLimit, pTransform, pMin, pMax);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4Para, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4Para, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Para, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Para, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Para, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Para, DistanceToOut, p);
   }

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4Para, GetEntityType, ); }

   G4ThreeVector GetPointOnSurface() const override { PYBIND11_OVERRIDE(G4ThreeVector, G4Para, GetPointOnSurface, ); }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4Para, Clone, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4Para, StreamInfo, os);
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Para, "DescribeYourselfTo", std::addressof(scene));
      G4Para::DescribeYourselfTo(scene);
   }

   G4Polyhedron *CreatePolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Para, CreatePolyhedron, ); }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Para, GetPolyhedron, ); }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4Para, GetExtent, ); }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4Para, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override { PYBIND11_OVERRIDE(G4VSolid *, G4Para, GetConstituentSolid, no); }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4Para, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4Para, GetDisplacedSolidPtr, );
   }
};

void export_G4Para(py::module &m)
{
   py::class_<G4Para, PyG4Para, G4CSGSolid, py::nodelete>(m, "G4Para")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double, G4double>(), py::arg("pName"),
           py::arg("pDx"), py::arg("pDy"), py::arg("pDz"), py::arg("pAlpha"), py::arg("pTheta"), py::arg("pPhi"))

      .def(py::init<const G4String &, const G4ThreeVector *>(), py::arg("pName"), py::arg("pt"))
      .def("__copy__", [](const PyG4Para &self) { return PyG4Para(self); })
      .def("__deepcopy__", [](const PyG4Para &self, py::dict) { return PyG4Para(self); })
      .def("GetZHalfLength", &G4Para::GetZHalfLength)
      .def("GetSymAxis", &G4Para::GetSymAxis)
      .def("GetYHalfLength", &G4Para::GetYHalfLength)
      .def("GetXHalfLength", &G4Para::GetXHalfLength)
      .def("GetTanAlpha", &G4Para::GetTanAlpha)
      .def("SetXHalfLength", &G4Para::SetXHalfLength, py::arg("val"))
      .def("SetYHalfLength", &G4Para::SetYHalfLength, py::arg("val"))
      .def("SetZHalfLength", &G4Para::SetZHalfLength, py::arg("val"))
      .def("SetAlpha", &G4Para::SetAlpha, py::arg("alpha"))
      .def("SetTanAlpha", &G4Para::SetTanAlpha, py::arg("val"))
      .def("SetThetaAndPhi", &G4Para::SetThetaAndPhi, py::arg("pTheta"), py::arg("pPhi"))
      .def("SetAllParameters", &G4Para::SetAllParameters, py::arg("pDx"), py::arg("pDy"), py::arg("pDz"),
           py::arg("pAlpha"), py::arg("pTheta"), py::arg("pPhi"))

      .def("GetCubicVolume", &G4Para::GetCubicVolume)
      .def("GetSurfaceArea", &G4Para::GetSurfaceArea)
      .def("ComputeDimensions", &G4Para::ComputeDimensions, py::arg("p"), py::arg("n"), py::arg("pRep"))
      .def("BoundingLimits", &G4Para::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4Para::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"), py::arg("pTransform"),
           py::arg("pMin"), py::arg("pMax"))

      .def("Inside", &G4Para::Inside, py::arg("p"))
      .def("SurfaceNormal", &G4Para::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4Para::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4Para::DistanceToIn, py::const_), py::arg("p"))
      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4Para::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false,
           py::arg("validNorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4Para::DistanceToOut, py::const_), py::arg("p"))

      .def("GetEntityType", &G4Para::GetEntityType)
      .def("GetPointOnSurface", &G4Para::GetPointOnSurface)
      .def("Clone", &G4Para::Clone, py::return_value_policy::reference)
      .def("StreamInfo", &G4Para::StreamInfo, py::arg("os"))
      .def("DescribeYourselfTo", &G4Para::DescribeYourselfTo, py::arg("scene"))
      .def("CreatePolyhedron", &G4Para::CreatePolyhedron, py::return_value_policy::reference);
}
