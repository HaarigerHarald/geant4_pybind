#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Ellipsoid.hh>
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

class PyG4Ellipsoid : public G4Ellipsoid, public py::trampoline_self_life_support {
public:
   using G4Ellipsoid::G4Ellipsoid;

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4Ellipsoid, ComputeDimensions, p, n, pRep);
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Ellipsoid, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4Ellipsoid::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pmin, G4double &pmax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4Ellipsoid, CalculateExtent, pAxis, pVoxelLimit, pTransform, pmin, pmax);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4Ellipsoid, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4Ellipsoid, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Ellipsoid, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Ellipsoid, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Ellipsoid, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Ellipsoid, DistanceToOut, p);
   }

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4Ellipsoid, GetEntityType, ); }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4Ellipsoid, Clone, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4Ellipsoid, StreamInfo, os);
   }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4Ellipsoid, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4Ellipsoid, GetSurfaceArea, ); }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4Ellipsoid, GetPointOnSurface, );
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Ellipsoid, "DescribeYourselfTo", std::addressof(scene));
      G4Ellipsoid::DescribeYourselfTo(scene);
   }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4Ellipsoid, GetExtent, ); }

   G4Polyhedron *CreatePolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4Ellipsoid, CreatePolyhedron, );
   }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Ellipsoid, GetPolyhedron, ); }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4Ellipsoid, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4Ellipsoid, GetConstituentSolid, no);
   }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4Ellipsoid, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4Ellipsoid, GetDisplacedSolidPtr, );
   }
};

void export_G4Ellipsoid(py::module &m)
{
   py::class_<G4Ellipsoid, PyG4Ellipsoid, G4VSolid, py::nodelete>(m, "G4Ellipsoid")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double>(), py::arg("name"),
           py::arg("xSemiAxis"), py::arg("ySemiAxis"), py::arg("zSemiAxis"), py::arg("zBottomCut") = 0.,
           py::arg("zTopCut") = 0.)

      .def("__copy__", [](const PyG4Ellipsoid &self) { return PyG4Ellipsoid(self); })
      .def("__deepcopy__", [](const PyG4Ellipsoid &self, py::dict) { return PyG4Ellipsoid(self); })
      .def("GetDx", &G4Ellipsoid::GetDx)
      .def("GetDy", &G4Ellipsoid::GetDy)
      .def("GetDz", &G4Ellipsoid::GetDz)
      .def("GetSemiAxisMax", &G4Ellipsoid::GetSemiAxisMax, py::arg("i"))
      .def("GetZBottomCut", &G4Ellipsoid::GetZBottomCut)
      .def("GetZTopCut", &G4Ellipsoid::GetZTopCut)
      .def("SetSemiAxis", &G4Ellipsoid::SetSemiAxis, py::arg("x"), py::arg("y"), py::arg("z"))
      .def("SetZCuts", &G4Ellipsoid::SetZCuts, py::arg("newzBottomCut"), py::arg("newzTopCut"))
      .def("ComputeDimensions", &G4Ellipsoid::ComputeDimensions, py::arg("p"), py::arg("n"), py::arg("pRep"))
      .def("BoundingLimits", &G4Ellipsoid::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4Ellipsoid::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"),
           py::arg("pTransform"), py::arg("pmin"), py::arg("pmax"))

      .def("Inside", &G4Ellipsoid::Inside, py::arg("p"))
      .def("SurfaceNormal", &G4Ellipsoid::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4Ellipsoid::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4Ellipsoid::DistanceToIn, py::const_),
           py::arg("p"))

      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4Ellipsoid::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false,
           py::arg("validNorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4Ellipsoid::DistanceToOut, py::const_),
           py::arg("p"))

      .def("GetEntityType", &G4Ellipsoid::GetEntityType)
      .def("Clone", &G4Ellipsoid::Clone, py::return_value_policy::reference)
      .def("StreamInfo", &G4Ellipsoid::StreamInfo, py::arg("os"))
      .def("GetCubicVolume", &G4Ellipsoid::GetCubicVolume)
      .def("GetSurfaceArea", &G4Ellipsoid::GetSurfaceArea)
      .def("GetPointOnSurface", &G4Ellipsoid::GetPointOnSurface)
      .def("DescribeYourselfTo", &G4Ellipsoid::DescribeYourselfTo, py::arg("scene"))
      .def("GetExtent", &G4Ellipsoid::GetExtent)
      .def("CreatePolyhedron", &G4Ellipsoid::CreatePolyhedron, py::return_value_policy::reference)
      .def("GetPolyhedron", &G4Ellipsoid::GetPolyhedron, py::return_value_policy::reference);
}
