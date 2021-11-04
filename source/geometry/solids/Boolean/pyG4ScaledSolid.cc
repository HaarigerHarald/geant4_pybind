#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ScaledSolid.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>
#include <G4ScaleTransform.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4ScaledSolid : public G4ScaledSolid, public py::trampoline_self_life_support {
public:
   using G4ScaledSolid::G4ScaledSolid;

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4ScaledSolid, Inside, p); }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ScaledSolid, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4ScaledSolid::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pMin, G4double &pMax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4ScaledSolid, CalculateExtent, pAxis, pVoxelLimit, pTransform, pMin, pMax);
   }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4ScaledSolid, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4ScaledSolid, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4ScaledSolid, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4ScaledSolid, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4ScaledSolid, DistanceToOut, p);
   }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4ScaledSolid, ComputeDimensions, p, n, pRep);
   }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4ScaledSolid, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4ScaledSolid, GetSurfaceArea, ); }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4ScaledSolid, GetPointOnSurface, );
   }

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4ScaledSolid, GetEntityType, ); }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4ScaledSolid, Clone, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4ScaledSolid, StreamInfo, os);
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ScaledSolid, "DescribeYourselfTo", std::addressof(scene));
      G4ScaledSolid::DescribeYourselfTo(scene);
   }

   G4Polyhedron *CreatePolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4ScaledSolid, CreatePolyhedron, );
   }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4ScaledSolid, GetPolyhedron, ); }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4ScaledSolid, GetExtent, ); }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4ScaledSolid, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4ScaledSolid, GetConstituentSolid, no);
   }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4ScaledSolid, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4ScaledSolid, GetDisplacedSolidPtr, );
   }
};

void export_G4ScaledSolid(py::module &m)
{
   py::class_<G4ScaledSolid, PyG4ScaledSolid, G4VSolid, py::nodelete>(m, "G4ScaledSolid")

      .def(py::init<const G4String &, G4VSolid *, const G4Scale3D &>(), py::arg("pName"), py::arg("pSolid"),
           py::arg("pScale"))

      .def("__copy__", [](const PyG4ScaledSolid &self) { return PyG4ScaledSolid(self); })
      .def("__deepcopy__", [](const PyG4ScaledSolid &self, py::dict) { return PyG4ScaledSolid(self); })
      .def("Inside", &G4ScaledSolid::Inside, py::arg("p"))
      .def("BoundingLimits", &G4ScaledSolid::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4ScaledSolid::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"),
           py::arg("pTransform"), py::arg("pMin"), py::arg("pMax"))

      .def("SurfaceNormal", &G4ScaledSolid::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4ScaledSolid::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4ScaledSolid::DistanceToIn, py::const_),
           py::arg("p"))

      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4ScaledSolid::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false,
           py::arg("validNorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4ScaledSolid::DistanceToOut, py::const_),
           py::arg("p"))

      .def("ComputeDimensions", &G4ScaledSolid::ComputeDimensions, py::arg("p"), py::arg("n"), py::arg("pRep"))
      .def("GetCubicVolume", &G4ScaledSolid::GetCubicVolume)
      .def("GetSurfaceArea", &G4ScaledSolid::GetSurfaceArea)
      //.def("CleanTransformations", &G4ScaledSolid::CleanTransformations)
      .def("GetPointOnSurface", &G4ScaledSolid::GetPointOnSurface)
      .def("GetScaleTransform", &G4ScaledSolid::GetScaleTransform)
      .def("SetScaleTransform", &G4ScaledSolid::SetScaleTransform, py::arg("scale"))
      .def("GetUnscaledSolid", &G4ScaledSolid::GetUnscaledSolid, py::return_value_policy::reference)
      .def("GetEntityType", &G4ScaledSolid::GetEntityType)
      .def("Clone", &G4ScaledSolid::Clone, py::return_value_policy::reference)
      .def("StreamInfo", &G4ScaledSolid::StreamInfo, py::arg("os"))
      .def("DescribeYourselfTo", &G4ScaledSolid::DescribeYourselfTo, py::arg("scene"))
      .def("CreatePolyhedron", &G4ScaledSolid::CreatePolyhedron, py::return_value_policy::reference)
      .def("GetPolyhedron", &G4ScaledSolid::GetPolyhedron, py::return_value_policy::reference);
}
