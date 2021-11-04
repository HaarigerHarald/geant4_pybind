#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4BooleanSolid.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4BooleanSolid : public G4BooleanSolid, public py::trampoline_self_life_support {
public:
   using G4BooleanSolid::G4BooleanSolid;

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pMin, G4double &pMax) const override
   {
      PYBIND11_OVERRIDE_PURE(G4bool, G4BooleanSolid, CalculateExtent, pAxis, pVoxelLimit, pTransform, pMin, pMax);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE_PURE(EInside, G4BooleanSolid, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE_PURE(G4ThreeVector, G4BooleanSolid, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4BooleanSolid, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4BooleanSolid, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4BooleanSolid, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4BooleanSolid, DistanceToOut, p);
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_PURE(void, G4BooleanSolid, DescribeYourselfTo, std::addressof(scene));
   }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4BooleanSolid, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4BooleanSolid, GetConstituentSolid, no);
   }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4BooleanSolid, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4BooleanSolid, GetSurfaceArea, ); }

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4BooleanSolid, GetEntityType, ); }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4BooleanSolid, GetPolyhedron, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4BooleanSolid, StreamInfo, os);
   }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4BooleanSolid, GetPointOnSurface, );
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4BooleanSolid, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4BooleanSolid::BoundingLimits(pMin, pMax);
   }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4BooleanSolid, ComputeDimensions, p, n, pRep);
   }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4BooleanSolid, Clone, ); }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4BooleanSolid, GetExtent, ); }

   G4Polyhedron *CreatePolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4BooleanSolid, CreatePolyhedron, );
   }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4BooleanSolid, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4BooleanSolid, GetDisplacedSolidPtr, );
   }
};

void export_G4BooleanSolid(py::module &m)
{
   py::class_<G4BooleanSolid, PyG4BooleanSolid, G4VSolid, py::nodelete>(m, "G4BooleanSolid")

      .def(py::init<const G4String &, G4VSolid *, G4VSolid *>(), py::arg("pName"), py::arg("pSolidA"),
           py::arg("pSolidB"))

      .def(py::init<const G4String &, G4VSolid *, G4VSolid *, G4RotationMatrix *, const G4ThreeVector &>(),
           py::arg("pName"), py::arg("pSolidA"), py::arg("pSolidB"), py::arg("rotMatrix"), py::arg("transVector"))

      .def(py::init<const G4String &, G4VSolid *, G4VSolid *, const G4Transform3D &>(), py::arg("pName"),
           py::arg("pSolidA"), py::arg("pSolidB"), py::arg("transform"))

      .def("__copy__", [](const PyG4BooleanSolid &self) { return PyG4BooleanSolid(self); })
      .def("__deepcopy__", [](const PyG4BooleanSolid &self, py::dict) { return PyG4BooleanSolid(self); })
      .def("GetConstituentSolid", py::overload_cast<G4int>(&G4BooleanSolid::GetConstituentSolid, py::const_),
           py::arg("no"), py::return_value_policy::reference)

      .def("GetConstituentSolid", py::overload_cast<G4int>(&G4BooleanSolid::GetConstituentSolid), py::arg("no"),
           py::return_value_policy::reference)

      .def("GetCubicVolume", &G4BooleanSolid::GetCubicVolume)
      .def("GetSurfaceArea", &G4BooleanSolid::GetSurfaceArea)
      .def("GetEntityType", &G4BooleanSolid::GetEntityType)
      .def("GetPolyhedron", &G4BooleanSolid::GetPolyhedron, py::return_value_policy::reference)
      .def("StreamInfo", &G4BooleanSolid::StreamInfo, py::arg("os"))
      .def("GetCubVolStatistics", &G4BooleanSolid::GetCubVolStatistics)
      .def("GetCubVolEpsilon", &G4BooleanSolid::GetCubVolEpsilon)
      .def("SetCubVolStatistics", &G4BooleanSolid::SetCubVolStatistics, py::arg("st"))
      .def("SetCubVolEpsilon", &G4BooleanSolid::SetCubVolEpsilon, py::arg("ep"))
      .def("GetAreaStatistics", &G4BooleanSolid::GetAreaStatistics)
      .def("GetAreaAccuracy", &G4BooleanSolid::GetAreaAccuracy)
      .def("SetAreaStatistics", &G4BooleanSolid::SetAreaStatistics, py::arg("st"))
      .def("SetAreaAccuracy", &G4BooleanSolid::SetAreaAccuracy, py::arg("ep"))
      .def("GetPointOnSurface", &G4BooleanSolid::GetPointOnSurface);
}
