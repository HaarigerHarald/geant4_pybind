#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4CutTubs.hh>
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

class PyG4CutTubs : public G4CutTubs, public py::trampoline_self_life_support {
public:
   using G4CutTubs::G4CutTubs;

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4CutTubs, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4CutTubs, GetSurfaceArea, ); }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4CutTubs, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4CutTubs::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pmin, G4double &pmax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4CutTubs, CalculateExtent, pAxis, pVoxelLimit, pTransform, pmin, pmax);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4CutTubs, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4CutTubs, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4CutTubs, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4CutTubs, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4CutTubs, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4CutTubs, DistanceToOut, p);
   }

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4CutTubs, GetEntityType, ); }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4CutTubs, GetPointOnSurface, );
   }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4CutTubs, Clone, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4CutTubs, StreamInfo, os);
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4CutTubs, "DescribeYourselfTo", std::addressof(scene));
      G4CutTubs::DescribeYourselfTo(scene);
   }

   G4Polyhedron *CreatePolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4CutTubs, CreatePolyhedron, ); }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4CutTubs, GetPolyhedron, ); }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4CutTubs, ComputeDimensions, p, n, pRep);
   }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4CutTubs, GetExtent, ); }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4CutTubs, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4CutTubs, GetConstituentSolid, no);
   }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4CutTubs, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4CutTubs, GetDisplacedSolidPtr, );
   }
};

void export_G4CutTubs(py::module &m)
{
   py::class_<G4CutTubs, PyG4CutTubs, G4CSGSolid, py::nodelete>(m, "G4CutTubs")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double, G4ThreeVector, G4ThreeVector>(),
           py::arg("pName"), py::arg("pRMin"), py::arg("pRMax"), py::arg("pDz"), py::arg("pSPhi"), py::arg("pDPhi"),
           py::arg("pLowNorm"), py::arg("pHighNorm"))

      .def("__copy__", [](const PyG4CutTubs &self) { return PyG4CutTubs(self); })
      .def("__deepcopy__", [](const PyG4CutTubs &self, py::dict) { return PyG4CutTubs(self); })
      .def("GetInnerRadius", &G4CutTubs::GetInnerRadius)
      .def("GetOuterRadius", &G4CutTubs::GetOuterRadius)
      .def("GetZHalfLength", &G4CutTubs::GetZHalfLength)
      .def("GetStartPhiAngle", &G4CutTubs::GetStartPhiAngle)
      .def("GetDeltaPhiAngle", &G4CutTubs::GetDeltaPhiAngle)
      .def("GetSinStartPhi", &G4CutTubs::GetSinStartPhi)
      .def("GetCosStartPhi", &G4CutTubs::GetCosStartPhi)
      .def("GetSinEndPhi", &G4CutTubs::GetSinEndPhi)
      .def("GetCosEndPhi", &G4CutTubs::GetCosEndPhi)
      .def("GetLowNorm", &G4CutTubs::GetLowNorm)
      .def("GetHighNorm", &G4CutTubs::GetHighNorm)
      .def("SetInnerRadius", &G4CutTubs::SetInnerRadius, py::arg("newRMin"))
      .def("SetOuterRadius", &G4CutTubs::SetOuterRadius, py::arg("newRMax"))
      .def("SetZHalfLength", &G4CutTubs::SetZHalfLength, py::arg("newDz"))
      .def("SetStartPhiAngle", &G4CutTubs::SetStartPhiAngle, py::arg("newSPhi"), py::arg("trig") = true)
      .def("SetDeltaPhiAngle", &G4CutTubs::SetDeltaPhiAngle, py::arg("newDPhi"))
      .def("GetCubicVolume", &G4CutTubs::GetCubicVolume)
      .def("GetSurfaceArea", &G4CutTubs::GetSurfaceArea)
      .def("BoundingLimits", &G4CutTubs::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4CutTubs::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"),
           py::arg("pTransform"), py::arg("pmin"), py::arg("pmax"))

      .def("Inside", &G4CutTubs::Inside, py::arg("p"))
      .def("SurfaceNormal", &G4CutTubs::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4CutTubs::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4CutTubs::DistanceToIn, py::const_), py::arg("p"))
      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4CutTubs::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false,
           py::arg("validNorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4CutTubs::DistanceToOut, py::const_),
           py::arg("p"))

      .def("GetEntityType", &G4CutTubs::GetEntityType)
      .def("GetPointOnSurface", &G4CutTubs::GetPointOnSurface)
      .def("Clone", &G4CutTubs::Clone, py::return_value_policy::reference)
      .def("StreamInfo", &G4CutTubs::StreamInfo, py::arg("os"))
      .def("DescribeYourselfTo", &G4CutTubs::DescribeYourselfTo, py::arg("scene"))
      .def("CreatePolyhedron", &G4CutTubs::CreatePolyhedron, py::return_value_policy::reference);
}
