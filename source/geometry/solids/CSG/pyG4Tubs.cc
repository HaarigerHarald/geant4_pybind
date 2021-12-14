#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Tubs.hh>
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

class PyG4Tubs : public G4Tubs, public py::trampoline_self_life_support {
public:
   using G4Tubs::G4Tubs;

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4Tubs, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4Tubs, GetSurfaceArea, ); }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4Tubs, ComputeDimensions, p, n, pRep);
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Tubs, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4Tubs::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pmin, G4double &pmax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4Tubs, CalculateExtent, pAxis, pVoxelLimit, pTransform, pmin, pmax);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4Tubs, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4Tubs, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Tubs, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Tubs, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Tubs, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Tubs, DistanceToOut, p);
   }

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4Tubs, GetEntityType, ); }

   G4ThreeVector GetPointOnSurface() const override { PYBIND11_OVERRIDE(G4ThreeVector, G4Tubs, GetPointOnSurface, ); }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4Tubs, Clone, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4Tubs, StreamInfo, os);
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Tubs, "DescribeYourselfTo", std::addressof(scene));
      G4Tubs::DescribeYourselfTo(scene);
   }

   G4Polyhedron *CreatePolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Tubs, CreatePolyhedron, ); }

   G4ThreeVector ApproxSurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4Tubs, ApproxSurfaceNormal, p);
   }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Tubs, GetPolyhedron, ); }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4Tubs, GetExtent, ); }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4Tubs, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override { PYBIND11_OVERRIDE(G4VSolid *, G4Tubs, GetConstituentSolid, no); }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4Tubs, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4Tubs, GetDisplacedSolidPtr, );
   }
};

void export_G4Tubs(py::module &m)
{
   py::class_<G4Tubs, PyG4Tubs, G4CSGSolid, py::nodelete>(m, "G4Tubs")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double>(), py::arg("pName"),
           py::arg("pRMin"), py::arg("pRMax"), py::arg("pDz"), py::arg("pSPhi"), py::arg("pDPhi"))

      .def("__copy__", [](const PyG4Tubs &self) { return PyG4Tubs(self); })
      .def("__deepcopy__", [](const PyG4Tubs &self, py::dict) { return PyG4Tubs(self); })
      .def("GetInnerRadius", &G4Tubs::GetInnerRadius)
      .def("GetOuterRadius", &G4Tubs::GetOuterRadius)
      .def("GetZHalfLength", &G4Tubs::GetZHalfLength)
      .def("GetStartPhiAngle", &G4Tubs::GetStartPhiAngle)
      .def("GetDeltaPhiAngle", &G4Tubs::GetDeltaPhiAngle)
      .def("GetSinStartPhi", &G4Tubs::GetSinStartPhi)
      .def("GetCosStartPhi", &G4Tubs::GetCosStartPhi)
      .def("GetSinEndPhi", &G4Tubs::GetSinEndPhi)
      .def("GetCosEndPhi", &G4Tubs::GetCosEndPhi)
      .def("SetInnerRadius", &G4Tubs::SetInnerRadius, py::arg("newRMin"))
      .def("SetOuterRadius", &G4Tubs::SetOuterRadius, py::arg("newRMax"))
      .def("SetZHalfLength", &G4Tubs::SetZHalfLength, py::arg("newDz"))
      .def("SetStartPhiAngle", &G4Tubs::SetStartPhiAngle, py::arg("newSPhi"), py::arg("trig") = true)
      .def("SetDeltaPhiAngle", &G4Tubs::SetDeltaPhiAngle, py::arg("newDPhi"))
      .def("GetCubicVolume", &G4Tubs::GetCubicVolume)
      .def("GetSurfaceArea", &G4Tubs::GetSurfaceArea)
      .def("ComputeDimensions", &G4Tubs::ComputeDimensions, py::arg("p"), py::arg("n"), py::arg("pRep"))
      .def("BoundingLimits", &G4Tubs::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4Tubs::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"), py::arg("pTransform"),
           py::arg("pmin"), py::arg("pmax"))

      .def("Inside", &G4Tubs::Inside, py::arg("p"))
      .def("SurfaceNormal", &G4Tubs::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4Tubs::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4Tubs::DistanceToIn, py::const_), py::arg("p"))
      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4Tubs::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false,
           py::arg("validNorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4Tubs::DistanceToOut, py::const_), py::arg("p"))
      .def("GetEntityType", &G4Tubs::GetEntityType)
      .def("GetPointOnSurface", &G4Tubs::GetPointOnSurface)
      .def("Clone", &G4Tubs::Clone, py::return_value_policy::reference)
      .def("StreamInfo", &G4Tubs::StreamInfo, py::arg("os"))
      .def("DescribeYourselfTo", &G4Tubs::DescribeYourselfTo, py::arg("scene"))
      .def("CreatePolyhedron", &G4Tubs::CreatePolyhedron, py::return_value_policy::reference);
}
