#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ExtrudedSolid.hh>
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

class PyG4ExtrudedSolid : public G4ExtrudedSolid, public py::trampoline_self_life_support {
public:
   using G4ExtrudedSolid::G4ExtrudedSolid;

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4ExtrudedSolid, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4ExtrudedSolid, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4ExtrudedSolid, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4ExtrudedSolid, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4ExtrudedSolid, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4ExtrudedSolid, DistanceToOut, p);
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ExtrudedSolid, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4ExtrudedSolid::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pMin, G4double &pMax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4ExtrudedSolid, CalculateExtent, pAxis, pVoxelLimit, pTransform, pMin, pMax);
   }

   G4GeometryType GetEntityType() const override
   {
      PYBIND11_OVERRIDE(G4GeometryType, G4ExtrudedSolid, GetEntityType, );
   }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4ExtrudedSolid, Clone, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4ExtrudedSolid, StreamInfo, os);
   }

   G4bool Normal(const G4ThreeVector &p, G4ThreeVector &n) const override
   {
      PYBIND11_OVERRIDE_IMPL(G4bool, G4ExtrudedSolid, "Normal", p, std::addressof(n));
      return G4ExtrudedSolid::Normal(p, n);
   }

   G4double SafetyFromOutside(const G4ThreeVector &p, G4bool aAccurate) const override
   {
      PYBIND11_OVERRIDE(G4double, G4ExtrudedSolid, SafetyFromOutside, p, aAccurate);
   }

   G4double SafetyFromInside(const G4ThreeVector &p, G4bool aAccurate) const override
   {
      PYBIND11_OVERRIDE(G4double, G4ExtrudedSolid, SafetyFromInside, p, aAccurate);
   }

   G4ThreeVector GetPointOnSurface() const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4ExtrudedSolid, GetPointOnSurface, );
   }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4ExtrudedSolid, GetSurfaceArea, ); }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4ExtrudedSolid, GetCubicVolume, ); }

   G4Polyhedron *CreatePolyhedron() const override
   {
      PYBIND11_OVERRIDE(G4Polyhedron *, G4ExtrudedSolid, CreatePolyhedron, );
   }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4ExtrudedSolid, GetPolyhedron, ); }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ExtrudedSolid, "DescribeYourselfTo", std::addressof(scene));
      G4ExtrudedSolid::DescribeYourselfTo(scene);
   }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4ExtrudedSolid, GetExtent, ); }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4ExtrudedSolid, ComputeDimensions, p, n, pRep);
   }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4ExtrudedSolid, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4ExtrudedSolid, GetConstituentSolid, no);
   }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4ExtrudedSolid, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4ExtrudedSolid, GetDisplacedSolidPtr, );
   }
};

void export_G4ExtrudedSolid(py::module &m)
{

   py::class_<G4ExtrudedSolid, PyG4ExtrudedSolid, G4TessellatedSolid> g4ExtrudedSolid(m, "G4ExtrudedSolid");

   py::class_<G4ExtrudedSolid::ZSection>(g4ExtrudedSolid, "ZSection")

      .def(py::init<G4double, const G4TwoVector &, G4double>(), py::arg("z"), py::arg("offset"), py::arg("scale"))
      .def(py::init<const G4ExtrudedSolid::ZSection &>())
      .def_readwrite("fZ", &G4ExtrudedSolid::ZSection::fZ)
      .def_readwrite("fOffset", &G4ExtrudedSolid::ZSection::fOffset)
      .def_readwrite("fScale", &G4ExtrudedSolid::ZSection::fScale);

   g4ExtrudedSolid
      .def(py::init<const G4String &, const std::vector<CLHEP::Hep2Vector, std::allocator<CLHEP::Hep2Vector>> &,
                    const std::vector<G4ExtrudedSolid::ZSection, std::allocator<G4ExtrudedSolid::ZSection>> &>(),
           py::arg("pName"), py::arg("polygon"), py::arg("zsections"))

      .def(py::init<const G4String &, const std::vector<CLHEP::Hep2Vector, std::allocator<CLHEP::Hep2Vector>> &,
                    G4double, const G4TwoVector &, G4double, const G4TwoVector &, G4double>(),
           py::arg("pName"), py::arg("polygon"), py::arg("halfZ"), py::arg("off1"), py::arg("scale1"), py::arg("off2"),
           py::arg("scale2"))

      .def("__copy__", [](const PyG4ExtrudedSolid &self) { return PyG4ExtrudedSolid(self); })
      .def("__deepcopy__", [](const PyG4ExtrudedSolid &self, py::dict) { return PyG4ExtrudedSolid(self); })

      .def("GetNofVertices", &G4ExtrudedSolid::GetNofVertices)
      .def("GetVertex", py::overload_cast<G4int>(&G4ExtrudedSolid::GetVertex, py::const_), py::arg("index"))

      .def("GetPolygon", &G4ExtrudedSolid::GetPolygon)
      .def("GetNofZSections", &G4ExtrudedSolid::GetNofZSections)
      .def("GetZSection", &G4ExtrudedSolid::GetZSection, py::arg("index"))
      .def("GetZSections", &G4ExtrudedSolid::GetZSections)
      .def("Inside", &G4ExtrudedSolid::Inside, py::arg("p"))
      .def("SurfaceNormal", &G4ExtrudedSolid::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4ExtrudedSolid::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4ExtrudedSolid::DistanceToIn, py::const_),
           py::arg("p"))

      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4ExtrudedSolid::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false,
           py::arg("validNorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4ExtrudedSolid::DistanceToOut, py::const_),
           py::arg("p"))

      .def("BoundingLimits", &G4ExtrudedSolid::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4ExtrudedSolid::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"),
           py::arg("pTransform"), py::arg("pMin"), py::arg("pMax"))

      .def("GetEntityType", &G4ExtrudedSolid::GetEntityType)
      .def("Clone", &G4ExtrudedSolid::Clone, py::return_value_policy::reference)
      .def("StreamInfo", &G4ExtrudedSolid::StreamInfo, py::arg("os"));
}
