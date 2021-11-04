#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Polycone.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>
#include <G4SolidExtentList.hh>
#include <G4IntersectingCone.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4VisAttributes.hh>
#include <G4EnclosingCylinder.hh>
#include <G4ReduciblePolygon.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4Polycone : public G4Polycone, public py::trampoline_self_life_support {
public:
   using G4Polycone::G4Polycone;

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4Polycone, Inside, p); }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Polycone, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Polycone, DistanceToIn, p);
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Polycone, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4Polycone::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pmin, G4double &pmax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4Polycone, CalculateExtent, pAxis, pVoxelLimit, pTransform, pmin, pmax);
   }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4Polycone, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4Polycone, GetSurfaceArea, ); }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4Polycone, GetPointOnSurface, );
   }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4Polycone, ComputeDimensions, p, n, pRep);
   }

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4Polycone, GetEntityType, ); }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4Polycone, Clone, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4Polycone, StreamInfo, os);
   }

   G4Polyhedron *CreatePolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4Polycone, CreatePolyhedron, );
   }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4Polycone, SurfaceNormal, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Polycone, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Polycone, DistanceToOut, p);
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Polycone, "DescribeYourselfTo", std::addressof(scene));
      G4Polycone::DescribeYourselfTo(scene);
   }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4Polycone, GetExtent, ); }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Polycone, GetPolyhedron, ); }

   G4double DistanceTo(const G4ThreeVector &p, const G4bool outgoing) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Polycone, DistanceTo, p, outgoing);
   }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4Polycone, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4Polycone, GetConstituentSolid, no);
   }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4Polycone, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4Polycone, GetDisplacedSolidPtr, );
   }
};

void export_G4Polycone(py::module &m)
{
   py::class_<G4Polycone, PyG4Polycone, G4VCSGfaceted>(m, "G4Polycone")

      .def(
         py::init<const G4String &, G4double, G4double, G4int, const G4double *, const G4double *, const G4double *>(),
         py::arg("name"), py::arg("phiStart"), py::arg("phiTotal"), py::arg("numZPlanes"), py::arg("zPlane"),
         py::arg("rInner"), py::arg("rOuter"))

      .def(py::init<const G4String &, G4double, G4double, G4int, const G4double *, const G4double *>(), py::arg("name"),
           py::arg("phiStart"), py::arg("phiTotal"), py::arg("numRZ"), py::arg("r"), py::arg("z"))

      .def("__copy__", [](const PyG4Polycone &self) { return PyG4Polycone(self); })
      .def("__deepcopy__", [](const PyG4Polycone &self, py::dict) { return PyG4Polycone(self); })
      .def("Inside", &G4Polycone::Inside, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4Polycone::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4Polycone::DistanceToIn, py::const_),
           py::arg("p"))

      .def("BoundingLimits", &G4Polycone::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4Polycone::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"),
           py::arg("pTransform"), py::arg("pmin"), py::arg("pmax"))

      .def("GetCubicVolume", &G4Polycone::GetCubicVolume)
      .def("GetSurfaceArea", &G4Polycone::GetSurfaceArea)
      .def("GetPointOnSurface", &G4Polycone::GetPointOnSurface)
      .def("ComputeDimensions", &G4Polycone::ComputeDimensions, py::arg("p"), py::arg("n"), py::arg("pRep"))
      .def("GetEntityType", &G4Polycone::GetEntityType)
      .def("Clone", &G4Polycone::Clone, py::return_value_policy::reference)
      .def("StreamInfo", &G4Polycone::StreamInfo, py::arg("os"))
      .def("CreatePolyhedron", &G4Polycone::CreatePolyhedron, py::return_value_policy::reference)
      .def("Reset", &G4Polycone::Reset)
      .def("GetStartPhi", &G4Polycone::GetStartPhi)
      .def("GetEndPhi", &G4Polycone::GetEndPhi)
      .def("GetSinStartPhi", &G4Polycone::GetSinStartPhi)
      .def("GetCosStartPhi", &G4Polycone::GetCosStartPhi)
      .def("GetSinEndPhi", &G4Polycone::GetSinEndPhi)
      .def("GetCosEndPhi", &G4Polycone::GetCosEndPhi)
      .def("IsOpen", &G4Polycone::IsOpen)
      .def("GetNumRZCorner", &G4Polycone::GetNumRZCorner)
      .def("GetCorner", &G4Polycone::GetCorner, py::arg("index"))
      .def("GetOriginalParameters", &G4Polycone::GetOriginalParameters, py::return_value_policy::reference)
      .def("SetOriginalParameters", py::overload_cast<G4PolyconeHistorical *>(&G4Polycone::SetOriginalParameters),
           py::arg("pars"));
}
