#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Torus.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4Torus : public G4Torus, public py::trampoline_self_life_support {
public:
   using G4Torus::G4Torus;

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4Torus, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4Torus, GetSurfaceArea, ); }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4Torus, Inside, p); }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Torus, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4Torus::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pmin, G4double &pmax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4Torus, CalculateExtent, pAxis, pVoxelLimit, pTransform, pmin, pmax);
   }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4Torus, ComputeDimensions, p, n, pRep);
   }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4Torus, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Torus, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Torus, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Torus, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Torus, DistanceToOut, p);
   }

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4Torus, GetEntityType, ); }

   G4ThreeVector GetPointOnSurface() const override { PYBIND11_OVERRIDE(G4ThreeVector, G4Torus, GetPointOnSurface, ); }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4Torus, Clone, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4Torus, StreamInfo, os);
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Torus, "DescribeYourselfTo", std::addressof(scene));
      G4Torus::DescribeYourselfTo(scene);
   }

   G4Polyhedron *CreatePolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Torus, CreatePolyhedron, ); }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Torus, GetPolyhedron, ); }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4Torus, GetExtent, ); }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4Torus, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override { PYBIND11_OVERRIDE(G4VSolid *, G4Torus, GetConstituentSolid, no); }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4Torus, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4Torus, GetDisplacedSolidPtr, );
   }
};

void export_G4Torus(py::module &m)
{
   py::class_<G4Torus, PyG4Torus, G4CSGSolid, py::nodelete>(m, "G4Torus")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double>(), py::arg("pName"),
           py::arg("pRmin"), py::arg("pRmax"), py::arg("pRtor"), py::arg("pSPhi"), py::arg("pDPhi"))

      .def("__copy__", [](const PyG4Torus &self) { return PyG4Torus(self); })
      .def("__deepcopy__", [](const PyG4Torus &self, py::dict) { return PyG4Torus(self); })
      .def("GetRmin", &G4Torus::GetRmin)
      .def("GetRmax", &G4Torus::GetRmax)
      .def("GetRtor", &G4Torus::GetRtor)
      .def("GetSPhi", &G4Torus::GetSPhi)
      .def("GetDPhi", &G4Torus::GetDPhi)
      .def("GetSinStartPhi", &G4Torus::GetSinStartPhi)
      .def("GetCosStartPhi", &G4Torus::GetCosStartPhi)
      .def("GetSinEndPhi", &G4Torus::GetSinEndPhi)
      .def("GetCosEndPhi", &G4Torus::GetCosEndPhi)
      .def("GetCubicVolume", &G4Torus::GetCubicVolume)
      .def("GetSurfaceArea", &G4Torus::GetSurfaceArea)
      .def("Inside", &G4Torus::Inside, py::arg("p"))
      .def("BoundingLimits", &G4Torus::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4Torus::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"),
           py::arg("pTransform"), py::arg("pmin"), py::arg("pmax"))

      .def("ComputeDimensions", &G4Torus::ComputeDimensions, py::arg("p"), py::arg("n"), py::arg("pRep"))

      .def("SurfaceNormal", &G4Torus::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4Torus::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4Torus::DistanceToIn, py::const_), py::arg("p"))

      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4Torus::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false,
           py::arg("validNorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4Torus::DistanceToOut, py::const_), py::arg("p"))

      .def("GetEntityType", &G4Torus::GetEntityType)
      .def("GetPointOnSurface", &G4Torus::GetPointOnSurface)
      .def("Clone", &G4Torus::Clone, py::return_value_policy::reference)
      .def("StreamInfo", &G4Torus::StreamInfo, py::arg("os"))
      .def("DescribeYourselfTo", &G4Torus::DescribeYourselfTo, py::arg("scene"))
      .def("CreatePolyhedron", &G4Torus::CreatePolyhedron, py::return_value_policy::reference)
      .def("SetAllParameters", &G4Torus::SetAllParameters, py::arg("pRmin"), py::arg("pRmax"), py::arg("pRtor"),
           py::arg("pSPhi"), py::arg("pDPhi"));
}
