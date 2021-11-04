#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VSolid.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VSolid : public G4VSolid, public py::trampoline_self_life_support {
public:
   using G4VSolid::G4VSolid;

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pMin, G4double &pMax) const override
   {
      PYBIND11_OVERRIDE_PURE(G4bool, G4VSolid, CalculateExtent, pAxis, pVoxelLimit, pTransform, pMin, pMax);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE_PURE(EInside, G4VSolid, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE_PURE(G4ThreeVector, G4VSolid, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4VSolid, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4VSolid, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4VSolid, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4VSolid, DistanceToOut, p);
   }

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE_PURE(G4GeometryType, G4VSolid, GetEntityType, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE_PURE(std::ostream &, G4VSolid, StreamInfo, os);
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VSolid, DescribeYourselfTo, std::addressof(scene));
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VSolid, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4VSolid::BoundingLimits(pMin, pMax);
   }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4VSolid, ComputeDimensions, p, n, pRep);
   }

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4VSolid, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4VSolid, GetSurfaceArea, ); }

   G4ThreeVector GetPointOnSurface() const override { PYBIND11_OVERRIDE(G4ThreeVector, G4VSolid, GetPointOnSurface, ); }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4VSolid, Clone, ); }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4VSolid, GetExtent, ); }

   G4Polyhedron *CreatePolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4VSolid, CreatePolyhedron, ); }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4VSolid, GetPolyhedron, ); }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4VSolid, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4VSolid, GetConstituentSolid, no);
   }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4VSolid, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4VSolid, GetDisplacedSolidPtr, );
   }
};

void export_G4VSolid(py::module &m)
{
   py::class_<G4VSolid, PyG4VSolid, py::nodelete>(m, "G4VSolid")

      .def(py::init<const G4String &>(), py::arg("name"))
      .def("__copy__", [](const PyG4VSolid &self) { return PyG4VSolid(self); })
      .def("__deepcopy__", [](const PyG4VSolid &self, py::dict) { return PyG4VSolid(self); })
      .def("GetName", &G4VSolid::GetName)
      .def("SetName", &G4VSolid::SetName, py::arg("name"))
      .def("GetTolerance", &G4VSolid::GetTolerance)
      .def("BoundingLimits", &G4VSolid::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4VSolid::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"),
           py::arg("pTransform"), py::arg("pMin"), py::arg("pMax"))

      .def("Inside", &G4VSolid::Inside, py::arg("p"))
      .def("SurfaceNormal", &G4VSolid::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4VSolid::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4VSolid::DistanceToIn, py::const_), py::arg("p"))
      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4VSolid::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false,
           py::arg("validNorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4VSolid::DistanceToOut, py::const_),
           py::arg("p"))

      .def("ComputeDimensions", &G4VSolid::ComputeDimensions, py::arg("p"), py::arg("n"), py::arg("pRep"))
      .def("GetCubicVolume", &G4VSolid::GetCubicVolume)
      .def("GetSurfaceArea", &G4VSolid::GetSurfaceArea)
      .def("GetEntityType", &G4VSolid::GetEntityType)
      .def("GetPointOnSurface", &G4VSolid::GetPointOnSurface)
      .def("Clone", &G4VSolid::Clone, py::return_value_policy::reference)
      .def("StreamInfo", &G4VSolid::StreamInfo, py::arg("os"))
      .def("DumpInfo", &G4VSolid::DumpInfo)
      .def("DescribeYourselfTo", &G4VSolid::DescribeYourselfTo, py::arg("scene"))
      .def("GetExtent", &G4VSolid::GetExtent)
      .def("CreatePolyhedron", &G4VSolid::CreatePolyhedron, py::return_value_policy::reference)
      .def("GetPolyhedron", &G4VSolid::GetPolyhedron, py::return_value_policy::reference)
      .def("GetConstituentSolid", py::overload_cast<G4int>(&G4VSolid::GetConstituentSolid, py::const_), py::arg("no"),
           py::return_value_policy::reference)

      .def("GetConstituentSolid", py::overload_cast<G4int>(&G4VSolid::GetConstituentSolid), py::arg("no"),
           py::return_value_policy::reference)

      .def("GetDisplacedSolidPtr", py::overload_cast<>(&G4VSolid::GetDisplacedSolidPtr, py::const_),
           py::return_value_policy::reference)

      .def("GetDisplacedSolidPtr", py::overload_cast<>(&G4VSolid::GetDisplacedSolidPtr),
           py::return_value_policy::reference)

      .def("EstimateCubicVolume", &G4VSolid::EstimateCubicVolume, py::arg("nStat"), py::arg("epsilon"))
      .def("EstimateSurfaceArea", &G4VSolid::EstimateSurfaceArea, py::arg("nStat"), py::arg("ell"))
      .def("__eq__", &G4VSolid::operator==, py::is_operator())
      .def(
         "__str__",
         [](const G4VSolid &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator());
}
