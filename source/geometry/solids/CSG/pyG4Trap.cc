#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Trap.hh>
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

class PyG4Trap : public G4Trap, public py::trampoline_self_life_support {
public:
   using G4Trap::G4Trap;

   G4double GetCubicVolume() override { PYBIND11_OVERRIDE(G4double, G4Trap, GetCubicVolume, ); }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE(G4double, G4Trap, GetSurfaceArea, ); }

   void ComputeDimensions(G4VPVParameterisation *p, const G4int n, const G4VPhysicalVolume *pRep) override
   {
      PYBIND11_OVERRIDE(void, G4Trap, ComputeDimensions, p, n, pRep);
   }

   void BoundingLimits(G4ThreeVector &pMin, G4ThreeVector &pMax) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Trap, "BoundingLimits", std::addressof(pMin), std::addressof(pMax));
      G4Trap::BoundingLimits(pMin, pMax);
   }

   G4bool CalculateExtent(const EAxis pAxis, const G4VoxelLimits &pVoxelLimit, const G4AffineTransform &pTransform,
                          G4double &pMin, G4double &pMax) const override
   {
      PYBIND11_OVERRIDE(G4bool, G4Trap, CalculateExtent, pAxis, pVoxelLimit, pTransform, pMin, pMax);
   }

   EInside Inside(const G4ThreeVector &p) const override { PYBIND11_OVERRIDE(EInside, G4Trap, Inside, p); }

   G4ThreeVector SurfaceNormal(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4Trap, SurfaceNormal, p);
   }

   G4double DistanceToIn(const G4ThreeVector &p, const G4ThreeVector &v) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Trap, DistanceToIn, p, v);
   }

   G4double DistanceToIn(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Trap, DistanceToIn, p);
   }

   G4double DistanceToOut(const G4ThreeVector &p, const G4ThreeVector &v, const G4bool calcNorm, G4bool *validNorm,
                          G4ThreeVector *n) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Trap, DistanceToOut, p, v, calcNorm, validNorm, n);
   }

   G4double DistanceToOut(const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4double, G4Trap, DistanceToOut, p);
   }

   G4GeometryType GetEntityType() const override { PYBIND11_OVERRIDE(G4GeometryType, G4Trap, GetEntityType, ); }

   G4ThreeVector GetPointOnSurface() const override { PYBIND11_OVERRIDE(G4ThreeVector, G4Trap, GetPointOnSurface, ); }

   G4VSolid *Clone() const override { PYBIND11_OVERRIDE(G4VSolid *, G4Trap, Clone, ); }

   std::ostream &StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(std::ostream &, G4Trap, StreamInfo, os);
   }

   void DescribeYourselfTo(G4VGraphicsScene &scene) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4Trap, "DescribeYourselfTo", std::addressof(scene));
      G4Trap::DescribeYourselfTo(scene);
   }

   G4Polyhedron *CreatePolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Trap, CreatePolyhedron, ); }

   G4Polyhedron *GetPolyhedron() const override { PYBIND11_OVERRIDE(G4Polyhedron *, G4Trap, GetPolyhedron, ); }

   G4VisExtent GetExtent() const override { PYBIND11_OVERRIDE(G4VisExtent, G4Trap, GetExtent, ); }

   const G4VSolid *GetConstituentSolid(G4int no) const override
   {
      PYBIND11_OVERRIDE(const G4VSolid *, G4Trap, GetConstituentSolid, no);
   }

   G4VSolid *GetConstituentSolid(G4int no) override { PYBIND11_OVERRIDE(G4VSolid *, G4Trap, GetConstituentSolid, no); }

   const G4DisplacedSolid *GetDisplacedSolidPtr() const override
   {
      PYBIND11_OVERRIDE(const G4DisplacedSolid *, G4Trap, GetDisplacedSolidPtr, );
   }

   G4DisplacedSolid *GetDisplacedSolidPtr() override
   {
      PYBIND11_OVERRIDE(G4DisplacedSolid *, G4Trap, GetDisplacedSolidPtr, );
   }
};

void export_G4Trap(py::module &m)
{
   py::class_<TrapSidePlane>(m, "TrapSidePlane")

      .def(py::init<>())
      .def("__copy__", [](const TrapSidePlane &self) { return TrapSidePlane(self); })
      .def("__deepcopy__", [](const TrapSidePlane &self, py::dict) { return TrapSidePlane(self); })
      .def_readwrite("a", &TrapSidePlane::a)
      .def_readwrite("b", &TrapSidePlane::b)
      .def_readwrite("c", &TrapSidePlane::c)
      .def_readwrite("d", &TrapSidePlane::d);

   py::class_<G4Trap, PyG4Trap, G4CSGSolid, py::nodelete>(m, "G4Trap")

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double, G4double, G4double, G4double,
                    G4double, G4double, G4double>(),
           py::arg("pName"), py::arg("pDz"), py::arg("pTheta"), py::arg("pPhi"), py::arg("pDy1"), py::arg("pDx1"),
           py::arg("pDx2"), py::arg("pAlp1"), py::arg("pDy2"), py::arg("pDx3"), py::arg("pDx4"), py::arg("pAlp2"))

      .def(py::init<const G4String &, const G4ThreeVector *>(), py::arg("pName"), py::arg("pt"))
      .def(py::init<const G4String &, G4double, G4double, G4double, G4double>(), py::arg("pName"), py::arg("pZ"),
           py::arg("pY"), py::arg("pX"), py::arg("pLTX"))

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double>(), py::arg("pName"),
           py::arg("pDx1"), py::arg("pDx2"), py::arg("pDy1"), py::arg("pDy2"), py::arg("pDz"))

      .def(py::init<const G4String &, G4double, G4double, G4double, G4double, G4double, G4double>(), py::arg("pName"),
           py::arg("pDx"), py::arg("pDy"), py::arg("pDz"), py::arg("pAlpha"), py::arg("pTheta"), py::arg("pPhi"))

      .def(py::init<const G4String &>(), py::arg("pName"))
      .def("__copy__", [](const PyG4Trap &self) { return PyG4Trap(self); })
      .def("__deepcopy__", [](const PyG4Trap &self, py::dict) { return PyG4Trap(self); })
      .def("GetZHalfLength", &G4Trap::GetZHalfLength)
      .def("GetYHalfLength1", &G4Trap::GetYHalfLength1)
      .def("GetXHalfLength1", &G4Trap::GetXHalfLength1)
      .def("GetXHalfLength2", &G4Trap::GetXHalfLength2)
      .def("GetTanAlpha1", &G4Trap::GetTanAlpha1)
      .def("GetYHalfLength2", &G4Trap::GetYHalfLength2)
      .def("GetXHalfLength3", &G4Trap::GetXHalfLength3)
      .def("GetXHalfLength4", &G4Trap::GetXHalfLength4)
      .def("GetTanAlpha2", &G4Trap::GetTanAlpha2)
      .def("GetSidePlane", &G4Trap::GetSidePlane, py::arg("n"))
      .def("GetSymAxis", &G4Trap::GetSymAxis)
      .def("SetAllParameters", &G4Trap::SetAllParameters, py::arg("pDz"), py::arg("pTheta"), py::arg("pPhi"),
           py::arg("pDy1"), py::arg("pDx1"), py::arg("pDx2"), py::arg("pAlp1"), py::arg("pDy2"), py::arg("pDx3"),
           py::arg("pDx4"), py::arg("pAlp2"))

      .def("GetCubicVolume", &G4Trap::GetCubicVolume)
      .def("GetSurfaceArea", &G4Trap::GetSurfaceArea)
      .def("ComputeDimensions", &G4Trap::ComputeDimensions, py::arg("p"), py::arg("n"), py::arg("pRep"))

      .def("BoundingLimits", &G4Trap::BoundingLimits, py::arg("pMin"), py::arg("pMax"))
      .def("CalculateExtent", &G4Trap::CalculateExtent, py::arg("pAxis"), py::arg("pVoxelLimit"), py::arg("pTransform"),
           py::arg("pMin"), py::arg("pMax"))

      .def("Inside", &G4Trap::Inside, py::arg("p"))
      .def("SurfaceNormal", &G4Trap::SurfaceNormal, py::arg("p"))
      .def("DistanceToIn",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &>(&G4Trap::DistanceToIn, py::const_),
           py::arg("p"), py::arg("v"))

      .def("DistanceToIn", py::overload_cast<const G4ThreeVector &>(&G4Trap::DistanceToIn, py::const_), py::arg("p"))
      .def("DistanceToOut",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4bool, G4bool *, G4ThreeVector *>(
              &G4Trap::DistanceToOut, py::const_),
           py::arg("p"), py::arg("v"), py::arg("calcNorm") = false,
           py::arg("validNorm") = static_cast<G4bool *>(nullptr), py::arg("n") = static_cast<G4ThreeVector *>(nullptr))

      .def("DistanceToOut", py::overload_cast<const G4ThreeVector &>(&G4Trap::DistanceToOut, py::const_), py::arg("p"))
      .def("GetEntityType", &G4Trap::GetEntityType)
      .def("GetPointOnSurface", &G4Trap::GetPointOnSurface)
      .def("Clone", &G4Trap::Clone, py::return_value_policy::reference)
      .def("StreamInfo", &G4Trap::StreamInfo, py::arg("os"))
      .def("DescribeYourselfTo", &G4Trap::DescribeYourselfTo, py::arg("scene"))
      .def("CreatePolyhedron", &G4Trap::CreatePolyhedron, py::return_value_policy::reference);
}
