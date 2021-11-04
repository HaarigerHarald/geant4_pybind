#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ReflectedSolid.hh>
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

class PyG4ReflectedSolid : public G4ReflectedSolid, public py::trampoline_self_life_support {
public:
   using G4ReflectedSolid::G4ReflectedSolid;

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4ReflectedSolid, Inside, p); }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ReflectedSolid, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4ReflectedSolid::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pMin, G4double &pMax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4ReflectedSolid, CalculateExtent, pAxis, pVoxelLimit, pTransform, pMin, pMax);
   }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4ReflectedSolid, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4ReflectedSolid, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4ReflectedSolid, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4ReflectedSolid, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4ReflectedSolid, DistanceToOut, p);
   }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4ReflectedSolid, ComputeDimensions, p, n, pRep);
   }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4ReflectedSolid, GetPointOnSurface, );
   }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4ReflectedSolid, Clone, ); }

   G4GeometryType GetEntityType() const override
   {
      PYBIND11_OVERRIDE(G4GeometryType, G4ReflectedSolid, GetEntityType, );
   }

   const G4ReflectedSolid *GetReflectedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4ReflectedSolid *, G4ReflectedSolid, GetReflectedSolidPtr, );
   }

   G4ReflectedSolid *GetReflectedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4ReflectedSolid *, G4ReflectedSolid, GetReflectedSolidPtr, );
   }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4ReflectedSolid, StreamInfo, os);
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ReflectedSolid, "DescribeYourselfTo", std::addressof(scene));
      G4ReflectedSolid::DescribeYourselfTo(scene);
   }

   G4Polyhedron *CreatePolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4ReflectedSolid, CreatePolyhedron, );
   }

   G4Polyhedron *GetPolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4ReflectedSolid, GetPolyhedron, );
   }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4ReflectedSolid, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4ReflectedSolid, GetSurfaceArea, ); }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4ReflectedSolid, GetExtent, ); }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4ReflectedSolid, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4ReflectedSolid, GetConstituentSolid, no);
   }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4ReflectedSolid, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4ReflectedSolid, GetDisplacedSolidPtr, );
   }
};

void export_G4ReflectedSolid(py::module &m)
{
   py::class_<G4ReflectedSolid, PyG4ReflectedSolid, G4VSolid>(m, "G4ReflectedSolid")

      .def(py::init<const G4String &, G4VSolid *, const G4Transform3D &>(), py::arg("pName"), py::arg("pSolid"),
           py::arg("transform"))

      .def("__copy__", [](const PyG4ReflectedSolid &self) { return PyG4ReflectedSolid(self); })
      .def("__deepcopy__", [](const PyG4ReflectedSolid &self, py::dict) { return PyG4ReflectedSolid(self); })
      .def("Inside", &G4ReflectedSolid::Inside, py::arg("p"))
      .def("BoundingLimits", &G4ReflectedSolid::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4ReflectedSolid::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"),
           py::arg("pTransform"), py::arg("pMin"), py::arg("pMax"))

      .def("SurfaceNormal", &G4ReflectedSolid::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4ReflectedSolid::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4ReflectedSolid::DistanceToIn, py::const_),
           py::arg("p"))

      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4ReflectedSolid::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false,
           py::arg("validNorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4ReflectedSolid::DistanceToOut, py::const_),
           py::arg("p"))

      .def("ComputeDimensions", &G4ReflectedSolid::ComputeDimensions, py::arg("p"), py::arg("n"), py::arg("pRep"))
      .def("GetPointOnSurface", &G4ReflectedSolid::GetPointOnSurface)
      .def("Clone", &G4ReflectedSolid::Clone, py::return_value_policy::reference)
      .def("GetEntityType", &G4ReflectedSolid::GetEntityType)
      .def("GetReflectedSolidPtr", py::overload_cast<>(&G4ReflectedSolid::GetReflectedSolidPtr, py::const_),
           py::return_value_policy::reference)

      .def("GetReflectedSolidPtr", py::overload_cast<>(&G4ReflectedSolid::GetReflectedSolidPtr),
           py::return_value_policy::reference)

      .def("GetConstituentMovedSolid", &G4ReflectedSolid::GetConstituentMovedSolid, py::return_value_policy::reference)
      .def("GetTransform3D", &G4ReflectedSolid::GetTransform3D)
      .def("GetDirectTransform3D", &G4ReflectedSolid::GetDirectTransform3D)
      .def("SetDirectTransform3D", &G4ReflectedSolid::SetDirectTransform3D)
      .def("StreamInfo", &G4ReflectedSolid::StreamInfo, py::arg("os"))
      .def("DescribeYourselfTo", &G4ReflectedSolid::DescribeYourselfTo, py::arg("scene"))
      .def("CreatePolyhedron", &G4ReflectedSolid::CreatePolyhedron, py::return_value_policy::reference)
      .def("GetPolyhedron", &G4ReflectedSolid::GetPolyhedron, py::return_value_policy::reference);
}
