#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4EllipticalTube.hh>
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

class PyG4EllipticalTube : public G4EllipticalTube, public py::trampoline_self_life_support {
public:
   using G4EllipticalTube::G4EllipticalTube;

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4EllipticalTube, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4EllipticalTube::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pmin, G4double &pmax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4EllipticalTube, CalculateExtent, pAxis, pVoxelLimit, pTransform, pmin, pmax);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4EllipticalTube, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4EllipticalTube, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4EllipticalTube, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4EllipticalTube, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4EllipticalTube, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4EllipticalTube, DistanceToOut, p);
   }

   G4GeometryType GetEntityType() const override
   {
      PYBIND11_OVERRIDE(G4GeometryType, G4EllipticalTube, GetEntityType, );
   }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4EllipticalTube, Clone, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4EllipticalTube, StreamInfo, os);
   }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4EllipticalTube, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4EllipticalTube, GetSurfaceArea, ); }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4EllipticalTube, GetPointOnSurface, );
   }

   G4Polyhedron *CreatePolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4EllipticalTube, CreatePolyhedron, );
   }

   G4Polyhedron *GetPolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4EllipticalTube, GetPolyhedron, );
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4EllipticalTube, "DescribeYourselfTo", std::addressof(scene));
      G4EllipticalTube::DescribeYourselfTo(scene);
   }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4EllipticalTube, GetExtent, ); }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4EllipticalTube, ComputeDimensions, p, n, pRep);
   }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4EllipticalTube, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4EllipticalTube, GetConstituentSolid, no);
   }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4EllipticalTube, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4EllipticalTube, GetDisplacedSolidPtr, );
   }
};

void export_G4EllipticalTube(py::module &m)
{
   py::class_<G4EllipticalTube, PyG4EllipticalTube, G4VSolid, py::nodelete>(m, "G4EllipticalTube")

      .def(py::init<const G4String &, G4double, G4double, G4double>(), py::arg("name"), py::arg("Dx"), py::arg("Dy"),
           py::arg("Dz"))

      .def("__copy__", [](const PyG4EllipticalTube &self) { return PyG4EllipticalTube(self); })
      .def("__deepcopy__", [](const PyG4EllipticalTube &self, py::dict) { return PyG4EllipticalTube(self); })

      .def("BoundingLimits", &G4EllipticalTube::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4EllipticalTube::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"),
           py::arg("pTransform"), py::arg("pmin"), py::arg("pmax"))

      .def("Inside", &G4EllipticalTube::Inside, py::arg("p"))
      .def("SurfaceNormal", &G4EllipticalTube::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4EllipticalTube::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4EllipticalTube::DistanceToIn, py::const_),
           py::arg("p"))

      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4EllipticalTube::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false,
           py::arg("validNorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4EllipticalTube::DistanceToOut, py::const_),
           py::arg("p"))

      .def("GetEntityType", &G4EllipticalTube::GetEntityType)
      .def("Clone", &G4EllipticalTube::Clone, py::return_value_policy::reference)
      .def("StreamInfo", &G4EllipticalTube::StreamInfo, py::arg("os"))
      .def("GetCubicVolume", &G4EllipticalTube::GetCubicVolume)
      .def("GetSurfaceArea", &G4EllipticalTube::GetSurfaceArea)
      .def("GetPointOnSurface", &G4EllipticalTube::GetPointOnSurface)
      .def("CreatePolyhedron", &G4EllipticalTube::CreatePolyhedron, py::return_value_policy::reference)
      .def("GetPolyhedron", &G4EllipticalTube::GetPolyhedron, py::return_value_policy::reference)
      .def("DescribeYourselfTo", &G4EllipticalTube::DescribeYourselfTo, py::arg("scene"))
      .def("GetExtent", &G4EllipticalTube::GetExtent)
      .def("GetDx", &G4EllipticalTube::GetDx)
      .def("GetDy", &G4EllipticalTube::GetDy)
      .def("GetDz", &G4EllipticalTube::GetDz)
      .def("SetDx", &G4EllipticalTube::SetDx, py::arg("Dx"))
      .def("SetDy", &G4EllipticalTube::SetDy, py::arg("Dy"))
      .def("SetDz", &G4EllipticalTube::SetDz, py::arg("Dz"));
}
