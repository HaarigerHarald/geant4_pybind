#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4TwistedBox.hh>
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

class PyG4TwistedBox : public G4TwistedBox, public py::trampoline_self_life_support {
public:
   using G4TwistedBox::G4TwistedBox;

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4TwistedBox, GetEntityType, ); }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4TwistedBox, Clone, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4TwistedBox, StreamInfo, os);
   }

   void ComputeDimensions(G4VPVParameterisation *arg0, const G4int arg1, const G4VPhysicalVolume *arg2) override
   {
      PYBIND11_OVERRIDE(void, G4TwistedBox, ComputeDimensions, arg0, arg1, arg2);
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4TwistedBox, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4TwistedBox::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pMin, G4double &pMax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4TwistedBox, CalculateExtent, pAxis, pVoxelLimit, pTransform, pMin, pMax);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4TwistedBox, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4TwistedBox, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcnorm, G4bool *validnorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4TwistedBox, DistanceToOut, p, v, calcnorm, validnorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4TwistedBox, DistanceToOut, p);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4TwistedBox, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4TwistedBox, SurfaceNormal, p);
   }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4TwistedBox, GetPointOnSurface, );
   }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4TwistedBox, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4TwistedBox, GetSurfaceArea, ); }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4TwistedBox, "DescribeYourselfTo", std::addressof(scene));
      G4TwistedBox::DescribeYourselfTo(scene);
   }

   G4Polyhedron *CreatePolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4TwistedBox, CreatePolyhedron, );
   }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4TwistedBox, GetPolyhedron, ); }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4TwistedBox, GetExtent, ); }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4TwistedBox, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4TwistedBox, GetConstituentSolid, no);
   }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4TwistedBox, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4TwistedBox, GetDisplacedSolidPtr, );
   }
};

void export_G4TwistedBox(py::module &m)
{
   py::class_<G4TwistedBox, PyG4TwistedBox, G4VTwistedFaceted>(m, "G4TwistedBox")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double>(), py::arg("pName"), py::arg("pPhiTwist"),
           py::arg("pDx"), py::arg("pDy"), py::arg("pDz"))

      .def("__copy__", [](const PyG4TwistedBox &self) { return PyG4TwistedBox(self); })
      .def("__deepcopy__", [](const PyG4TwistedBox &self, py::dict) { return PyG4TwistedBox(self); })
      .def("GetXHalfLength", &G4TwistedBox::GetXHalfLength)
      .def("GetYHalfLength", &G4TwistedBox::GetYHalfLength)
      .def("GetZHalfLength", &G4TwistedBox::GetZHalfLength)
      .def("GetPhiTwist", &G4TwistedBox::GetPhiTwist)
      .def("GetEntityType", &G4TwistedBox::GetEntityType)
      .def("Clone", &G4TwistedBox::Clone, py::return_value_policy::reference)
      .def("StreamInfo", &G4TwistedBox::StreamInfo, py::arg("os"));
}
