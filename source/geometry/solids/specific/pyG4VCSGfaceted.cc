#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VCSGfaceted.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>
#include <G4VCSGface.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VCSGfaceted : public G4VCSGfaceted, public py::trampoline_self_life_support {
public:
   using G4VCSGfaceted::G4VCSGfaceted;

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pmin, G4double &pmax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4VCSGfaceted, CalculateExtent, pAxis, pVoxelLimit, pTransform, pmin, pmax);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4VCSGfaceted, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4VCSGfaceted, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4VCSGfaceted, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4VCSGfaceted, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4VCSGfaceted, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4VCSGfaceted, DistanceToOut, p);
   }

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4VCSGfaceted, GetEntityType, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4VCSGfaceted, StreamInfo, os);
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VCSGfaceted, "DescribeYourselfTo", std::addressof(scene));
      G4VCSGfaceted::DescribeYourselfTo(scene);
   }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4VCSGfaceted, GetExtent, ); }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4VCSGfaceted, GetPolyhedron, ); }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4VCSGfaceted, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4VCSGfaceted, GetSurfaceArea, ); }

   G4double DistanceTo(const G4ThreeVector &p, const G4bool outgoing) const override
   {
      PYBIND11_OVERRIDE(G4double, G4VCSGfaceted, DistanceTo, p, outgoing);
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VCSGfaceted, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4VCSGfaceted::BoundingLimits(pMin, pMax);
   }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4VCSGfaceted, ComputeDimensions, p, n, pRep);
   }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4VCSGfaceted, GetPointOnSurface, );
   }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4VCSGfaceted, Clone, ); }

   G4Polyhedron *CreatePolyhedron() const override
   {
      PYBIND11_OVERRIDE_PURE(G4Polyhedron *, G4VCSGfaceted, CreatePolyhedron, );
   }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4VCSGfaceted, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4VCSGfaceted, GetConstituentSolid, no);
   }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4VCSGfaceted, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4VCSGfaceted, GetDisplacedSolidPtr, );
   }
};

void export_G4VCSGfaceted(py::module &m)
{
   py::class_<G4VCSGfaceted, PyG4VCSGfaceted, G4VSolid, py::nodelete>(m, "G4VCSGfaceted")

      .def(py::init<const G4String &>(), py::arg("name"))
      .def("__copy__", [](const PyG4VCSGfaceted &self) { return PyG4VCSGfaceted(self); })
      .def("__deepcopy__", [](const PyG4VCSGfaceted &self, py::dict) { return PyG4VCSGfaceted(self); })
      .def("CalculateExtent", &G4VCSGfaceted::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"),
           py::arg("pTransform"), py::arg("pmin"), py::arg("pmax"))

      .def("Inside", &G4VCSGfaceted::Inside, py::arg("p"))
      .def("SurfaceNormal", &G4VCSGfaceted::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4VCSGfaceted::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4VCSGfaceted::DistanceToIn, py::const_),
           py::arg("p"))

      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4VCSGfaceted::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false,
           py::arg("validNorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4VCSGfaceted::DistanceToOut, py::const_),
           py::arg("p"))

      .def("GetEntityType", &G4VCSGfaceted::GetEntityType)
      .def("StreamInfo", &G4VCSGfaceted::StreamInfo, py::arg("os"))
      .def("CreatePolyhedron", &G4VCSGfaceted::CreatePolyhedron, py::return_value_policy::reference)
      .def("DescribeYourselfTo", &G4VCSGfaceted::DescribeYourselfTo, py::arg("scene"))
      .def("GetExtent", &G4VCSGfaceted::GetExtent)
      .def("GetPolyhedron", &G4VCSGfaceted::GetPolyhedron, py::return_value_policy::reference)
      .def("GetCubVolStatistics", &G4VCSGfaceted::GetCubVolStatistics)
      .def("GetCubVolEpsilon", &G4VCSGfaceted::GetCubVolEpsilon)
      .def("SetCubVolStatistics", &G4VCSGfaceted::SetCubVolStatistics, py::arg("st"))
      .def("SetCubVolEpsilon", &G4VCSGfaceted::SetCubVolEpsilon, py::arg("ep"))
      .def("GetAreaStatistics", &G4VCSGfaceted::GetAreaStatistics)
      .def("GetAreaAccuracy", &G4VCSGfaceted::GetAreaAccuracy)
      .def("SetAreaStatistics", &G4VCSGfaceted::SetAreaStatistics, py::arg("st"))
      .def("SetAreaAccuracy", &G4VCSGfaceted::SetAreaAccuracy, py::arg("ep"))
      .def("GetCubicVolume", &G4VCSGfaceted::GetCubicVolume)
      .def("GetSurfaceArea", &G4VCSGfaceted::GetSurfaceArea);
}
