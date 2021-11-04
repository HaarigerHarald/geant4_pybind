#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4GenericTrap.hh>
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

class PyG4GenericTrap : public G4GenericTrap, public py::trampoline_self_life_support {
public:
   using G4GenericTrap::G4GenericTrap;

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4GenericTrap, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4GenericTrap, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4GenericTrap, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4GenericTrap, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4GenericTrap, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4GenericTrap, DistanceToOut, p);
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4GenericTrap, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4GenericTrap::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pmin, G4double &pmax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4GenericTrap, CalculateExtent, pAxis, pVoxelLimit, pTransform, pmin, pmax);
   }

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4GenericTrap, GetEntityType, ); }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4GenericTrap, Clone, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4GenericTrap, StreamInfo, os);
   }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4GenericTrap, GetPointOnSurface, );
   }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4GenericTrap, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4GenericTrap, GetSurfaceArea, ); }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4GenericTrap, GetPolyhedron, ); }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4GenericTrap, "DescribeYourselfTo", std::addressof(scene));
      G4GenericTrap::DescribeYourselfTo(scene);
   }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4GenericTrap, GetExtent, ); }

   G4Polyhedron *CreatePolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4GenericTrap, CreatePolyhedron, );
   }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4GenericTrap, ComputeDimensions, p, n, pRep);
   }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4GenericTrap, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4GenericTrap, GetConstituentSolid, no);
   }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4GenericTrap, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4GenericTrap, GetDisplacedSolidPtr, );
   }
};

void export_G4GenericTrap(py::module &m)
{
   py::class_<G4GenericTrap, PyG4GenericTrap, G4VSolid, py::nodelete>(m, "G4GenericTrap")

      .def(py::init<const G4String &, G4double,
                    const std::vector<CLHEP::Hep2Vector, std::allocator<CLHEP::Hep2Vector>> &>(),
           py::arg("name"), py::arg("halfZ"), py::arg("vertices"))

      .def("__copy__", [](const PyG4GenericTrap &self) { return PyG4GenericTrap(self); })
      .def("__deepcopy__", [](const PyG4GenericTrap &self, py::dict) { return PyG4GenericTrap(self); })
      .def("GetZHalfLength", &G4GenericTrap::GetZHalfLength)
      .def("GetNofVertices", &G4GenericTrap::GetNofVertices)
      .def("GetVertex", &G4GenericTrap::GetVertex, py::arg("index"))
      .def("GetVertices", &G4GenericTrap::GetVertices)
      .def("GetTwistAngle", &G4GenericTrap::GetTwistAngle, py::arg("index"))
      .def("IsTwisted", &G4GenericTrap::IsTwisted)
      .def("GetVisSubdivisions", &G4GenericTrap::GetVisSubdivisions)
      .def("SetVisSubdivisions", &G4GenericTrap::SetVisSubdivisions, py::arg("subdiv"))
      .def("Inside", &G4GenericTrap::Inside, py::arg("p"))
      .def("SurfaceNormal", &G4GenericTrap::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4GenericTrap::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4GenericTrap::DistanceToIn, py::const_),
           py::arg("p"))

      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4GenericTrap::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false,
           py::arg("validNorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4GenericTrap::DistanceToOut, py::const_),
           py::arg("p"))

      .def("BoundingLimits", &G4GenericTrap::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4GenericTrap::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"),
           py::arg("pTransform"), py::arg("pmin"), py::arg("pmax"))

      .def("GetEntityType", &G4GenericTrap::GetEntityType)
      .def("Clone", &G4GenericTrap::Clone, py::return_value_policy::reference)
      .def("StreamInfo", &G4GenericTrap::StreamInfo, py::arg("os"))
      .def("GetPointOnSurface", &G4GenericTrap::GetPointOnSurface)
      .def("GetCubicVolume", &G4GenericTrap::GetCubicVolume)
      .def("GetSurfaceArea", &G4GenericTrap::GetSurfaceArea)
      .def("GetPolyhedron", &G4GenericTrap::GetPolyhedron, py::return_value_policy::reference)
      .def("DescribeYourselfTo", &G4GenericTrap::DescribeYourselfTo, py::arg("scene"))
      .def("GetExtent", &G4GenericTrap::GetExtent)
      .def("CreatePolyhedron", &G4GenericTrap::CreatePolyhedron, py::return_value_policy::reference);
}
