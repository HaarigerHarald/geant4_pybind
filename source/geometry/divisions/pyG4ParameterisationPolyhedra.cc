#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ParameterisationPolyhedra.hh>
#include <G4Material.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VTouchable.hh>
#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4Trd.hh>
#include <G4Trap.hh>
#include <G4Cons.hh>
#include <G4Sphere.hh>
#include <G4Orb.hh>
#include <G4Ellipsoid.hh>
#include <G4Torus.hh>
#include <G4Para.hh>
#include <G4Polycone.hh>
#include <G4Hype.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>
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

class PyG4VParameterisationPolyhedra : public G4VParameterisationPolyhedra, public py::trampoline_self_life_support {
public:
   using G4VParameterisationPolyhedra::G4VParameterisationPolyhedra;

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VParameterisationPolyhedra, ComputeTransformation, copyNo, physVol);
   }

   G4double GetMaxParameter() const override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4VParameterisationPolyhedra, GetMaxParameter, );
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4VParameterisationPolyhedra, ComputeSolid, arg0, arg1);
   }

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4VParameterisationPolyhedra, CheckParametersValidity, );
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4VParameterisationPolyhedra, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4VParameterisationPolyhedra, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4VParameterisationPolyhedra, GetMaterialScanner, );
   }

   void ComputeDimensions(G4Box &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolyhedra, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolyhedra::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Tubs &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolyhedra, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolyhedra::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Trd &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolyhedra, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolyhedra::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Trap &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolyhedra, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolyhedra::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Cons &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolyhedra, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolyhedra::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Sphere &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolyhedra, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolyhedra::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Orb &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolyhedra, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolyhedra::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Ellipsoid &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolyhedra, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolyhedra::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Torus &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolyhedra, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolyhedra::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Para &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolyhedra, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolyhedra::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Polycone &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolyhedra, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolyhedra::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Polyhedra &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolyhedra, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolyhedra::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Hype &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolyhedra, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolyhedra::ComputeDimensions(arg0, arg1, arg2);
   }
};

class PyG4ParameterisationPolyhedraRho : public G4ParameterisationPolyhedraRho,
                                         public py::trampoline_self_life_support {
public:
   using G4ParameterisationPolyhedraRho::G4ParameterisationPolyhedraRho;

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationPolyhedraRho, CheckParametersValidity, );
   }

   G4double GetMaxParameter() const override
   {
      PYBIND11_OVERRIDE(G4double, G4ParameterisationPolyhedraRho, GetMaxParameter, );
   }

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationPolyhedraRho, ComputeTransformation, copyNo, physVol);
   }

   void ComputeDimensions(G4Polyhedra &phedra, const G4int copyNo, const G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ParameterisationPolyhedraRho, "ComputeDimensions", std::addressof(phedra), copyNo,
                             physVol);
      G4ParameterisationPolyhedraRho::ComputeDimensions(phedra, copyNo, physVol);
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4ParameterisationPolyhedraRho, ComputeSolid, arg0, arg1);
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4ParameterisationPolyhedraRho, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4ParameterisationPolyhedraRho, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4ParameterisationPolyhedraRho, GetMaterialScanner, );
   }
};

class PyG4ParameterisationPolyhedraPhi : public G4ParameterisationPolyhedraPhi,
                                         public py::trampoline_self_life_support {
public:
   using G4ParameterisationPolyhedraPhi::G4ParameterisationPolyhedraPhi;

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationPolyhedraPhi, CheckParametersValidity, );
   }

   G4double GetMaxParameter() const override
   {
      PYBIND11_OVERRIDE(G4double, G4ParameterisationPolyhedraPhi, GetMaxParameter, );
   }

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationPolyhedraPhi, ComputeTransformation, copyNo, physVol);
   }

   void ComputeDimensions(G4Polyhedra &phedra, const G4int copyNo, const G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ParameterisationPolyhedraPhi, "ComputeDimensions", std::addressof(phedra), copyNo,
                             physVol);
      G4ParameterisationPolyhedraPhi::ComputeDimensions(phedra, copyNo, physVol);
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4ParameterisationPolyhedraPhi, ComputeSolid, arg0, arg1);
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4ParameterisationPolyhedraPhi, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4ParameterisationPolyhedraPhi, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4ParameterisationPolyhedraPhi, GetMaterialScanner, );
   }
};

class PyG4ParameterisationPolyhedraZ : public G4ParameterisationPolyhedraZ, public py::trampoline_self_life_support {
public:
   using G4ParameterisationPolyhedraZ::G4ParameterisationPolyhedraZ;

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationPolyhedraZ, CheckParametersValidity, );
   }

   G4double GetMaxParameter() const override
   {
      PYBIND11_OVERRIDE(G4double, G4ParameterisationPolyhedraZ, GetMaxParameter, );
   }

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationPolyhedraZ, ComputeTransformation, copyNo, physVol);
   }

   void ComputeDimensions(G4Polyhedra &phedra, const G4int copyNo, const G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ParameterisationPolyhedraZ, "ComputeDimensions", std::addressof(phedra), copyNo,
                             physVol);
      G4ParameterisationPolyhedraZ::ComputeDimensions(phedra, copyNo, physVol);
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4ParameterisationPolyhedraZ, ComputeSolid, arg0, arg1);
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4ParameterisationPolyhedraZ, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4ParameterisationPolyhedraZ, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4ParameterisationPolyhedraZ, GetMaterialScanner, );
   }
};

void export_G4ParameterisationPolyhedra(py::module &m)
{
   py::class_<G4VParameterisationPolyhedra, PyG4VParameterisationPolyhedra, G4VDivisionParameterisation>(
      m, "G4VParameterisationPolyhedra")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("msolid"), py::arg("divType"))

      .def("__copy__", [](const PyG4VParameterisationPolyhedra &self) { return PyG4VParameterisationPolyhedra(self); })

      .def("__deepcopy__",
           [](const PyG4VParameterisationPolyhedra &self, py::dict) { return PyG4VParameterisationPolyhedra(self); });

   py::class_<G4ParameterisationPolyhedraRho, PyG4ParameterisationPolyhedraRho, G4VParameterisationPolyhedra>(
      m, "G4ParameterisationPolyhedraRho")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("motherSolid"), py::arg("divType"))

      .def("__copy__",
           [](const PyG4ParameterisationPolyhedraRho &self) { return PyG4ParameterisationPolyhedraRho(self); })

      .def("__deepcopy__", [](const PyG4ParameterisationPolyhedraRho &self,
                              py::dict) { return PyG4ParameterisationPolyhedraRho(self); })

      .def("CheckParametersValidity", &G4ParameterisationPolyhedraRho::CheckParametersValidity)
      .def("GetMaxParameter", &G4ParameterisationPolyhedraRho::GetMaxParameter)
      .def("ComputeTransformation", &G4ParameterisationPolyhedraRho::ComputeTransformation, py::arg("copyNo"),
           py::arg("physVol"))

      .def("ComputeDimensions",
           py::overload_cast<G4Polyhedra &, const G4int, const G4VPhysicalVolume *>(
              &G4ParameterisationPolyhedraRho::ComputeDimensions, py::const_),
           py::arg("phedra"), py::arg("copyNo"), py::arg("physVol"));

   py::class_<G4ParameterisationPolyhedraPhi, PyG4ParameterisationPolyhedraPhi, G4VParameterisationPolyhedra>(
      m, "G4ParameterisationPolyhedraPhi")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("motherSolid"), py::arg("divType"))

      .def("__copy__",
           [](const PyG4ParameterisationPolyhedraPhi &self) { return PyG4ParameterisationPolyhedraPhi(self); })

      .def("__deepcopy__", [](const PyG4ParameterisationPolyhedraPhi &self,
                              py::dict) { return PyG4ParameterisationPolyhedraPhi(self); })

      .def("CheckParametersValidity", &G4ParameterisationPolyhedraPhi::CheckParametersValidity)
      .def("GetMaxParameter", &G4ParameterisationPolyhedraPhi::GetMaxParameter)
      .def("ComputeTransformation", &G4ParameterisationPolyhedraPhi::ComputeTransformation, py::arg("copyNo"),
           py::arg("physVol"))

      .def("ComputeDimensions",
           py::overload_cast<G4Polyhedra &, const G4int, const G4VPhysicalVolume *>(
              &G4ParameterisationPolyhedraPhi::ComputeDimensions, py::const_),
           py::arg("phedra"), py::arg("copyNo"), py::arg("physVol"));

   py::class_<G4ParameterisationPolyhedraZ, PyG4ParameterisationPolyhedraZ, G4VParameterisationPolyhedra>(
      m, "G4ParameterisationPolyhedraZ")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("motherSolid"), py::arg("divType"))

      .def("__copy__", [](const PyG4ParameterisationPolyhedraZ &self) { return PyG4ParameterisationPolyhedraZ(self); })

      .def("__deepcopy__",
           [](const PyG4ParameterisationPolyhedraZ &self, py::dict) { return PyG4ParameterisationPolyhedraZ(self); })

      .def("CheckParametersValidity", &G4ParameterisationPolyhedraZ::CheckParametersValidity)
      .def("GetMaxParameter", &G4ParameterisationPolyhedraZ::GetMaxParameter)
      .def("ComputeTransformation", &G4ParameterisationPolyhedraZ::ComputeTransformation, py::arg("copyNo"),
           py::arg("physVol"))

      .def("ComputeDimensions",
           py::overload_cast<G4Polyhedra &, const G4int, const G4VPhysicalVolume *>(
              &G4ParameterisationPolyhedraZ::ComputeDimensions, py::const_),
           py::arg("phedra"), py::arg("copyNo"), py::arg("physVol"));
}
