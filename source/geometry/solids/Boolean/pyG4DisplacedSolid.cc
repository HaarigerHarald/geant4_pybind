#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4DisplacedSolid.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4DisplacedSolid : public G4DisplacedSolid, public py::trampoline_self_life_support {
public:
   using G4DisplacedSolid::G4DisplacedSolid;

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4DisplacedSolid, Inside, p); }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4DisplacedSolid, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4DisplacedSolid::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pMin, G4double &pMax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4DisplacedSolid, CalculateExtent, pAxis, pVoxelLimit, pTransform, pMin, pMax);
   }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4DisplacedSolid, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4DisplacedSolid, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4DisplacedSolid, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4DisplacedSolid, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4DisplacedSolid, DistanceToOut, p);
   }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4DisplacedSolid, ComputeDimensions, p, n, pRep);
   }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4DisplacedSolid, GetPointOnSurface, );
   }

   G4GeometryType GetEntityType() const override
   {
      PYBIND11_OVERRIDE(G4GeometryType, G4DisplacedSolid, GetEntityType, );
   }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4DisplacedSolid, Clone, ); }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4DisplacedSolid, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4DisplacedSolid, GetDisplacedSolidPtr, );
   }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4DisplacedSolid, StreamInfo, os);
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4DisplacedSolid, "DescribeYourselfTo", std::addressof(scene));
      G4DisplacedSolid::DescribeYourselfTo(scene);
   }

   G4Polyhedron *CreatePolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4DisplacedSolid, CreatePolyhedron, );
   }

   G4Polyhedron *GetPolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4DisplacedSolid, GetPolyhedron, );
   }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4DisplacedSolid, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4DisplacedSolid, GetSurfaceArea, ); }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4DisplacedSolid, GetExtent, ); }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4DisplacedSolid, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4DisplacedSolid, GetConstituentSolid, no);
   }
};

void export_G4DisplacedSolid(py::module &m)
{
   py::class_<G4DisplacedSolid, PyG4DisplacedSolid, G4VSolid, py::nodelete>(m, "G4DisplacedSolid")

      .def(py::init<const G4String &, G4VSolid *, G4RotationMatrix *, const G4ThreeVector &>(), py::arg("pName"),
           py::arg("pSolid"), py::arg("rotMatrix"), py::arg("transVector"))

      .def(py::init<const G4String &, G4VSolid *, const G4Transform3D &>(), py::arg("pName"), py::arg("pSolid"),
           py::arg("transform"))

      .def(py::init<const G4String &, G4VSolid *, const G4AffineTransform>(), py::arg("pName"), py::arg("pSolid"),
           py::arg("directTransform"))

      .def("__copy__", [](const PyG4DisplacedSolid &self) { return PyG4DisplacedSolid(self); })
      .def("__deepcopy__", [](const PyG4DisplacedSolid &self, py::dict) { return PyG4DisplacedSolid(self); })
      .def("Inside", &G4DisplacedSolid::Inside, py::arg("p"))
      .def("BoundingLimits", &G4DisplacedSolid::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4DisplacedSolid::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"),
           py::arg("pTransform"), py::arg("pMin"), py::arg("pMax"))

      .def("SurfaceNormal", &G4DisplacedSolid::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4DisplacedSolid::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4DisplacedSolid::DistanceToIn, py::const_),
           py::arg("p"))

      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4DisplacedSolid::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false, py::arg("validNorm") = static_cast<G4bool *>(0),
           py::arg("n") = static_cast<G4ThreeVector *>(0))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4DisplacedSolid::DistanceToOut, py::const_),
           py::arg("p"))

      .def("ComputeDimensions", &G4DisplacedSolid::ComputeDimensions, py::arg("p"), py::arg("n"), py::arg("pRep"))
      .def("CleanTransformations", &G4DisplacedSolid::CleanTransformations)
      .def("GetPointOnSurface", &G4DisplacedSolid::GetPointOnSurface)
      .def("GetEntityType", &G4DisplacedSolid::GetEntityType)
      .def("Clone", &G4DisplacedSolid::Clone, py::return_value_policy::reference)
      .def("GetDisplacedSolidPtr", py::overload_cast<>(&G4DisplacedSolid::GetDisplacedSolidPtr, py::const_),
           py::return_value_policy::reference)

      .def("GetDisplacedSolidPtr", py::overload_cast<>(&G4DisplacedSolid::GetDisplacedSolidPtr),
           py::return_value_policy::reference)

      .def("GetConstituentMovedSolid", &G4DisplacedSolid::GetConstituentMovedSolid, py::return_value_policy::reference)
      .def("GetTransform", &G4DisplacedSolid::GetTransform)
      .def("SetTransform", &G4DisplacedSolid::SetTransform)
      .def("GetDirectTransform", &G4DisplacedSolid::GetDirectTransform)
      .def("SetDirectTransform", &G4DisplacedSolid::SetDirectTransform)
      .def("GetFrameRotation", &G4DisplacedSolid::GetFrameRotation)
      .def("SetFrameRotation", &G4DisplacedSolid::SetFrameRotation)
      .def("GetFrameTranslation", &G4DisplacedSolid::GetFrameTranslation)
      .def("SetFrameTranslation", &G4DisplacedSolid::SetFrameTranslation)
      .def("GetObjectRotation", &G4DisplacedSolid::GetObjectRotation)
      .def("SetObjectRotation", &G4DisplacedSolid::SetObjectRotation)
      .def("GetObjectTranslation", &G4DisplacedSolid::GetObjectTranslation)
      .def("SetObjectTranslation", &G4DisplacedSolid::SetObjectTranslation)
      .def("StreamInfo", &G4DisplacedSolid::StreamInfo, py::arg("os"))
      .def("DescribeYourselfTo", &G4DisplacedSolid::DescribeYourselfTo, py::arg("scene"))
      .def("CreatePolyhedron", &G4DisplacedSolid::CreatePolyhedron, py::return_value_policy::reference)
      .def("GetPolyhedron", &G4DisplacedSolid::GetPolyhedron, py::return_value_policy::reference);
}
