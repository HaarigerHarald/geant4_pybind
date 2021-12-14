#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Tet.hh>
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

class PyG4Tet : public G4Tet, public py::trampoline_self_life_support {
public:
   using G4Tet::G4Tet;

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4Tet, ComputeDimensions, p, n, pRep);
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Tet, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4Tet::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pmin, G4double &pmax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4Tet, CalculateExtent, pAxis, pVoxelLimit, pTransform, pmin, pmax);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4Tet, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4Tet, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Tet, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(G4double, G4Tet, DistanceToIn, p); }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Tet, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Tet, DistanceToOut, p);
   }

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4Tet, GetEntityType, ); }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4Tet, Clone, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4Tet, StreamInfo, os);
   }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4Tet, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4Tet, GetSurfaceArea, ); }

   G4ThreeVector GetPointOnSurface() const override { PYBIND11_OVERRIDE(G4ThreeVector, G4Tet, GetPointOnSurface, ); }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Tet, "DescribeYourselfTo", std::addressof(scene));
      G4Tet::DescribeYourselfTo(scene);
   }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4Tet, GetExtent, ); }

   G4Polyhedron *CreatePolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Tet, CreatePolyhedron, ); }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Tet, GetPolyhedron, ); }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4Tet, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override { PYBIND11_OVERRIDE(G4VSolid *, G4Tet, GetConstituentSolid, no); }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4Tet, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4Tet, GetDisplacedSolidPtr, );
   }
};

void export_G4Tet(py::module &m)
{
   py::class_<G4Tet, PyG4Tet, G4VSolid, py::nodelete>(m, "G4Tet")

      .def(py::init<const G4String &, const G4ThreeVector &, const G4ThreeVector &, const G4ThreeVector &,
                    const G4ThreeVector &, G4bool *>(),
           py::arg("pName"), py::arg("anchor"), py::arg("p1"), py::arg("p2"), py::arg("p3"),
           py::arg("degeneracyFlag") = static_cast<G4bool *>(nullptr))

      .def("__copy__", [](const PyG4Tet &self) { return PyG4Tet(self); })
      .def("__deepcopy__", [](const PyG4Tet &self, py::dict) { return PyG4Tet(self); })
      .def("SetVertices", &G4Tet::SetVertices, py::arg("anchor"), py::arg("p1"), py::arg("p2"), py::arg("p3"),
           py::arg("degeneracyFlag") = static_cast<G4bool *>(nullptr))

      .def("GetVertices",
           py::overload_cast<G4ThreeVector &, G4ThreeVector &, G4ThreeVector &, G4ThreeVector &>(&G4Tet::GetVertices,
                                                                                                 py::const_),
           py::arg("anchor"), py::arg("p1"), py::arg("p2"), py::arg("p3"))

      .def("GetVertices", py::overload_cast<>(&G4Tet::GetVertices, py::const_))
      .def("PrintWarnings", &G4Tet::PrintWarnings)
      .def("CheckDegeneracy", &G4Tet::CheckDegeneracy, py::arg("p0"), py::arg("p1"), py::arg("p2"), py::arg("p3"))
      .def("ComputeDimensions", &G4Tet::ComputeDimensions, py::arg("p"), py::arg("n"), py::arg("pRep"))
      .def("BoundingLimits", &G4Tet::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4Tet::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"), py::arg("pTransform"),
           py::arg("pmin"), py::arg("pmax"))

      .def("Inside", &G4Tet::Inside, py::arg("p"))
      .def("SurfaceNormal", &G4Tet::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4Tet::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4Tet::DistanceToIn, py::const_), py::arg("p"))
      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4Tet::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false,
           py::arg("validNorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4Tet::DistanceToOut, py::const_), py::arg("p"))
      .def("GetEntityType", &G4Tet::GetEntityType)
      .def("Clone", &G4Tet::Clone, py::return_value_policy::reference)
      .def("StreamInfo", &G4Tet::StreamInfo, py::arg("os"))
      .def("GetCubicVolume", &G4Tet::GetCubicVolume)
      .def("GetSurfaceArea", &G4Tet::GetSurfaceArea)
      .def("GetPointOnSurface", &G4Tet::GetPointOnSurface)
      .def("DescribeYourselfTo", &G4Tet::DescribeYourselfTo, py::arg("scene"))
      .def("GetExtent", &G4Tet::GetExtent)
      .def("CreatePolyhedron", &G4Tet::CreatePolyhedron, py::return_value_policy::reference)
      .def("GetPolyhedron", &G4Tet::GetPolyhedron, py::return_value_policy::reference);
}
