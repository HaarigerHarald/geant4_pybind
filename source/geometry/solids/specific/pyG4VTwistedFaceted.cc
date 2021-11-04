#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VTwistedFaceted.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>
#include <G4SolidExtentList.hh>
#include <G4ClippablePolygon.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VTwistedFaceted : public G4VTwistedFaceted, public py::trampoline_self_life_support {
public:
   using G4VTwistedFaceted::G4VTwistedFaceted;

   void ComputeDimensions(G4VPVParameterisation *arg0, const G4int arg1, const G4VPhysicalVolume *arg2) override
   {
      PYBIND11_OVERRIDE(void, G4VTwistedFaceted, ComputeDimensions, arg0, arg1, arg2);
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VTwistedFaceted, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4VTwistedFaceted::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pMin, G4double &pMax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4VTwistedFaceted, CalculateExtent, pAxis, pVoxelLimit, pTransform, pMin, pMax);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4VTwistedFaceted, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4VTwistedFaceted, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcnorm, G4bool *validnorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4VTwistedFaceted, DistanceToOut, p, v, calcnorm, validnorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4VTwistedFaceted, DistanceToOut, p);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4VTwistedFaceted, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4VTwistedFaceted, SurfaceNormal, p);
   }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4VTwistedFaceted, GetPointOnSurface, );
   }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4VTwistedFaceted, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4VTwistedFaceted, GetSurfaceArea, ); }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VTwistedFaceted, "DescribeYourselfTo", std::addressof(scene));
      G4VTwistedFaceted::DescribeYourselfTo(scene);
   }

   G4Polyhedron *CreatePolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4VTwistedFaceted, CreatePolyhedron, );
   }

   G4Polyhedron *GetPolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4VTwistedFaceted, GetPolyhedron, );
   }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4VTwistedFaceted, StreamInfo, os);
   }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4VTwistedFaceted, GetExtent, ); }

   G4GeometryType GetEntityType() const override
   {
      PYBIND11_OVERRIDE(G4GeometryType, G4VTwistedFaceted, GetEntityType, );
   }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4VTwistedFaceted, Clone, ); }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4VTwistedFaceted, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4VTwistedFaceted, GetConstituentSolid, no);
   }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4VTwistedFaceted, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4VTwistedFaceted, GetDisplacedSolidPtr, );
   }
};

void export_G4VTwistedFaceted(py::module &m)
{
   py::class_<G4VTwistedFaceted, PyG4VTwistedFaceted, G4VSolid, py::nodelete>(m, "G4VTwistedFaceted")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double, G4double, G4double, G4double,
                    G4double, G4double, G4double>(),
           py::arg("pname"), py::arg("PhiTwist"), py::arg("pDz"), py::arg("pTheta"), py::arg("pPhi"), py::arg("pDy1"),
           py::arg("pDx1"), py::arg("pDx2"), py::arg("pDy2"), py::arg("pDx3"), py::arg("pDx4"), py::arg("pAlph"))

      .def("__copy__", [](const PyG4VTwistedFaceted &self) { return PyG4VTwistedFaceted(self); })
      .def("__deepcopy__", [](const PyG4VTwistedFaceted &self, py::dict) { return PyG4VTwistedFaceted(self); })
      .def("ComputeDimensions", &G4VTwistedFaceted::ComputeDimensions)
      .def("BoundingLimits", &G4VTwistedFaceted::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4VTwistedFaceted::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"),
           py::arg("pTransform"), py::arg("pMin"), py::arg("pMax"))

      .def(
         "DistanceToIn",
         py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4VTwistedFaceted::DistanceToIn, py::const_),
         py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4VTwistedFaceted::DistanceToIn, py::const_),
           py::arg("p"))

      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4VTwistedFaceted::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcnorm") = false,
           py::arg("validnorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4VTwistedFaceted::DistanceToOut, py::const_),
           py::arg("p"))

      .def("Inside", &G4VTwistedFaceted::Inside, py::arg("p"))
      .def("SurfaceNormal", &G4VTwistedFaceted::SurfaceNormal, py::arg("p"))
      .def("GetPointOnSurface", &G4VTwistedFaceted::GetPointOnSurface)
      .def("GetPointInSolid", &G4VTwistedFaceted::GetPointInSolid, py::arg("z"))
      .def("GetCubicVolume", &G4VTwistedFaceted::GetCubicVolume)
      .def("GetSurfaceArea", &G4VTwistedFaceted::GetSurfaceArea)
      .def("DescribeYourselfTo", &G4VTwistedFaceted::DescribeYourselfTo, py::arg("scene"))
      .def("CreatePolyhedron", &G4VTwistedFaceted::CreatePolyhedron, py::return_value_policy::reference)
      .def("GetPolyhedron", &G4VTwistedFaceted::GetPolyhedron, py::return_value_policy::reference)
      .def("StreamInfo", &G4VTwistedFaceted::StreamInfo, py::arg("os"))
      .def("GetTwistAngle", &G4VTwistedFaceted::GetTwistAngle)
      .def("GetDx1", &G4VTwistedFaceted::GetDx1)
      .def("GetDx2", &G4VTwistedFaceted::GetDx2)
      .def("GetDx3", &G4VTwistedFaceted::GetDx3)
      .def("GetDx4", &G4VTwistedFaceted::GetDx4)
      .def("GetDy1", &G4VTwistedFaceted::GetDy1)
      .def("GetDy2", &G4VTwistedFaceted::GetDy2)
      .def("GetDz", &G4VTwistedFaceted::GetDz)
      .def("GetPhi", &G4VTwistedFaceted::GetPhi)
      .def("GetTheta", &G4VTwistedFaceted::GetTheta)
      .def("GetAlpha", &G4VTwistedFaceted::GetAlpha)
      .def("Xcoef", &G4VTwistedFaceted::Xcoef, py::arg("u"), py::arg("phi"), py::arg("ftg"))
      .def("GetValueA", &G4VTwistedFaceted::GetValueA, py::arg("phi"))
      .def("GetValueB", &G4VTwistedFaceted::GetValueB, py::arg("phi"))
      .def("GetValueD", &G4VTwistedFaceted::GetValueD, py::arg("phi"))
      .def("GetExtent", &G4VTwistedFaceted::GetExtent)
      .def("GetEntityType", &G4VTwistedFaceted::GetEntityType);
}
