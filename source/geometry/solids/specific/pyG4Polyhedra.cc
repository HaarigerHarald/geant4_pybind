#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Polyhedra.hh>
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

class PyG4Polyhedra : public G4Polyhedra, public py::trampoline_self_life_support {
public:
   using G4Polyhedra::G4Polyhedra;

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4Polyhedra, Inside, p); }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Polyhedra, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Polyhedra, DistanceToIn, p);
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Polyhedra, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4Polyhedra::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pmin, G4double &pmax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4Polyhedra, CalculateExtent, pAxis, pVoxelLimit, pTransform, pmin, pmax);
   }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4Polyhedra, ComputeDimensions, p, n, pRep);
   }

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4Polyhedra, GetEntityType, ); }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4Polyhedra, Clone, ); }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4Polyhedra, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4Polyhedra, GetSurfaceArea, ); }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4Polyhedra, GetPointOnSurface, );
   }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4Polyhedra, StreamInfo, os);
   }

   G4Polyhedron *CreatePolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4Polyhedra, CreatePolyhedron, );
   }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4Polyhedra, SurfaceNormal, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Polyhedra, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Polyhedra, DistanceToOut, p);
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Polyhedra, "DescribeYourselfTo", std::addressof(scene));
      G4Polyhedra::DescribeYourselfTo(scene);
   }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4Polyhedra, GetExtent, ); }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Polyhedra, GetPolyhedron, ); }

   G4double DistanceTo(const G4ThreeVector &p, const G4bool outgoing) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Polyhedra, DistanceTo, p, outgoing);
   }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4Polyhedra, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4Polyhedra, GetConstituentSolid, no);
   }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4Polyhedra, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4Polyhedra, GetDisplacedSolidPtr, );
   }
};

void export_G4Polyhedra(py::module &m)
{
   py::class_<G4Polyhedra, PyG4Polyhedra, G4VCSGfaceted>(m, "G4Polyhedra")

      .def(py::init<const G4String &, G4double, G4double, G4int, G4int, const G4double *, const G4double *,
                    const G4double *>(),
           py::arg("name"), py::arg("phiStart"), py::arg("phiTotal"), py::arg("numSide"), py::arg("numZPlanes"),
           py::arg("zPlane"), py::arg("rInner"), py::arg("rOuter"))

      .def(py::init<const G4String &, G4double, G4double, G4int, G4int, const G4double *, const G4double *>(),
           py::arg("name"), py::arg("phiStart"), py::arg("phiTotal"), py::arg("numSide"), py::arg("numRZ"),
           py::arg("r"), py::arg("z"))

      .def("__copy__", [](const PyG4Polyhedra &self) { return PyG4Polyhedra(self); })
      .def("__deepcopy__", [](const PyG4Polyhedra &self, py::dict) { return PyG4Polyhedra(self); })
      .def("Inside", &G4Polyhedra::Inside, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4Polyhedra::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4Polyhedra::DistanceToIn, py::const_),
           py::arg("p"))

      .def("BoundingLimits", &G4Polyhedra::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4Polyhedra::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"),
           py::arg("pTransform"), py::arg("pmin"), py::arg("pmax"))

      .def("ComputeDimensions", &G4Polyhedra::ComputeDimensions, py::arg("p"), py::arg("n"), py::arg("pRep"))
      .def("GetEntityType", &G4Polyhedra::GetEntityType)
      .def("Clone", &G4Polyhedra::Clone, py::return_value_policy::reference)
      .def("GetCubicVolume", &G4Polyhedra::GetCubicVolume)
      .def("GetSurfaceArea", &G4Polyhedra::GetSurfaceArea)
      .def("GetPointOnSurface", &G4Polyhedra::GetPointOnSurface)
      .def("StreamInfo", &G4Polyhedra::StreamInfo, py::arg("os"))
      .def("CreatePolyhedron", &G4Polyhedra::CreatePolyhedron, py::return_value_policy::reference)
      .def("Reset", &G4Polyhedra::Reset)
      .def("GetNumSide", &G4Polyhedra::GetNumSide)
      .def("GetStartPhi", &G4Polyhedra::GetStartPhi)
      .def("GetEndPhi", &G4Polyhedra::GetEndPhi)
      .def("GetSinStartPhi", &G4Polyhedra::GetSinStartPhi)
      .def("GetCosStartPhi", &G4Polyhedra::GetCosStartPhi)
      .def("GetSinEndPhi", &G4Polyhedra::GetSinEndPhi)
      .def("GetCosEndPhi", &G4Polyhedra::GetCosEndPhi)
      .def("IsOpen", &G4Polyhedra::IsOpen)
      .def("IsGeneric", &G4Polyhedra::IsGeneric)
      .def("GetNumRZCorner", &G4Polyhedra::GetNumRZCorner)
      .def("GetCorner", &G4Polyhedra::GetCorner, py::arg("index"))
      .def("GetOriginalParameters", &G4Polyhedra::GetOriginalParameters, py::return_value_policy::reference)
      .def("SetOriginalParameters", py::overload_cast<G4PolyhedraHistorical *>(&G4Polyhedra::SetOriginalParameters),
           py::arg("pars"));
}
