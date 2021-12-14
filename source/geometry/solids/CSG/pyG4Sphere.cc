#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Sphere.hh>
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

class PyG4Sphere : public G4Sphere, public py::trampoline_self_life_support {
public:
   using G4Sphere::G4Sphere;

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4Sphere, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4Sphere, GetSurfaceArea, ); }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4Sphere, ComputeDimensions, p, n, pRep);
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Sphere, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4Sphere::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pmin, G4double &pmax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4Sphere, CalculateExtent, pAxis, pVoxelLimit, pTransform, pmin, pmax);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4Sphere, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4Sphere, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Sphere, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Sphere, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Sphere, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Sphere, DistanceToOut, p);
   }

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4Sphere, GetEntityType, ); }

   G4ThreeVector GetPointOnSurface() const override { PYBIND11_OVERRIDE(G4ThreeVector, G4Sphere, GetPointOnSurface, ); }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4Sphere, Clone, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4Sphere, StreamInfo, os);
   }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4Sphere, GetExtent, ); }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Sphere, "DescribeYourselfTo", std::addressof(scene));
      G4Sphere::DescribeYourselfTo(scene);
   }

   G4Polyhedron *CreatePolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Sphere, CreatePolyhedron, ); }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Sphere, GetPolyhedron, ); }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4Sphere, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4Sphere, GetConstituentSolid, no);
   }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4Sphere, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4Sphere, GetDisplacedSolidPtr, );
   }
};

void export_G4Sphere(py::module &m)
{
   py::class_<G4Sphere, PyG4Sphere, G4CSGSolid, py::nodelete>(m, "G4Sphere")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double, G4double>(), py::arg("pName"),
           py::arg("pRmin"), py::arg("pRmax"), py::arg("pSPhi"), py::arg("pDPhi"), py::arg("pSTheta"),
           py::arg("pDTheta"))

      .def("__copy__", [](const PyG4Sphere &self) { return PyG4Sphere(self); })
      .def("__deepcopy__", [](const PyG4Sphere &self, py::dict) { return PyG4Sphere(self); })
      .def("GetInnerRadius", &G4Sphere::GetInnerRadius)
      .def("GetOuterRadius", &G4Sphere::GetOuterRadius)
      .def("GetStartPhiAngle", &G4Sphere::GetStartPhiAngle)
      .def("GetDeltaPhiAngle", &G4Sphere::GetDeltaPhiAngle)
      .def("GetStartThetaAngle", &G4Sphere::GetStartThetaAngle)
      .def("GetDeltaThetaAngle", &G4Sphere::GetDeltaThetaAngle)
      .def("GetSinStartPhi", &G4Sphere::GetSinStartPhi)
      .def("GetCosStartPhi", &G4Sphere::GetCosStartPhi)
      .def("GetSinEndPhi", &G4Sphere::GetSinEndPhi)
      .def("GetCosEndPhi", &G4Sphere::GetCosEndPhi)
      .def("GetSinStartTheta", &G4Sphere::GetSinStartTheta)
      .def("GetCosStartTheta", &G4Sphere::GetCosStartTheta)
      .def("GetSinEndTheta", &G4Sphere::GetSinEndTheta)
      .def("GetCosEndTheta", &G4Sphere::GetCosEndTheta)
      .def("SetInnerRadius", &G4Sphere::SetInnerRadius, py::arg("newRMin"))
      .def("SetOuterRadius", &G4Sphere::SetOuterRadius, py::arg("newRmax"))
      .def("SetStartPhiAngle", &G4Sphere::SetStartPhiAngle, py::arg("newSphi"), py::arg("trig") = true)
      .def("SetDeltaPhiAngle", &G4Sphere::SetDeltaPhiAngle, py::arg("newDphi"))
      .def("SetStartThetaAngle", &G4Sphere::SetStartThetaAngle, py::arg("newSTheta"))
      .def("SetDeltaThetaAngle", &G4Sphere::SetDeltaThetaAngle, py::arg("newDTheta"))
      .def("GetCubicVolume", &G4Sphere::GetCubicVolume)
      .def("GetSurfaceArea", &G4Sphere::GetSurfaceArea)
      .def("ComputeDimensions", &G4Sphere::ComputeDimensions, py::arg("p"), py::arg("n"), py::arg("pRep"))
      .def("BoundingLimits", &G4Sphere::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4Sphere::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"),
           py::arg("pTransform"), py::arg("pmin"), py::arg("pmax"))

      .def("Inside", &G4Sphere::Inside, py::arg("p"))
      .def("SurfaceNormal", &G4Sphere::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4Sphere::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4Sphere::DistanceToIn, py::const_), py::arg("p"))
      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4Sphere::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false,
           py::arg("validNorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4Sphere::DistanceToOut, py::const_),
           py::arg("p"))

      .def("GetEntityType", &G4Sphere::GetEntityType)
      .def("GetPointOnSurface", &G4Sphere::GetPointOnSurface)
      .def("Clone", &G4Sphere::Clone, py::return_value_policy::reference)
      .def("StreamInfo", &G4Sphere::StreamInfo, py::arg("os"))
      .def("GetExtent", &G4Sphere::GetExtent)
      .def("DescribeYourselfTo", &G4Sphere::DescribeYourselfTo, py::arg("scene"))
      .def("CreatePolyhedron", &G4Sphere::CreatePolyhedron, py::return_value_policy::reference);
}
