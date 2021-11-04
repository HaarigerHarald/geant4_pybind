#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4GenericPolycone.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>
#include <G4SolidExtentList.hh>
#include <G4IntersectingCone.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4EnclosingCylinder.hh>
#include <G4ReduciblePolygon.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4GenericPolycone : public G4GenericPolycone, public py::trampoline_self_life_support {
public:
   using G4GenericPolycone::G4GenericPolycone;

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4GenericPolycone, Inside, p); }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4GenericPolycone, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4GenericPolycone, DistanceToIn, p);
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4GenericPolycone, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4GenericPolycone::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pmin, G4double &pmax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4GenericPolycone, CalculateExtent, pAxis, pVoxelLimit, pTransform, pmin, pmax);
   }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4GenericPolycone, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4GenericPolycone, GetSurfaceArea, ); }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4GenericPolycone, GetPointOnSurface, );
   }

   G4GeometryType GetEntityType() const override
   {
      PYBIND11_OVERRIDE(G4GeometryType, G4GenericPolycone, GetEntityType, );
   }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4GenericPolycone, Clone, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4GenericPolycone, StreamInfo, os);
   }

   G4Polyhedron *CreatePolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4GenericPolycone, CreatePolyhedron, );
   }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4GenericPolycone, SurfaceNormal, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4GenericPolycone, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4GenericPolycone, DistanceToOut, p);
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4GenericPolycone, "DescribeYourselfTo", std::addressof(scene));
      G4GenericPolycone::DescribeYourselfTo(scene);
   }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4GenericPolycone, GetExtent, ); }

   G4Polyhedron *GetPolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4GenericPolycone, GetPolyhedron, );
   }

   G4double DistanceTo(const G4ThreeVector &p, const G4bool outgoing) const override
   {
      PYBIND11_OVERRIDE(G4double, G4GenericPolycone, DistanceTo, p, outgoing);
   }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4GenericPolycone, ComputeDimensions, p, n, pRep);
   }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4GenericPolycone, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4GenericPolycone, GetConstituentSolid, no);
   }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4GenericPolycone, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4GenericPolycone, GetDisplacedSolidPtr, );
   }
};

void export_G4GenericPolycone(py::module &m)
{

   py::class_<G4GenericPolycone, PyG4GenericPolycone, G4VCSGfaceted>(m, "G4GenericPolycone")

      .def(py::init<const G4String &, G4double, G4double, G4int, const G4double *, const G4double *>(), py::arg("name"),
           py::arg("phiStart"), py::arg("phiTotal"), py::arg("numRZ"), py::arg("r"), py::arg("z"))

      .def("__copy__", [](const PyG4GenericPolycone &self) { return PyG4GenericPolycone(self); })
      .def("__deepcopy__", [](const PyG4GenericPolycone &self, py::dict) { return PyG4GenericPolycone(self); })
      .def("Inside", &G4GenericPolycone::Inside, py::arg("p"))
      .def(
         "DistanceToIn",
         py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4GenericPolycone::DistanceToIn, py::const_),
         py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4GenericPolycone::DistanceToIn, py::const_),
           py::arg("p"))

      .def("BoundingLimits", &G4GenericPolycone::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4GenericPolycone::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"),
           py::arg("pTransform"), py::arg("pmin"), py::arg("pmax"))

      .def("GetCubicVolume", &G4GenericPolycone::GetCubicVolume)
      .def("GetSurfaceArea", &G4GenericPolycone::GetSurfaceArea)
      .def("GetPointOnSurface", &G4GenericPolycone::GetPointOnSurface)
      .def("GetEntityType", &G4GenericPolycone::GetEntityType)
      .def("Clone", &G4GenericPolycone::Clone, py::return_value_policy::reference)
      .def("StreamInfo", &G4GenericPolycone::StreamInfo, py::arg("os"))
      .def("CreatePolyhedron", &G4GenericPolycone::CreatePolyhedron, py::return_value_policy::reference)
      .def("Reset", &G4GenericPolycone::Reset)
      .def("GetStartPhi", &G4GenericPolycone::GetStartPhi)
      .def("GetEndPhi", &G4GenericPolycone::GetEndPhi)
      .def("GetSinStartPhi", &G4GenericPolycone::GetSinStartPhi)
      .def("GetCosStartPhi", &G4GenericPolycone::GetCosStartPhi)
      .def("GetSinEndPhi", &G4GenericPolycone::GetSinEndPhi)
      .def("GetCosEndPhi", &G4GenericPolycone::GetCosEndPhi)
      .def("IsOpen", &G4GenericPolycone::IsOpen)
      .def("GetNumRZCorner", &G4GenericPolycone::GetNumRZCorner)
      .def("GetCorner", &G4GenericPolycone::GetCorner, py::arg("index"));
}
