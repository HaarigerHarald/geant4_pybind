#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4TwistedTubs.hh>
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

class PyG4TwistedTubs : public G4TwistedTubs, public py::trampoline_self_life_support {
public:
   using G4TwistedTubs::G4TwistedTubs;

   void ComputeDimensions(G4VPVParameterisation *arg0, const G4int arg1, const G4VPhysicalVolume *arg2) override
   {
      PYBIND11_OVERRIDE(void, G4TwistedTubs, ComputeDimensions, arg0, arg1, arg2);
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4TwistedTubs, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4TwistedTubs::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pMin, G4double &pMax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4TwistedTubs, CalculateExtent, pAxis, pVoxelLimit, pTransform, pMin, pMax);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4TwistedTubs, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4TwistedTubs, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcnorm, G4bool *validnorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4TwistedTubs, DistanceToOut, p, v, calcnorm, validnorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4TwistedTubs, DistanceToOut, p);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4TwistedTubs, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4TwistedTubs, SurfaceNormal, p);
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4TwistedTubs, "DescribeYourselfTo", std::addressof(scene));
      G4TwistedTubs::DescribeYourselfTo(scene);
   }

   G4Polyhedron *CreatePolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4TwistedTubs, CreatePolyhedron, );
   }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4TwistedTubs, GetPolyhedron, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4TwistedTubs, StreamInfo, os);
   }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4TwistedTubs, GetExtent, ); }

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4TwistedTubs, GetEntityType, ); }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4TwistedTubs, Clone, ); }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4TwistedTubs, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4TwistedTubs, GetSurfaceArea, ); }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4TwistedTubs, GetPointOnSurface, );
   }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4TwistedTubs, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4TwistedTubs, GetConstituentSolid, no);
   }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4TwistedTubs, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4TwistedTubs, GetDisplacedSolidPtr, );
   }
};

void export_G4TwistedTubs(py::module &m)
{
   py::class_<G4TwistedTubs, PyG4TwistedTubs, G4VSolid, py::nodelete>(m, "G4TwistedTubs")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double>(), py::arg("pname"),
           py::arg("twistedangle"), py::arg("endinnerrad"), py::arg("endouterrad"), py::arg("halfzlen"),
           py::arg("dphi"))

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4int, G4double>(), py::arg("pname"),
           py::arg("twistedangle"), py::arg("endinnerrad"), py::arg("endouterrad"), py::arg("halfzlen"),
           py::arg("nseg"), py::arg("totphi"))

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double, G4double>(), py::arg("pname"),
           py::arg("twistedangle"), py::arg("innerrad"), py::arg("outerrad"), py::arg("negativeEndz"),
           py::arg("positiveEndz"), py::arg("dphi"))

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double, G4int, G4double>(),
           py::arg("pname"), py::arg("twistedangle"), py::arg("innerrad"), py::arg("outerrad"), py::arg("negativeEndz"),
           py::arg("positiveEndz"), py::arg("nseg"), py::arg("totphi"))

      .def("__copy__", [](const PyG4TwistedTubs &self) { return PyG4TwistedTubs(self); })
      .def("__deepcopy__", [](const PyG4TwistedTubs &self, py::dict) { return PyG4TwistedTubs(self); })
      .def("ComputeDimensions", &G4TwistedTubs::ComputeDimensions)
      .def("BoundingLimits", &G4TwistedTubs::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4TwistedTubs::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"),
           py::arg("pTransform"), py::arg("pMin"), py::arg("pMax"))

      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4TwistedTubs::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4TwistedTubs::DistanceToIn, py::const_),
           py::arg("p"))

      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4TwistedTubs::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcnorm") = false,
           py::arg("validnorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4TwistedTubs::DistanceToOut, py::const_),
           py::arg("p"))

      .def("Inside", &G4TwistedTubs::Inside, py::arg("p"))
      .def("SurfaceNormal", &G4TwistedTubs::SurfaceNormal, py::arg("p"))
      .def("DescribeYourselfTo", &G4TwistedTubs::DescribeYourselfTo, py::arg("scene"))
      .def("CreatePolyhedron", &G4TwistedTubs::CreatePolyhedron, py::return_value_policy::reference)
      .def("GetPolyhedron", &G4TwistedTubs::GetPolyhedron, py::return_value_policy::reference)
      .def("StreamInfo", &G4TwistedTubs::StreamInfo, py::arg("os"))
      .def("GetDPhi", &G4TwistedTubs::GetDPhi)
      .def("GetPhiTwist", &G4TwistedTubs::GetPhiTwist)
      .def("GetInnerRadius", &G4TwistedTubs::GetInnerRadius)
      .def("GetOuterRadius", &G4TwistedTubs::GetOuterRadius)
      .def("GetInnerStereo", &G4TwistedTubs::GetInnerStereo)
      .def("GetOuterStereo", &G4TwistedTubs::GetOuterStereo)
      .def("GetZHalfLength", &G4TwistedTubs::GetZHalfLength)
      .def("GetKappa", &G4TwistedTubs::GetKappa)
      .def("GetTanInnerStereo", &G4TwistedTubs::GetTanInnerStereo)
      .def("GetTanInnerStereo2", &G4TwistedTubs::GetTanInnerStereo2)
      .def("GetTanOuterStereo", &G4TwistedTubs::GetTanOuterStereo)
      .def("GetTanOuterStereo2", &G4TwistedTubs::GetTanOuterStereo2)
      .def("GetEndZ", &G4TwistedTubs::GetEndZ, py::arg("i"))
      .def("GetEndPhi", &G4TwistedTubs::GetEndPhi, py::arg("i"))
      .def("GetEndInnerRadius", py::overload_cast<G4int>(&G4TwistedTubs::GetEndInnerRadius, py::const_), py::arg("i"))
      .def("GetEndOuterRadius", py::overload_cast<G4int>(&G4TwistedTubs::GetEndOuterRadius, py::const_), py::arg("i"))
      .def("GetEndInnerRadius", py::overload_cast<>(&G4TwistedTubs::GetEndInnerRadius, py::const_))
      .def("GetEndOuterRadius", py::overload_cast<>(&G4TwistedTubs::GetEndOuterRadius, py::const_))
      .def("GetExtent", &G4TwistedTubs::GetExtent)
      .def("GetEntityType", &G4TwistedTubs::GetEntityType)
      .def("Clone", &G4TwistedTubs::Clone, py::return_value_policy::reference)
      .def("GetCubicVolume", &G4TwistedTubs::GetCubicVolume)
      .def("GetSurfaceArea", &G4TwistedTubs::GetSurfaceArea)
      .def("GetPointOnSurface", &G4TwistedTubs::GetPointOnSurface);
}
